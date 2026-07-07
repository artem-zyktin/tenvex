#include "naive_vec4.h"

#include <benchmark/benchmark.h>

#include <vector>
#include <random>

using namespace naive;

// File-local; mirrors make_vecs from bench_vec4.cpp with the same seed,
// so the naive and tenvex benchmarks run on identical input data.
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

static std::vector<vec4> make_points(int n, unsigned seed)
{
	std::mt19937 rng(seed);
	std::uniform_real_distribution<float> d(-1.0f, 1.0f);
	std::vector<vec4> v;
	v.reserve(n);
	for (int i = 0; i < n; ++i)
		v.push_back(vec4{ d(rng), d(rng), d(rng), 1.0f });
	return v;
}

static void BM_Naive_Dot3_Latency(benchmark::State& state)
{
	vec4 a { 1.0f, 2.0f, 3.0f, 0.0f };
	vec4 b { 0.5f, 0.5f, 0.5f, 0.0f };
	float acc = 0.0f;
	for (auto _ : state)
	{
		vec4 bb = b + vec4 { acc, 0.0f, 0.0f, 0.0f };
		float d = dot3(a, bb);
		acc = d * 1e-7f;
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_Naive_Dot3_Latency);

static void BM_Naive_Norm3_Latency(benchmark::State& state)
{
	vec4 v { 1.0f, 2.0f, 3.0f, 1.0f };
	for (auto _ : state)
	{
		v = normalize3(v) + vec4 { 1e-3f, 2e-3f, 3e-3f, 0.0f };
		benchmark::DoNotOptimize(v);
	}
}
BENCHMARK(BM_Naive_Norm3_Latency);

static void BM_Naive_Dot3_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i], bb = b[i];
		float d = dot3(aa, bb);
		benchmark::DoNotOptimize(d);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Dot3_Throughput);

static void BM_Naive_Compound(benchmark::State& state)
{
	const auto va = make_vecs(1024, 1);
	const auto vb = make_vecs(1024, 2);
	const auto vc = make_vecs(1024, 3);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 a = va[i], b = vb[i], c = vc[i];
		vec4 r = normalize3(a + b * 2.0f) * dot3(b, c) + c * 3.0f;
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Compound);

static void BM_Naive_FacingSameWay(benchmark::State& state)
{
	vec4 fa = normalize3(vec4 { 1.0f, 0.0f, 0.2f, 0.0f });
	vec4 fb = vec4 { 0.9f, 0.1f, 0.1f, 0.0f };
	float jitter = 0.0f;
	for (auto _ : state)
	{
		vec4 f = normalize3(fb + vec4 { jitter, 0.0f, 0.0f, 0.0f });
		float c = dot3(fa, f);
		bool same = c > 0.95f;
		jitter = c * 1e-6f;
		benchmark::DoNotOptimize(same);
	}
}
BENCHMARK(BM_Naive_FacingSameWay);

static void BM_Naive_Dot4_Latency(benchmark::State& state)
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
BENCHMARK(BM_Naive_Dot4_Latency);

static void BM_Naive_Dot4_Throughput(benchmark::State& state)
{
	const auto a = make_points(1024, 1);
	const auto b = make_points(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i], bb = b[i];
		float d = dot4(aa, bb);
		benchmark::DoNotOptimize(d);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Dot4_Throughput);

static void BM_Naive_Min_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i], bb = b[i];
		vec4 r = min(aa, bb);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Min_Throughput);

static void BM_Naive_Max_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i], bb = b[i];
		vec4 r = max(aa, bb);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Max_Throughput);

static void BM_Naive_AABB_Latency(benchmark::State& state)
{
	const auto pts = make_vecs(1024, 1);
	vec4 lo {  1e30f,  1e30f,  1e30f, 0.0f };
	vec4 hi { -1e30f, -1e30f, -1e30f, 0.0f };
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 vtx = pts[i];
		lo = min(lo, vtx);
		hi = max(hi, vtx);
		i = (i + 1) & 1023;
	}
	benchmark::DoNotOptimize(lo);
	benchmark::DoNotOptimize(hi);
}
BENCHMARK(BM_Naive_AABB_Latency);

static void BM_Naive_Abs_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i];
		vec4 r = abs(aa);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Abs_Throughput);

static void BM_Naive_Abs_Latency(benchmark::State& state)
{
	vec4 v { -1.0f, 2.0f, -3.0f, 4.0f };
	for (auto _ : state)
	{
		v = abs(v - vec4 { 0.5f, 0.5f, 0.5f, 0.5f });
		benchmark::DoNotOptimize(v);
	}
}
BENCHMARK(BM_Naive_Abs_Latency);

static void BM_Naive_Clamp_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const vec4 lo { 0.0f, 0.0f, 0.0f, 0.0f };
	const vec4 hi { 1.0f, 1.0f, 1.0f, 1.0f };
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i];
		vec4 r = clamp(aa, lo, hi);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Clamp_Throughput);

static void BM_Naive_Clamp_Latency(benchmark::State& state)
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
BENCHMARK(BM_Naive_Clamp_Latency);

static void BM_Naive_Saturate_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i];
		vec4 r = saturate(aa);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Saturate_Throughput);

static void BM_Naive_Lerp_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 av = a[i], bv = b[i];
		vec4 r = lerp(av, bv, 0.35f);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Lerp_Throughput);

static void BM_Naive_Lerp_Latency(benchmark::State& state)
{
	vec4 v { 0.0f, 0.0f, 0.0f, 0.0f };
	const vec4 target { 1.0f, 2.0f, 3.0f, 0.0f };
	for (auto _ : state)
	{
		v = lerp(v, target, 0.25f);
		benchmark::DoNotOptimize(v);
	}
}
BENCHMARK(BM_Naive_Lerp_Latency);

static void BM_Naive_Dist3_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i], bb = b[i];
		float r = distance3(aa, bb);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Dist3_Throughput);

static void BM_Naive_Dist3Sq_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i], bb = b[i];
		float r = distance3_sq(aa, bb);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Dist3Sq_Throughput);

static void BM_Naive_Reflect_Throughput(benchmark::State& state)
{
	const auto v = make_vecs(1024, 1);
	const auto n = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 vv = v[i], nv = n[i];
		vec4 r = reflect(vv, nv);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Reflect_Throughput);

static void BM_Naive_Reflect_Latency(benchmark::State& state)
{
	vec4 v { 1.0f, -1.0f, 0.5f, 0.0f };
	const vec4 n { 0.0f, 1.0f, 0.0f, 0.0f };
	for (auto _ : state)
	{
		v = reflect(v, n);
		benchmark::DoNotOptimize(v);
	}
}
BENCHMARK(BM_Naive_Reflect_Latency);

static void BM_Naive_Floor_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i];
		vec4 r = floor(aa);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Floor_Throughput);

static void BM_Naive_Ceil_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i];
		vec4 r = ceil(aa);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Ceil_Throughput);

static void BM_Naive_Round_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i];
		vec4 r = round(aa);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Round_Throughput);

static void BM_Naive_Frac_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i];
		vec4 r = frac(aa);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Frac_Throughput);

static void BM_Naive_Hadamard_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i], bb = b[i];
		vec4 r = hadamard(aa, bb);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Hadamard_Throughput);

static void BM_Naive_Hadamard_Latency(benchmark::State& state)
{
	vec4 v { 1.001f, 0.999f, 1.0f, 1.0f };
	const vec4 k { 0.9999f, 1.0001f, 1.0f, 1.0f };
	for (auto _ : state)
	{
		v = hadamard(v, k);
		benchmark::DoNotOptimize(v);
	}
}
BENCHMARK(BM_Naive_Hadamard_Latency);

static void BM_Naive_MagLess_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i], bb = b[i];
		bool r = magnitude3(aa) < magnitude3(bb);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_MagLess_Throughput);

static void BM_Naive_MagLessConst_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const float radius = 0.75f;
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i];
		bool r = magnitude3(aa) < radius;
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_MagLessConst_Throughput);

static void BM_Naive_MagLess_Latency(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i], bb = b[i];
		bool closer = magnitude3(aa) < magnitude3(bb);
		i = (i + (closer ? 1u : 3u)) & 1023;
		benchmark::DoNotOptimize(i);
	}
}
BENCHMARK(BM_Naive_MagLess_Latency);

static void BM_Naive_Cross3_Latency(benchmark::State& state)
{
	vec4 v { 1.0f, 0.0f, 0.0f, 0.0f };
	vec4 k { 0.0f, 1.0f, 0.0f, 0.0f };
	for (auto _ : state)
	{
		v = cross3(v, k) + vec4 { 1e-3f, 2e-3f, 3e-3f, 0.0f };
		benchmark::DoNotOptimize(v);
	}
}
BENCHMARK(BM_Naive_Cross3_Latency);

static void BM_Naive_Cross3_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	const auto b = make_vecs(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i], bb = b[i];
		vec4 r = cross3(aa, bb);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Cross3_Throughput);

static void BM_Naive_Norm3_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i];
		vec4 r = normalize3(aa);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Norm3_Throughput);

static void BM_Naive_Magnitude4_Latency(benchmark::State& state)
{
	vec4 a { 1.0f, 2.0f, 3.0f, 4.0f };
	float acc = 0.0f;
	for (auto _ : state)
	{
		vec4 aa = a + vec4 { acc, 0.0f, 0.0f, 0.0f };
		float m = magnitude4(aa);
		acc = m * 1e-7f;
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_Naive_Magnitude4_Latency);

static void BM_Naive_Magnitude4_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i];
		float m = magnitude4(aa);
		benchmark::DoNotOptimize(m);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Magnitude4_Throughput);

static void BM_Naive_Magnitude4Sq_Latency(benchmark::State& state)
{
	vec4 a { 1.0f, 2.0f, 3.0f, 4.0f };
	float acc = 0.0f;
	for (auto _ : state)
	{
		vec4 aa = a + vec4 { acc, 0.0f, 0.0f, 0.0f };
		float m = magnitude4_sq(aa);
		acc = m * 1e-7f;
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_Naive_Magnitude4Sq_Latency);

static void BM_Naive_Magnitude4Sq_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i];
		float m = magnitude4_sq(aa);
		benchmark::DoNotOptimize(m);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Magnitude4Sq_Throughput);
