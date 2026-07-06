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

static void BM_Naive_QuatConj_Throughput(benchmark::State& state)
{
	const auto a = make_quats(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat qq = a[i];
		quat r = conj(qq);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_QuatConj_Throughput);

static void BM_Naive_QuatRotate_Throughput(benchmark::State& state)
{
	const auto qs = make_quats(1024, 1);
	const auto vs = make_vecs(1024, 3);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat qq = qs[i];
		vec4 vv = vs[i];
		quat pv = { vv.x(), vv.y(), vv.z(), 0.0f };
		quat r = (qq * pv) * conj(qq);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_QuatRotate_Throughput);

static void BM_Naive_QuatDot4_Latency(benchmark::State& state)
{
	quat a { 1.0f, 2.0f, 3.0f, 4.0f };
	quat b { 0.5f, 0.5f, 0.5f, 0.5f };
	float acc = 0.0f;
	for (auto _ : state)
	{
		quat bb = b + quat { acc, 0.0f, 0.0f, 0.0f };
		float d = dot4(a, bb);
		acc = d * 1e-7f;
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_Naive_QuatDot4_Latency);

static void BM_Naive_QuatDot4_Throughput(benchmark::State& state)
{
	const auto a = make_quats(1024, 1);
	const auto b = make_quats(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat aa = a[i], bb = b[i];
		float d = dot4(aa, bb);
		benchmark::DoNotOptimize(d);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_QuatDot4_Throughput);

static void BM_Naive_QuatMagnitude4_Latency(benchmark::State& state)
{
	quat a { 1.0f, 2.0f, 3.0f, 4.0f };
	float acc = 0.0f;
	for (auto _ : state)
	{
		quat aa = a + quat { acc, 0.0f, 0.0f, 0.0f };
		float m = magnitude4(aa);
		acc = m * 1e-7f;
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_Naive_QuatMagnitude4_Latency);

static void BM_Naive_QuatMagnitude4_Throughput(benchmark::State& state)
{
	const auto a = make_quats(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat aa = a[i];
		float m = magnitude4(aa);
		benchmark::DoNotOptimize(m);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_QuatMagnitude4_Throughput);

static void BM_Naive_QuatMagnitude4Sq_Latency(benchmark::State& state)
{
	quat a { 1.0f, 2.0f, 3.0f, 4.0f };
	float acc = 0.0f;
	for (auto _ : state)
	{
		quat aa = a + quat { acc, 0.0f, 0.0f, 0.0f };
		float m = magnitude4_sq(aa);
		acc = m * 1e-7f;
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_Naive_QuatMagnitude4Sq_Latency);

static void BM_Naive_QuatMagnitude4Sq_Throughput(benchmark::State& state)
{
	const auto a = make_quats(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat aa = a[i];
		float m = magnitude4_sq(aa);
		benchmark::DoNotOptimize(m);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_QuatMagnitude4Sq_Throughput);

static void BM_Naive_QuatInverse_Latency(benchmark::State& state)
{
	quat a { 1.0f, 2.0f, 3.0f, 4.0f };
	float acc = 0.0f;
	for (auto _ : state)
	{
		quat aa = a + quat { acc, 0.0f, 0.0f, 0.0f };
		quat r = inverse(aa);
		acc = r.x() * 1e-7f;
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_Naive_QuatInverse_Latency);

static void BM_Naive_QuatInverse_Throughput(benchmark::State& state)
{
	const auto a = make_quats(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat qq = a[i];
		quat r = inverse(qq);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_QuatInverse_Throughput);

static void BM_Naive_QuatNormalize_Latency(benchmark::State& state)
{
	quat a { 1.0f, 2.0f, 3.0f, 4.0f };
	float acc = 0.0f;
	for (auto _ : state)
	{
		quat aa = a + quat { acc, 0.0f, 0.0f, 0.0f };
		quat r = normalize(aa);
		acc = r.x() * 1e-7f;
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_Naive_QuatNormalize_Latency);

static void BM_Naive_QuatNormalize_Throughput(benchmark::State& state)
{
	const auto a = make_quats(1024, 1);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat qq = a[i];
		quat r = normalize(qq);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_QuatNormalize_Throughput);

static void BM_Naive_QuatSlerp_Latency(benchmark::State& state)
{
	quat a = normalize(quat { 1.0f, 2.0f, 3.0f, 4.0f });
	quat b = normalize(quat { 4.0f, 3.0f, 2.0f, 1.0f });
	float acc = 0.0f;
	for (auto _ : state)
	{
		quat aa = normalize(a + quat { acc, 0.0f, 0.0f, 0.0f });
		quat r = slerp(aa, b, 0.5f);
		acc = r.x() * 1e-7f;
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_Naive_QuatSlerp_Latency);

static void BM_Naive_QuatSlerp_Throughput(benchmark::State& state)
{
	auto a = make_quats(1024, 1);
	auto b = make_quats(1024, 2);
	for (auto& q : a) q = normalize(q);
	for (auto& q : b) q = normalize(q);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat aa = a[i];
		quat bb = b[i];
		quat r = slerp(aa, bb, 0.5f);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_QuatSlerp_Throughput);

static void BM_Naive_QuatNlerp_Latency(benchmark::State& state)
{
	quat a { 1.0f, 2.0f, 3.0f, 4.0f };
	quat b { 4.0f, 3.0f, 2.0f, 1.0f };
	float acc = 0.0f;
	for (auto _ : state)
	{
		quat aa = a + quat { acc, 0.0f, 0.0f, 0.0f };
		quat r = nlerp(aa, b, 0.5f);
		acc = r.x() * 1e-7f;
		benchmark::DoNotOptimize(acc);
	}
}
BENCHMARK(BM_Naive_QuatNlerp_Latency);

static void BM_Naive_QuatNlerp_Throughput(benchmark::State& state)
{
	const auto a = make_quats(1024, 1);
	const auto b = make_quats(1024, 2);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat aa = a[i];
		quat bb = b[i];
		quat r = nlerp(aa, bb, 0.5f);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_Naive_QuatNlerp_Throughput);
