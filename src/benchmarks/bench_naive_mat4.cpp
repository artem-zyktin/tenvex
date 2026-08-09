#include "naive/naive_mat4.h"

#include <benchmark/benchmark.h>

#include <vector>
#include <random>

using namespace naive;

// File-local; mirrors the generators in bench_mat4.cpp with the same seeds,
// so the naive and tenvex benchmarks run on identical input data.
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

// =====================================================================
// THROUGHPUT ONLY, mirroring bench_mat4.cpp: see the note there on why a
// latency chain through one lane would under-measure a 64-byte result.
// =====================================================================

static void BM_Naive_MatFromQuat_Throughput(benchmark::State& state)
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
BENCHMARK(BM_Naive_MatFromQuat_Throughput);

static void BM_Naive_MatFromRotation_Throughput(benchmark::State& state)
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
BENCHMARK(BM_Naive_MatFromRotation_Throughput);

static void BM_Naive_MatTranslation_Throughput(benchmark::State& state)
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
BENCHMARK(BM_Naive_MatTranslation_Throughput);

static void BM_Naive_MatScalingVec_Throughput(benchmark::State& state)
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
BENCHMARK(BM_Naive_MatScalingVec_Throughput);

static void BM_Naive_MatScalingScalar_Throughput(benchmark::State& state)
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
BENCHMARK(BM_Naive_MatScalingScalar_Throughput);

static void BM_Naive_MatAt_Throughput(benchmark::State& state)
{
	const auto m = make_mats(1024, 9);
	std::size_t i = 0;
	for (auto _ : state)
	{
		mat4 mm = m[i];
		float f = mm.at(2, 1);
		benchmark::DoNotOptimize(f);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_MatAt_Throughput);
