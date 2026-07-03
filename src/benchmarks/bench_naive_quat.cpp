#include "naive_quat.h"

#include <benchmark/benchmark.h>

#include <vector>
#include <random>

using namespace naive;

// File-local; mirrors make_quats in bench_quat.cpp with the same seeds,
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

// =====================================================================
// THROUGHPUT: independent iterations. quat add/sub/mul are single
// element-wise SIMD ops (addps / subps / mulps) that the compiler
// auto-vectorises anyway, so tenvex and naive come out byte-identical:
// this is a zero-cost confirmation, not an advantage benchmark.
// Leaves are bound to named locals (GCC/aarch64 SROA discipline).
// =====================================================================

static void BM_Naive_QuatAdd_Throughput(benchmark::State& state)
{
	const auto a = make_quats(1024, 1);
	const auto b = make_quats(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat aa = a[i], bb = b[i];
		quat r = aa + bb;
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_QuatAdd_Throughput);

static void BM_Naive_QuatSub_Throughput(benchmark::State& state)
{
	const auto a = make_quats(1024, 1);
	const auto b = make_quats(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat aa = a[i], bb = b[i];
		quat r = aa - bb;
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_QuatSub_Throughput);

static void BM_Naive_QuatMul_Throughput(benchmark::State& state)
{
	const auto a = make_quats(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat aa = a[i];
		quat r = aa * 2.0f;
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_QuatMul_Throughput);

static void BM_Naive_QuatHamilton_Throughput(benchmark::State& state)
{
	const auto a = make_quats(1024, 1);
	const auto b = make_quats(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat aa = a[i], bb = b[i];
		quat r = aa * bb;
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_QuatHamilton_Throughput);