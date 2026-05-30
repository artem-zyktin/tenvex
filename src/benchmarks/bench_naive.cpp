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
		v = norm3(v) + vec4 { 1e-3f, 2e-3f, 3e-3f, 0.0f };
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
		float d = dot3(a[i], b[i]);
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
		vec4 r = norm3(va[i] + vb[i] * 2.0f) * dot3(vb[i], vc[i]) + vc[i] * 3.0f;
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_Compound);

static void BM_Naive_FacingSameWay(benchmark::State& state)
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
BENCHMARK(BM_Naive_FacingSameWay);
