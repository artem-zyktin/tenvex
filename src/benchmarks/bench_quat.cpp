#include "tenvex.h"

#include <benchmark/benchmark.h>

#include <vector>
#include <random>

using namespace tnvx;

// File-local; mirrors make_quats in bench_naive_quat.cpp with the same seeds,
// so the tenvex and naive benchmarks run on identical input data. All four
// lanes vary (unlike vec4's w=0) so nothing folds to a constant.
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

static void BM_QuatAdd_Throughput(benchmark::State& state)
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
BENCHMARK(BM_QuatAdd_Throughput);

static void BM_QuatSub_Throughput(benchmark::State& state)
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
BENCHMARK(BM_QuatSub_Throughput);

static void BM_QuatMul_Throughput(benchmark::State& state)
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
BENCHMARK(BM_QuatMul_Throughput);

static void BM_QuatHamilton_Throughput(benchmark::State& state)
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
BENCHMARK(BM_QuatHamilton_Throughput);

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

// conj is a single xorps - like the add/sub/mul quat benches this is a
// zero-cost confirmation, not an advantage benchmark.
static void BM_QuatConj_Throughput(benchmark::State& state)
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
BENCHMARK(BM_QuatConj_Throughput);

// rotate(v, q) = the sandwich q * v * conj(q). tenvex fuses it into one node;
// rotate() is a vec_expr, so bind the result to a concrete vec4.
static void BM_QuatRotate_Throughput(benchmark::State& state)
{
	const auto qs = make_quats(1024, 1);
	const auto vs = make_vecs(1024, 3);
	std::size_t i = 0;
	for (auto _ : state)
	{
		quat qq = qs[i];
		vec4 vv = vs[i];
		vec4 r = rotate(vv, qq);
		benchmark::DoNotOptimize(r);
		i = (i + 1) & 1023;
	}
}
BENCHMARK(BM_QuatRotate_Throughput);

// dot4 collapses a quaternion pair to a scalar. Same node as vec4's dot4
// (shared via dot4_operands); this is the quaternion instantiation.
static void BM_QuatDot4_Latency(benchmark::State& state)
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
BENCHMARK(BM_QuatDot4_Latency);

static void BM_QuatDot4_Throughput(benchmark::State& state)
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
BENCHMARK(BM_QuatDot4_Throughput);

// magnitude4 on quaternions: same reduction node as vec4, quat instantiation.
static void BM_QuatMagnitude4_Latency(benchmark::State& state)
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
BENCHMARK(BM_QuatMagnitude4_Latency);

static void BM_QuatMagnitude4_Throughput(benchmark::State& state)
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
BENCHMARK(BM_QuatMagnitude4_Throughput);

static void BM_QuatMagnitude4Sq_Latency(benchmark::State& state)
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
BENCHMARK(BM_QuatMagnitude4Sq_Latency);

static void BM_QuatMagnitude4Sq_Throughput(benchmark::State& state)
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
BENCHMARK(BM_QuatMagnitude4Sq_Throughput);

// inverse = conj(q) / magnitude4_sq(q): a reduction + div, no sqrt.
static void BM_QuatInverse_Latency(benchmark::State& state)
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
BENCHMARK(BM_QuatInverse_Latency);

static void BM_QuatInverse_Throughput(benchmark::State& state)
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
BENCHMARK(BM_QuatInverse_Throughput);

static void BM_QuatNormalize_Latency(benchmark::State& state)
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
BENCHMARK(BM_QuatNormalize_Latency);

static void BM_QuatNormalize_Throughput(benchmark::State& state)
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
BENCHMARK(BM_QuatNormalize_Throughput);
