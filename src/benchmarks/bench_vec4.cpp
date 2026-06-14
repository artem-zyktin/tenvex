#include "tenvex.h"

#include <benchmark/benchmark.h>

#include <vector>
#include <random>

using namespace tnvx;

// Runtime data so nothing folds to a compile-time constant.
static std::vector<vec4> make_vecs(int n, unsigned seed)
{
	std::mt19937 rng(seed);
	std::uniform_real_distribution<float> d(-1.0f, 1.0f);
	std::vector<vec4> v;
	v.reserve(n);
	for (int i = 0; i < n; ++i)
		v.push_back(vec4 { d(rng), d(rng), d(rng), 0.0f });
	return v;
}

inline std::vector<tnvx::vec4> make_points(int n, unsigned seed)
{
	std::mt19937 rng(seed);
	std::uniform_real_distribution<float> d(-1.0f, 1.0f);
	std::vector<tnvx::vec4> v;
	v.reserve(n);
	for (int i = 0; i < n; ++i)
		v.push_back(tnvx::vec4{ d(rng), d(rng), d(rng), 1.0f }); // w=1: point
	return v;
}

// =====================================================================
// LATENCY: each iteration depends on the previous result (serial chain).
// This is the metric for scattered everyday math: the result is needed
// before moving on.
// =====================================================================
static void BM_Dot3_Latency(benchmark::State& state)
{
	vec4 a { 1.0f, 2.0f, 3.0f, 0.0f };
	vec4 b { 0.5f, 0.5f, 0.5f, 0.0f };
	float acc = 0.0f;
	for (auto _ : state)
	{
		vec4 bb = b + vec4 { acc, 0.0f, 0.0f, 0.0f }; // depends on previous result
		float d = dot3(a, bb);
		acc = d * 1e-7f;                              // feedback = dependency chain
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_Dot3_Latency);

static void BM_Norm3_Latency(benchmark::State& state)
{
	vec4 v { 1.0f, 2.0f, 3.0f, 1.0f };
	for (auto _ : state)
	{
		v = norm3(v) + vec4 { 1e-3f, 2e-3f, 3e-3f, 0.0f }; // chain through v
		benchmark::DoNotOptimize(v);
	}
}
BENCHMARK(BM_Norm3_Latency);

// =====================================================================
// THROUGHPUT: independent inputs, no cross-iteration dependency, so the
// CPU can pipeline. Contrast to latency.
// =====================================================================
static void BM_Dot3_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		float d = dot3(a[i], b[i]);
		benchmark::DoNotOptimize(d);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Dot3_Throughput);

// =====================================================================
// Compound expression: tenvex vs hand-written intrinsics.
// If the numbers are roughly equal, the abstraction is zero-cost.
// =====================================================================
static void BM_Compound_tenvex(benchmark::State& state)
{
	const auto va = make_vecs(1024, 1);
	const auto vb = make_vecs(1024, 2);
	const auto vc = make_vecs(1024, 3);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 r = norm3(va[i] + vb[i] * 2.0f) * dot3(vb[i], vc[i]) + vc[i] * 3.0f;
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Compound_tenvex);

#if defined(TNVX_SSE41)
#include <smmintrin.h>
static __m128 dp3_raw(__m128 a, __m128 b) { return _mm_dp_ps(a, b, 0x7F); }

static __m128 norm3_raw(__m128 v)
{
	__m128 len = _mm_sqrt_ps(dp3_raw(v, v));
	return _mm_blend_ps(_mm_div_ps(v, len), v, 0b1000);
}

static void BM_Compound_intrinsics(benchmark::State& state)
{
	const auto va = make_vecs(1024, 1);
	const auto vb = make_vecs(1024, 2);
	const auto vc = make_vecs(1024, 3);
	std::size_t i = 0;
	for (auto _ : state)
	{
		__m128 a = va[i].eval(), b = vb[i].eval(), c = vc[i].eval();
		__m128 t = norm3_raw(_mm_add_ps(a, _mm_mul_ps(b, _mm_set1_ps(2.0f))));
		__m128 d = dp3_raw(b, c);
		__m128 r = _mm_add_ps(_mm_mul_ps(t, d), _mm_mul_ps(c, _mm_set1_ps(3.0f)));
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Compound_intrinsics);

static void BM_Compound_manual_kernels(benchmark::State& state)
{
	const auto va = make_vecs(1024, 1);
	const auto vb = make_vecs(1024, 2);
	const auto vc = make_vecs(1024, 3);
	std::size_t i = 0;
	for (auto _ : state)
	{
		using namespace tnvx::detail;
		vf4 a = va[i].eval(), b = vb[i].eval(), c = vc[i].eval();
		vf4 t = norm3(add(a, mul(b, set_all(2.0f))));
		vf4 d = dot3(b, c);
		vf4 r = add(mul(t, d), mul(c, set_all(3.0f)));
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Compound_manual_kernels);
#elif defined(TNVX_NEON)
#include <arm_neon.h>
static float32x4_t dp3_raw(float32x4_t a, float32x4_t b)
{
	float32x4_t prod = vmulq_f32(a, b);
	prod = vsetq_lane_f32(0.0f, prod, 3);
	return vdupq_n_f32(vaddvq_f32(prod));
}

static float32x4_t norm3_raw(float32x4_t v)
{
	float32x4_t len = vsqrtq_f32(dp3_raw(v, v));
	float32x4_t n = vdivq_f32(v, len);
	return vsetq_lane_f32(vgetq_lane_f32(v, 3), n, 3);
}

static void BM_Compound_intrinsics(benchmark::State& state)
{
	const auto va = make_vecs(1024, 1);
	const auto vb = make_vecs(1024, 2);
	const auto vc = make_vecs(1024, 3);
	std::size_t i = 0;
	for (auto _ : state)
	{
		float32x4_t a = va[i].eval(), b = vb[i].eval(), c = vc[i].eval();
		float32x4_t t = norm3_raw(vaddq_f32(a, vmulq_f32(b, vdupq_n_f32(2.0f))));
		float32x4_t d = dp3_raw(b, c);
		float32x4_t r = vaddq_f32(vmulq_f32(t, d), vmulq_f32(c, vdupq_n_f32(3.0f)));
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Compound_intrinsics);

static void BM_Compound_manual_kernels(benchmark::State& state)
{
	const auto va = make_vecs(1024, 1);
	const auto vb = make_vecs(1024, 2);
	const auto vc = make_vecs(1024, 3);
	std::size_t i = 0;
	for (auto _ : state)
	{
		using namespace tnvx::detail;
		vf4 a = va[i].eval(), b = vb[i].eval(), c = vc[i].eval();
		vf4 t = norm3(add(a, mul(b, set_all(2.0f))));
		vf4 d = dot3(b, c);
		vf4 r = add(mul(t, d), mul(c, set_all(3.0f)));
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Compound_manual_kernels);
#endif

// =====================================================================
// Gameplay-style query: do two units face roughly the same way?
// Latency-bound - the answer is needed before branching on it.
// =====================================================================
static void BM_FacingSameWay(benchmark::State& state)
{
	vec4 fa = norm3(vec4 { 1.0f, 0.0f, 0.2f, 0.0f });
	vec4 fb = vec4 { 0.9f, 0.1f, 0.1f, 0.0f };
	float jitter = 0.0f;
	for (auto _ : state)
	{
		vec4 f = norm3(fb + vec4 { jitter, 0.0f, 0.0f, 0.0f });
		float c = dot3(fa, f);
		bool same = c > 0.95f;
		jitter = c * 1e-6f;
		benchmark::DoNotOptimize(same);
	}
}
BENCHMARK(BM_FacingSameWay);

static void BM_Dot4_Latency(benchmark::State& state)
{
	vec4 a{ 1.0f, 2.0f, 3.0f, 1.0f };
	vec4 b{ 0.5f, 0.5f, 0.5f, 0.5f };
	float acc = 0.0f;
	for (auto _ : state)
	{
		vec4 bb = b + vec4{ acc, 0.0f, 0.0f, 0.0f };
		float d = dot4(a, bb);
		acc = d * 1e-7f;
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_Dot4_Latency);

static void BM_Dot4_Throughput(benchmark::State& state)
{
	const auto a = make_points(1024, 1);
	const auto b = make_points(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		float d = dot4(a[i], b[i]);
		benchmark::DoNotOptimize(d);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Dot4_Throughput);

// =====================================================================
// min/max throughput: independent inputs, fully pipelineable.
// =====================================================================
static void BM_Min_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 r = min(a[i], b[i]);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Min_Throughput);

static void BM_Max_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 r = max(a[i], b[i]);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Max_Throughput);

// =====================================================================
// AABB build: grow a bounding box over a point stream. lo/hi feed back
// into the next iteration, so this is min/max on a serial chain -
// the latency metric.
// =====================================================================
static void BM_AABB_Latency(benchmark::State& state)
{
	const auto pts = make_vecs(1024, 1);
	vec4 lo {  1e30f,  1e30f,  1e30f, 0.0f };
	vec4 hi { -1e30f, -1e30f, -1e30f, 0.0f };
	std::size_t i = 0;
	for (auto _ : state)
	{
		lo = min(lo, pts[i]); // each step depends on the running box
		hi = max(hi, pts[i]);
		i = (i + 1) & 1023;
	}
	benchmark::DoNotOptimize(lo);
	benchmark::DoNotOptimize(hi);
}
BENCHMARK(BM_AABB_Latency);

static void BM_Abs_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 r = abs(a[i]);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Abs_Throughput);

static void BM_Abs_Latency(benchmark::State& state)
{
	vec4 v { -1.0f, 2.0f, -3.0f, 4.0f };
	for (auto _ : state)
	{
		v = abs(v - vec4 { 0.5f, 0.5f, 0.5f, 0.5f });
		benchmark::DoNotOptimize(v);
	}
}
BENCHMARK(BM_Abs_Latency);

static void BM_Clamp_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const vec4 lo { 0.0f, 0.0f, 0.0f, 0.0f };
	const vec4 hi { 1.0f, 1.0f, 1.0f, 1.0f };
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 r = clamp(a[i], lo, hi);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Clamp_Throughput);

static void BM_Clamp_Latency(benchmark::State& state)
{
	vec4 v { 0.5f, -2.0f, 3.0f, 0.25f };
	const vec4 lo { 0.0f, 0.0f, 0.0f, 0.0f };
	const vec4 hi { 1.0f, 1.0f, 1.0f, 1.0f };
	for (auto _ : state)
	{
		v = clamp(v + vec4 { 0.1f, 0.1f, 0.1f, 0.1f }, lo, hi);
		benchmark::DoNotOptimize(v);
	}
}
BENCHMARK(BM_Clamp_Latency);

static void BM_Saturate_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 r = saturate(a[i]);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Saturate_Throughput);

static void BM_Lerp_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	const Scalar t { 0.35f };
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 r = lerp(a[i], b[i], t);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Lerp_Throughput);

static void BM_Lerp_Latency(benchmark::State& state)
{
	vec4 v { 0.0f, 0.0f, 0.0f, 0.0f };
	const vec4 target { 1.0f, 2.0f, 3.0f, 0.0f };
	const Scalar t { 0.25f };
	for (auto _ : state)
	{
		v = lerp(v, target, t);
		benchmark::DoNotOptimize(v);
	}
}
BENCHMARK(BM_Lerp_Latency);

static void BM_Dist3_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		float r = dist3(a[i], b[i]);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Dist3_Throughput);

static void BM_Dist3Sq_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		float r = dist3_sq(a[i], b[i]);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Dist3Sq_Throughput);

static void BM_Reflect_Throughput(benchmark::State& state)
{
	const auto v = make_vecs(1024, 1);
	const auto n = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 r = reflect(v[i], n[i]);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Reflect_Throughput);

static void BM_Reflect_Latency(benchmark::State& state)
{
	vec4 v { 1.0f, -1.0f, 0.5f, 0.0f };
	const vec4 n { 0.0f, 1.0f, 0.0f, 0.0f };
	for (auto _ : state)
	{
		v = reflect(v, n);
		benchmark::DoNotOptimize(v);
	}
}
BENCHMARK(BM_Reflect_Latency);

static void BM_Floor_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 r = floor(a[i]);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Floor_Throughput);

static void BM_Ceil_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 r = ceil(a[i]);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Ceil_Throughput);

static void BM_Round_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 r = round(a[i]);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Round_Throughput);

static void BM_Frac_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 r = frac(a[i]);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Frac_Throughput);

static void BM_Hadamard_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 r = hadamard(a[i], b[i]);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Hadamard_Throughput);

static void BM_Hadamard_Latency(benchmark::State& state)
{
	vec4 v { 1.001f, 0.999f, 1.0f, 1.0f };
	const vec4 k { 0.9999f, 1.0001f, 1.0f, 1.0f };
	for (auto _ : state)
	{
		v = hadamard(v, k);
		benchmark::DoNotOptimize(v);
	}
}
BENCHMARK(BM_Hadamard_Latency);
