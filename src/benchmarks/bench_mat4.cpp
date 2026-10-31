#include "tenvex/tenvex.h"

#include <benchmark/benchmark.h>

#include <vector>
#include <random>

using namespace tnvx;

static std::vector<quat> make_quats(int n, unsigned seed)
{
	std::mt19937 rng(seed);
	std::uniform_real_distribution<float> d(-1.0f, 1.0f);
	std::vector<quat> v;
	v.reserve(n);
	for (int i = 0; i < n; ++i)
		v.push_back(quat { d(rng), d(rng), d(rng), d(rng) });
	return v;
}

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

static std::vector<float> make_floats(int n, unsigned seed)
{
	std::mt19937 rng(seed);
	std::uniform_real_distribution<float> d(-1.0f, 1.0f);
	std::vector<float> v;
	v.reserve(n);
	for (int i = 0; i < n; ++i)
		v.push_back(d(rng));
	return v;
}

static std::vector<mat4> make_mats(int n, unsigned seed)
{
	const auto c = make_vecs(4 * n, seed);
	std::vector<mat4> v;
	v.reserve(n);
	for (int i = 0; i < n; ++i)
		v.push_back(mat4 { c[4 * i], c[4 * i + 1], c[4 * i + 2], c[4 * i + 3] });
	return v;
}

static void BM_MatFromQuat_Throughput(benchmark::State& state)
{
	const auto q = make_quats(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat qq = q[i];
		mat4 r = mat4::from_quat(qq);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_MatFromQuat_Throughput);

static void BM_MatFromRotation_Throughput(benchmark::State& state)
{
	const auto a = make_vecs(1024, 3);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 aa = a[i];
		mat4 r = mat4::from_rotation(aa, 1.0471975f);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_MatFromRotation_Throughput);

static void BM_MatTranslation_Throughput(benchmark::State& state)
{
	const auto t = make_vecs(1024, 4);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 tt = t[i];
		mat4 r = mat4::translation(tt);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_MatTranslation_Throughput);

static void BM_MatScalingVec_Throughput(benchmark::State& state)
{
	const auto s = make_vecs(1024, 5);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 ss = s[i];
		mat4 r = mat4::scaling(ss);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_MatScalingVec_Throughput);

static void BM_MatScalingScalar_Throughput(benchmark::State& state)
{
	const auto sx = make_floats(1024, 6);
	const auto sy = make_floats(1024, 7);
	const auto sz = make_floats(1024, 8);
	std::size_t i = 0;
	for (auto _ : state)
	{
		float x = sx[i], y = sy[i], z = sz[i];
		mat4 r = mat4::scaling(x, y, z);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_MatScalingScalar_Throughput);

static void BM_MatAt_Throughput(benchmark::State& state)
{
	const auto m = make_mats(1024, 9);
	std::size_t i = 0;
	for (auto _ : state)
	{
		mat4 mm = m[i];
		float f = mm.at<2, 1>();
		benchmark::DoNotOptimize(f);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_MatAt_Throughput);

// =====================================================================
// THROUGHPUT: independent iterations over the matrix operations. M * v
// is the linear-combination kernel the column-major layout is chosen
// for; the element-wise add / scale are four SIMD ops the compiler
// auto-vectorises anyway, so those confirm zero cost rather than show a
// win. Leaves are bound to named locals (GCC/aarch64 SROA discipline).
// =====================================================================

static void BM_MatTransform_Throughput(benchmark::State& state)
{
	const auto m = make_mats(256, 9);
	const auto v = make_vecs(256, 10);
	std::size_t i = 0;
	for (auto _ : state)
	{
		const mat4& mm = m[i];
		vec4 vv = v[i];
		vec4 r = mm * vv;
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 255;
	}
}
BENCHMARK(BM_MatTransform_Throughput);

static void BM_MatMul_Throughput(benchmark::State& state)
{
	const auto a = make_mats(256, 9);
	const auto b = make_mats(256, 11);
	std::size_t i = 0;
	for (auto _ : state)
	{
		const mat4& aa = a[i];
		const mat4& bb = b[i];
		mat4 r = aa * bb;
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 255;
	}
}
BENCHMARK(BM_MatMul_Throughput);

static void BM_MatTranspose_Throughput(benchmark::State& state)
{
	const auto m = make_mats(256, 9);
	std::size_t i = 0;
	for (auto _ : state)
	{
		const mat4& mm = m[i];
		mat4 r = transpose(mm);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 255;
	}
}
BENCHMARK(BM_MatTranspose_Throughput);

static void BM_MatDeterminant_Throughput(benchmark::State& state)
{
	const auto m = make_mats(256, 9);
	std::size_t i = 0;
	for (auto _ : state)
	{
		const mat4& mm = m[i];
		float d = determinant(mm);
		benchmark::DoNotOptimize(d);
		i = (i + 1) & 255;
	}
}
BENCHMARK(BM_MatDeterminant_Throughput);

static void BM_MatInverse_Throughput(benchmark::State& state)
{
	const auto m = make_mats(256, 9);
	std::size_t i = 0;
	for (auto _ : state)
	{
		const mat4& mm = m[i];
		mat4 r = inverse(mm);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 255;
	}
}
BENCHMARK(BM_MatInverse_Throughput);

static void BM_MatAdd_Throughput(benchmark::State& state)
{
	const auto a = make_mats(256, 9);
	const auto b = make_mats(256, 11);
	std::size_t i = 0;
	for (auto _ : state)
	{
		const mat4& aa = a[i];
		const mat4& bb = b[i];
		mat4 r = aa + bb;
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 255;
	}
}
BENCHMARK(BM_MatAdd_Throughput);

static void BM_MatScale_Throughput(benchmark::State& state)
{
	const auto m = make_mats(256, 9);
	std::size_t i = 0;
	for (auto _ : state)
	{
		const mat4& mm = m[i];
		mat4 r = mm * 2.0f;
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 255;
	}
}
BENCHMARK(BM_MatScale_Throughput);

// The shape a renderer actually writes: build T * R * S and push a point
// through it in one statement.
static void BM_MatCompose_Throughput(benchmark::State& state)
{
	const auto t = make_vecs(256, 10);
	const auto q = make_quats(256, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		vec4 tt = t[i];
		quat qq = q[i];
		mat4 model = mat4::translation(tt) * mat4(mat4::from_quat(qq) * mat4::scaling(2.0f));
		vec4 r = model * tt;
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 255;
	}
}
BENCHMARK(BM_MatCompose_Throughput);

// =====================================================================
// LATENCY: each iteration depends on the previous result, so the chain
// length rather than the issue rate decides the time. The feedback
// operand is a small rotation (orthonormal, so the values stay bounded
// over a long run) or the result itself.
// =====================================================================

static void BM_MatTransform_Latency(benchmark::State& state)
{
	const mat4 r = mat4::from_rotation(vec4 { 0.3f, 0.5f, -0.8f, 0.0f }, 0.01f);
	vec4 v = { 1.0f, 2.0f, 3.0f, 1.0f };
	for (auto _ : state)
	{
		v = r * v;
		benchmark::DoNotOptimize(v);
	}
}
BENCHMARK(BM_MatTransform_Latency);

static void BM_MatMul_Latency(benchmark::State& state)
{
	const mat4 r = mat4::from_rotation(vec4 { 0.3f, 0.5f, -0.8f, 0.0f }, 0.01f);
	mat4 acc = mat4::identity();
	for (auto _ : state)
	{
		acc = acc * r;
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_MatMul_Latency);

static void BM_MatTranspose_Latency(benchmark::State& state)
{
	mat4 acc = mat4::from_rotation(vec4 { 0.3f, 0.5f, -0.8f, 0.0f }, 0.01f);
	for (auto _ : state)
	{
		acc = transpose(acc);
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_MatTranspose_Latency);

// determinant collapses the four columns to a broadcast scalar; the chain
// runs back through one leaf lane, as the quaternion reductions do.
static void BM_MatDeterminant_Latency(benchmark::State& state)
{
	const auto m = make_mats(1, 9);
	const mat4 a = m[0];
	float acc = 0.0f;
	for (auto _ : state)
	{
		mat4 aa = a + mat4::scaling(acc);
		float d = determinant(aa);
		acc = d * 1e-7f;
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_MatDeterminant_Latency);

static void BM_MatInverse_Latency(benchmark::State& state)
{
	mat4 acc = mat4::translation(1.0f, 2.0f, 3.0f)
			   * mat4::from_rotation(vec4 { 0.3f, 0.5f, -0.8f, 0.0f }, 0.01f);
	for (auto _ : state)
	{
		acc = inverse(acc);
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_MatInverse_Latency);
