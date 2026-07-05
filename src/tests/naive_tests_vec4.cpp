#include "naive_vec4.h"

#include "gtest/gtest.h"

#include <cmath>

namespace naive
{

TEST(naive_vec4, add)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 b = { 4.0f, 3.0f, 2.0f, 1.0f };
	vec4 check = { 5.0f, 5.0f, 5.0f, 5.0f };
	vec4 result = a + b;

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, mixed_type_add)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 0.0f };
	vec4 b = { 1.0f, 1.0f, 1.0f, 0.0f };
	vec4 c = { 2.0f, 0.0f, 0.0f, 0.0f };
	vec4 check = { 4.0f, 3.0f, 4.0f, 0.0f };

	vec4 result = a + b + c;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, sub)
{
	vec4 a = { 5.0f, 5.0f, 5.0f, 5.0f };
	vec4 b = { 4.0f, 3.0f, 2.0f, 1.0f };
	vec4 check = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 result = a - b;

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, mult_a)
{
	vec4 a = { 1.0f, 2.0f, 0.0f, 0.0f };
	float b = 3.0f;
	vec4 check = { 3.0f, 6.0f, 0.0f, 0.0f };
	vec4 result = a * b;

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, mult_b)
{
	float a = 2.0f;
	vec4 b = { 1.0f, 0.0f, 2.0f, 0.0f };
	vec4 check = { 2.0f, 0.0f, 4.0f, 0.0f };
	vec4 result = a * b;

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, div)
{
	vec4 a = { 3.0f, 6.0f, 0.0f, 0.0f };
	float b = 3.0f;
	vec4 check = { 1.0f, 2.0f, 0.0f, 0.0f };
	vec4 result = a / b;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, dot3)
{
	vec4 a = { 1.0f, 0.0f, 3.0f, 1.0f };
	vec4 b = { 1.0f, 2.0f, 3.0f, 4.0f };
	float check = 10.0f;
	float result = dot3(a, b);

	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_vec4, cross)
{
	vec4 a = { 1.0f, 0.0f, 0.0f, 0.0f };
	vec4 b = { 0.0f, 1.0f, 0.0f, 0.0f };
	vec4 check = { 0.0f, 0.0f, 1.0f, 0.0f };
	vec4 result = cross3(a, b);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, norm_a)
{
	vec4 a = { 1.0f, 0.0f, 0.0f, 1.0f };
	vec4 check = { 1.0f, 0.0f, 0.0f, 1.0f };
	vec4 result = norm3(a);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, norm_b)
{
	vec4 a = { 1.0f, 0.0f, 1.0f, 1.0f };
	vec4 check = { 0.707106f, 0.0f, 0.707106f, 1.0f };
	vec4 result = norm3(a);

	EXPECT_TRUE(approx_eq(check, result, 1e-3f));
}

TEST(naive_vec4, magnitude_a)
{
	vec4 a = { 1.0f, 0.0f, 0.0f, 0.0f };
	float check = 1.0f;
	float result = magnitude3(a);

	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_vec4, magnitude_b)
{
	vec4 a = { 1.0f, 0.0f, 1.0f, 0.0f };
	float check = 1.4142135f;
	float result = magnitude3(a);

	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_vec4, magnitude3_sq_a)
{
	vec4 a = { 1.0f, 0.0f, 0.0f, 0.0f };
	float check = 1.0f;
	float result = magnitude3_sq(a);

	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_vec4, magnitude3_sq_b)
{
	vec4 a = { 1.0f, 0.0f, 1.0f, 1.0f };
	float check = 2.0f;
	float result = magnitude3_sq(a);

	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_vec4, expression_a)
{
	vec4 a = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4 b = { 0.0f, 1.0f, 0.0f, 3.0f };
	vec4 c = { 1.15f, 0.0f, 11.0f, 0.0f };

	vec4 check = { 3.45f, 0.0f, 33.0f, 0.0f };

	vec4 result = dot3(a, b) * 3.0f * c;

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, expression_b)
{
	vec4 a = { 1.0f, 1.0f, 1.0f, 0.0f };
	vec4 b = { 0.0f, 1.0f, 0.0f, 0.0f };
	vec4 c = { 1.15f, 0.0f, 11.0f, 0.0f };

	vec4 check = { 33.0f, 0.0f, -3.45f, 0.0f };

	vec4 result = dot3(a, b) * 3.0f * cross3(b, c);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, expression_c)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 0.0f };
	vec4 b = { 4.0f, 5.0f, 6.0f, 0.0f };
	vec4 c = { 1.0f, 0.0f, 1.0f, 0.0f };

	vec4 check = { 7.24264050f, 5.65685463f, 10.0710678f, 0.0f };

	vec4 tmp1 = norm3(a + b * 2.0f) * dot3(b, c);
	vec4 tmp2 = c * 3.0f;

	vec4 result = tmp1 + tmp2;

	EXPECT_TRUE(approx_eq(check, result, 1e-3f));
}

TEST(naive_vec4, expression_d)
{
	vec4 a = { 1.0f, 0.0f, 0.0f, 0.0f };
	vec4 b = { 0.0f, 2.0f, 0.0f, 0.0f };
	vec4 c = { 0.0f, 0.0f, 3.0f, 0.0f };
	vec4 result = (a + b) * 2.0f + c - a;
	vec4 check = { 1.0f, 4.0f, 3.0f, 0.0f };
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, expression_from_temporaries)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 0.0f };
	vec4 b = { 4.0f, 5.0f, 6.0f, 0.0f };
	vec4 check = { 2.0f, 4.0f, 6.0f, 0.0f };
	vec4 result = (a + b) + (a - b);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, cross_anticommutative)
{
	vec4 a = { 1.0f, 0.0f, 0.0f, 0.0f };
	vec4 b = { 0.0f, 1.0f, 0.0f, 0.0f };

	EXPECT_TRUE(approx_eq(cross3(a, b), cross3(b, a) * -1.0f));
}

TEST(naive_vec4, w_is_zero_with_nonzero_input_w)
{
	vec4 a = { 1.0f, 0.0f, 0.0f, 5.0f };
	vec4 b = { 0.0f, 1.0f, 0.0f, 7.0f };

	vec4 r = cross3(a, b);

	EXPECT_FLOAT_EQ(r.w(), 0.0f);
	EXPECT_FLOAT_EQ(r.z(), 1.0f);
}

TEST(naive_vec4, preserves_nontrivial_w)
{
	vec4 a = { 0.0f, 3.0f, 0.0f, 9.0f };
	vec4 r = norm3(a);

	EXPECT_FLOAT_EQ(r.y(), 1.0f);
	EXPECT_FLOAT_EQ(r.w(), 9.0f);
}

TEST(naive_vec4, dot_commutative)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 0.0f };
	vec4 b = { 4.0f, 5.0f, 6.0f, 0.0f };

	EXPECT_FLOAT_EQ(dot3(a, b), dot3(b, a));
}

TEST(naive_vec4, norm_magnitude)
{
	vec4 a = { 3.0f, 1.0f, 4.0f, 0.0f };

	EXPECT_NEAR(magnitude3(norm3(a)), 1.0f, 1e-6f);
}

TEST(naive_vec4, zero_vector_is_nan)
{
	vec4 z = { 0.0f, 0.0f, 0.0f, 0.0f };
	vec4 r = norm3(z);

	EXPECT_TRUE(std::isnan(r.x()));
}

TEST(naive_vec4, dot_perpendicular)
{
	vec4 a = { 1.0f, 0.0f, 0.0f, 0.0f };
	vec4 b = { 0.0f, 1.0f, 0.0f, 0.0f };

	EXPECT_FLOAT_EQ(dot3(a, b), 0.0f);
}

TEST(naive_vec4, cross_parallel)
{
	vec4 a = { 1.0f, 0.0f, 0.0f, 0.0f };
	vec4 b = { 2.0f, 0.0f, 0.0f, 0.0f };
	vec4 check = { 0.0f, 0.0f, 0.0f, 0.0f };

	EXPECT_TRUE(approx_eq(cross3(a, b), check));
}

TEST(naive_vec4, neg_basic)
{
	vec4 a = { 1.0f, -2.0f, 3.0f, -4.0f };
	vec4 check = { -1.0f, 2.0f, -3.0f, 4.0f };

	EXPECT_TRUE(approx_eq(-a, check));
}

TEST(naive_vec4, neg_zero)
{
	vec4 a = { 0.0f, 0.0f, 0.0f, 0.0f };

	EXPECT_TRUE(approx_eq(-a, a));
}

TEST(naive_vec4, neg_double)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 4.0f };

	EXPECT_TRUE(approx_eq(-(-a), a));
}

TEST(naive_vec4, neg_compound)
{
	vec4 a = { 5.0f, 3.0f, 1.0f, 0.0f };
	vec4 b = { 2.0f, 1.0f, 4.0f, 0.0f };

	EXPECT_TRUE(approx_eq(a + (-b), a - b));
}

TEST(naive_vec4, dot4_basic)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 b = { 1.0f, 2.0f, 3.0f, 4.0f };
	EXPECT_FLOAT_EQ(dot4(a, b), 30.0f);
}

TEST(naive_vec4, dot4_w_matters)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 b = { 1.0f, 2.0f, 3.0f, 4.0f };
	EXPECT_FLOAT_EQ(dot3(a, b), 14.0f);
	EXPECT_FLOAT_EQ(dot4(a, b), 30.0f);
}

TEST(naive_vec4, dot4_w_only)
{
	vec4 a = { 0.0f, 0.0f, 0.0f, 5.0f };
	vec4 b = { 0.0f, 0.0f, 0.0f, 3.0f };
	EXPECT_FLOAT_EQ(dot4(a, b), 15.0f);
}

TEST(naive_vec4, dot4_commutative)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 b = { 4.0f, 3.0f, 2.0f, 1.0f };
	EXPECT_FLOAT_EQ(dot4(a, b), dot4(b, a));
}

TEST(naive_vec4, dot4_w_zero_matches_dot3)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 0.0f };
	vec4 b = { 4.0f, 5.0f, 6.0f, 0.0f };
	EXPECT_FLOAT_EQ(dot4(a, b), dot3(a, b));
}

TEST(naive_vec4, min_basic)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 b = { 4.0f, 3.0f, 2.0f, 1.0f };
	vec4 check = { 1.0f, 2.0f, 2.0f, 1.0f };
	vec4 result = min(a, b);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, max_basic)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 b = { 4.0f, 3.0f, 2.0f, 1.0f };
	vec4 check = { 4.0f, 3.0f, 3.0f, 4.0f };
	vec4 result = max(a, b);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, min_negatives)
{
	vec4 a = { -1.0f, 5.0f, -3.0f, 2.0f };
	vec4 b = { 1.0f, -5.0f, 3.0f, -2.0f };
	vec4 check = { -1.0f, -5.0f, -3.0f, -2.0f };
	vec4 result = min(a, b);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, max_negatives)
{
	vec4 a = { -1.0f, 5.0f, -3.0f, 2.0f };
	vec4 b = { 1.0f, -5.0f, 3.0f, -2.0f };
	vec4 check = { 1.0f, 5.0f, 3.0f, 2.0f };
	vec4 result = max(a, b);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, min_includes_w)
{
	vec4 a = { 0.0f, 0.0f, 0.0f, 5.0f };
	vec4 b = { 0.0f, 0.0f, 0.0f, 3.0f };
	float check1 = 3.0f;
	float result1 = min(a, b).w();
	float check2 = 5.0f;
	float result2 = max(a, b).w();

	EXPECT_FLOAT_EQ(check1, result1);
	EXPECT_FLOAT_EQ(check2, result2);
}

TEST(naive_vec4, min_idempotent)
{
	vec4 a = { 1.0f, -2.0f, 3.0f, -4.0f };

	EXPECT_TRUE(approx_eq(min(a, a), a));
	EXPECT_TRUE(approx_eq(max(a, a), a));
}

TEST(naive_vec4, min_commutative)
{
	vec4 a = { 1.0f, 5.0f, -3.0f, 2.0f };
	vec4 b = { 4.0f, -5.0f, 3.0f, -2.0f };

	EXPECT_TRUE(approx_eq(min(a, b), min(b, a)));
	EXPECT_TRUE(approx_eq(max(a, b), max(b, a)));
}

TEST(naive_vec4, abs_basic)
{
	vec4 a = { -1.0f, 2.0f, -3.0f, 4.0f };
	vec4 check = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 result = abs(a);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, abs_all_negative)
{
	vec4 a = { -5.0f, -5.0f, -5.0f, -5.0f };
	vec4 check = { 5.0f, 5.0f, 5.0f, 5.0f };
	vec4 result = abs(a);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, abs_already_positive)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 result = abs(a);
	EXPECT_TRUE(approx_eq(a, result));
}

TEST(naive_vec4, abs_zero)
{
	vec4 a = { 0.0f, 0.0f, 0.0f, 0.0f };
	vec4 result = abs(a);
	EXPECT_TRUE(approx_eq(a, result));
}

TEST(naive_vec4, clamp_basic)
{
	vec4 v = { -2.0f, 0.5f, 5.0f, 0.0f };
	vec4 lo = { 0.0f, 0.0f, 0.0f, 0.0f };
	vec4 hi = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4 check = { 0.0f, 0.5f, 1.0f, 0.0f };
	vec4 result = clamp(v, lo, hi);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, clamp_custom_range)
{
	vec4 v = { 5.0f, 10.0f, 15.0f, 20.0f };
	vec4 lo = { 8.0f, 8.0f, 8.0f, 8.0f };
	vec4 hi = { 12.0f, 12.0f, 12.0f, 12.0f };
	vec4 check = { 8.0f, 10.0f, 12.0f, 12.0f };
	vec4 result = clamp(v, lo, hi);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, clamp_within_range)
{
	vec4 v = { 0.3f, 0.5f, 0.7f, 0.9f };
	vec4 lo = { 0.0f, 0.0f, 0.0f, 0.0f };
	vec4 hi = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4 result = clamp(v, lo, hi);
	EXPECT_TRUE(approx_eq(v, result));
}

TEST(naive_vec4, clamp_all_below)
{
	vec4 v = { -1.0f, -2.0f, -3.0f, -4.0f };
	vec4 lo = { 0.0f, 0.0f, 0.0f, 0.0f };
	vec4 hi = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4 result = clamp(v, lo, hi);
	EXPECT_TRUE(approx_eq(lo, result));
}

TEST(naive_vec4, clamp_all_above)
{
	vec4 v = { 5.0f, 6.0f, 7.0f, 8.0f };
	vec4 lo = { 0.0f, 0.0f, 0.0f, 0.0f };
	vec4 hi = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4 result = clamp(v, lo, hi);
	EXPECT_TRUE(approx_eq(hi, result));
}

TEST(naive_vec4, saturate_basic)
{
	vec4 v = { -0.5f, 0.3f, 1.5f, 0.0f };
	vec4 check = { 0.0f, 0.3f, 1.0f, 0.0f };
	vec4 result = saturate(v);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, saturate_within_range)
{
	vec4 v = { 0.1f, 0.5f, 0.9f, 0.0f };
	vec4 result = saturate(v);
	EXPECT_TRUE(approx_eq(v, result));
}

TEST(naive_vec4, saturate_clamps_negatives)
{
	vec4 v = { -1.0f, -2.0f, -3.0f, -4.0f };
	vec4 check = { 0.0f, 0.0f, 0.0f, 0.0f };
	vec4 result = saturate(v);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, saturate_clamps_above_one)
{
	vec4 v = { 2.0f, 3.0f, 4.0f, 5.0f };
	vec4 check = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4 result = saturate(v);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, lerp_at_zero)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 0.0f };
	vec4 b = { 5.0f, 6.0f, 7.0f, 0.0f };
	vec4 result = lerp(a, b, 0.0f);
	EXPECT_TRUE(approx_eq(a, result));
}

TEST(naive_vec4, lerp_at_one)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 0.0f };
	vec4 b = { 5.0f, 6.0f, 7.0f, 0.0f };
	vec4 result = lerp(a, b, 1.0f);
	EXPECT_TRUE(approx_eq(b, result));
}

TEST(naive_vec4, lerp_half)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 0.0f };
	vec4 b = { 5.0f, 6.0f, 7.0f, 0.0f };
	vec4 check = { 3.0f, 4.0f, 5.0f, 0.0f };
	vec4 result = lerp(a, b, 0.5f);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, dist3_basic)
{
	vec4 l = { 0.0f, 0.0f, 0.0f, 0.0f };
	vec4 r = { 3.0f, 4.0f, 0.0f, 0.0f };
	float check = 5.0f;
	float result = dist3(l, r);
	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_vec4, dist3_zero)
{
	vec4 l = { 1.0f, 2.0f, 3.0f, 0.0f };
	vec4 r = { 1.0f, 2.0f, 3.0f, 0.0f };
	float check = 0.0f;
	float result = dist3(l, r);
	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_vec4, dist3_ignores_w)
{
	vec4 l = { 0.0f, 0.0f, 0.0f, 100.0f };
	vec4 r = { 3.0f, 4.0f, 0.0f, -100.0f };
	float check = 5.0f;
	float result = dist3(l, r);
	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_vec4, dist3_sq_basic)
{
	vec4 l = { 0.0f, 0.0f, 0.0f, 0.0f };
	vec4 r = { 3.0f, 4.0f, 0.0f, 0.0f };
	float check = 25.0f;
	float result = dist3_sq(l, r);
	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_vec4, dist3_sq_zero)
{
	vec4 l = { 1.0f, 2.0f, 3.0f, 0.0f };
	vec4 r = { 1.0f, 2.0f, 3.0f, 0.0f };
	float check = 0.0f;
	float result = dist3_sq(l, r);
	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_vec4, reflect_off_horizontal)
{
	vec4 v = { 1.0f, -1.0f, 0.0f, 0.0f };
	vec4 n = { 0.0f, 1.0f, 0.0f, 0.0f };
	vec4 check = { 1.0f, 1.0f, 0.0f, 0.0f };
	vec4 result = reflect(v, n);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, reflect_scaled)
{
	vec4 v = { 3.0f, -4.0f, 0.0f, 0.0f };
	vec4 n = { 0.0f, 1.0f, 0.0f, 0.0f };
	vec4 check = { 3.0f, 4.0f, 0.0f, 0.0f };
	vec4 result = reflect(v, n);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, reflect_diagonal)
{
	const float s = 0.70710678f;
	vec4 v = { 1.0f, 0.0f, 0.0f, 0.0f };
	vec4 n = { s, s, 0.0f, 0.0f };
	vec4 check = { 0.0f, -1.0f, 0.0f, 0.0f };
	vec4 result = reflect(v, n);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, floor_basic)
{
	vec4 v = { 1.5f, -1.5f, 2.9f, -2.1f };
	vec4 check = { 1.0f, -2.0f, 2.0f, -3.0f };
	vec4 result = floor(v);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, ceil_basic)
{
	vec4 v = { 1.5f, -1.5f, 2.1f, -2.9f };
	vec4 check = { 2.0f, -1.0f, 3.0f, -2.0f };
	vec4 result = ceil(v);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, round_basic)
{
	vec4 v = { 2.4f, 2.6f, -2.4f, -2.6f };
	vec4 check = { 2.0f, 3.0f, -2.0f, -3.0f };
	vec4 result = round(v);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, round_half_to_even)
{
	vec4 v = { 0.5f, 1.5f, 2.5f, 3.5f };
	vec4 check = { 0.0f, 2.0f, 2.0f, 4.0f };
	vec4 result = round(v);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, frac_basic)
{
	vec4 v = { 1.25f, 2.75f, -1.25f, 3.0f };
	vec4 check = { 0.25f, 0.75f, 0.75f, 0.0f };
	vec4 result = frac(v);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, hadamard_basic)
{
	vec4 a = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 b = { 5.0f, 6.0f, 7.0f, 8.0f };
	vec4 check = { 5.0f, 12.0f, 21.0f, 32.0f };
	vec4 result = hadamard(a, b);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_vec4, hadamard_includes_w)
{
	vec4 a = { 1.0f, 1.0f, 1.0f, 2.0f };
	vec4 b = { 1.0f, 1.0f, 1.0f, 3.0f };
	vec4 check = { 1.0f, 1.0f, 1.0f, 6.0f };
	vec4 result = hadamard(a, b);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(vec4, magnitude3_less_all_relations)
{
	vec4 a = { 1.0f, 2.0f, 2.0f, 0.0f };
	vec4 b = { 3.0f, 0.0f, 4.0f, 0.0f };

	bool check_lt = true;
	bool check_le = true;
	bool check_gt = false;
	bool check_ge = false;

	bool result_lt = magnitude3(a) < magnitude3(b);
	bool result_le = magnitude3(a) <= magnitude3(b);
	bool result_gt = magnitude3(a) > magnitude3(b);
	bool result_ge = magnitude3(a) >= magnitude3(b);

	EXPECT_EQ(check_lt, result_lt);
	EXPECT_EQ(check_le, result_le);
	EXPECT_EQ(check_gt, result_gt);
	EXPECT_EQ(check_ge, result_ge);
}

TEST(vec4, magnitude3_equal_relations)
{
	vec4 a = { 1.0f, 2.0f, 2.0f, 0.0f };
	vec4 b = { 2.0f, 2.0f, 1.0f, 0.0f };

	bool check_lt = false;
	bool check_le = true;
	bool check_gt = false;
	bool check_ge = true;
	bool check_eq = true;
	bool check_ne = false;

	bool result_lt = magnitude3(a) < magnitude3(b);
	bool result_le = magnitude3(a) <= magnitude3(b);
	bool result_gt = magnitude3(a) > magnitude3(b);
	bool result_ge = magnitude3(a) >= magnitude3(b);
	bool result_eq = magnitude3(a) == magnitude3(b);
	bool result_ne = magnitude3(a) != magnitude3(b);

	EXPECT_EQ(check_lt, result_lt);
	EXPECT_EQ(check_le, result_le);
	EXPECT_EQ(check_gt, result_gt);
	EXPECT_EQ(check_ge, result_ge);
	EXPECT_EQ(check_eq, result_eq);
	EXPECT_EQ(check_ne, result_ne);
}

TEST(vec4, magnitude3_less_scalar_both_positions)
{
	vec4 a = { 3.0f, 0.0f, 4.0f, 0.0f };

	bool check_lt6 = true;
	bool check_lt4 = false;
	bool check_gt4 = true;
	bool check_le5 = true;
	bool check_ge5 = true;

	bool result_lt6 = magnitude3(a) < 6.0f;
	bool result_lt4 = magnitude3(a) < 4.0f;
	bool result_gt4 = magnitude3(a) > 4.0f;
	bool result_le5 = magnitude3(a) <= 5.0f;
	bool result_ge5 = magnitude3(a) >= 5.0f;

	EXPECT_EQ(check_lt6, result_lt6);
	EXPECT_EQ(check_lt4, result_lt4);
	EXPECT_EQ(check_gt4, result_gt4);
	EXPECT_EQ(check_le5, result_le5);
	EXPECT_EQ(check_ge5, result_ge5);

	bool check_6gt = true;
	bool check_4lt = true;
	bool check_5ge = true;

	bool result_6gt = 6.0f >= magnitude3(a);
	bool result_4lt = 4.0f < magnitude3(a);
	bool result_5ge = 5.0f >= magnitude3(a);

	EXPECT_EQ(check_6gt, result_6gt);
	EXPECT_EQ(check_4lt, result_4lt);
	EXPECT_EQ(check_5ge, result_5ge);
}

TEST(vec4, magnitude3_scalar_threshold_types)
{
	vec4 a = { 3.0f, 0.0f, 4.0f, 0.0f };

	bool check_int_6 = true;
	bool check_int_5 = false;
	bool check_double = true;
	bool check_float = true;

	bool result_int_6 = magnitude3(a) < 6;
	bool result_int_5 = magnitude3(a) < 5;
	bool result_double = magnitude3(a) < 5.5;
	bool result_float = magnitude3(a) < 5.5f;

	EXPECT_EQ(check_int_6, result_int_6);
	EXPECT_EQ(check_int_5, result_int_5);
	EXPECT_EQ(check_double, result_double);
	EXPECT_EQ(check_float, result_float);
}

TEST(vec4, magnitude3_nan_is_unordered)
{
	vec4 n = { std::nanf(""), 0.0f, 0.0f, 0.0f };
	vec4 b = { 1.0f, 0.0f, 0.0f, 0.0f };

	std::partial_ordering check_ord = std::partial_ordering::unordered;
	std::partial_ordering result_ord = magnitude3(n) <=> magnitude3(b);
	EXPECT_TRUE(check_ord == result_ord);

	bool check_lt = false;
	bool check_le = false;
	bool check_gt = false;
	bool check_ge = false;

	bool result_lt = magnitude3(n) < magnitude3(b);
	bool result_le = magnitude3(n) <= magnitude3(b);
	bool result_gt = magnitude3(n) > magnitude3(b);
	bool result_ge = magnitude3(n) >= magnitude3(b);

	EXPECT_EQ(check_lt, result_lt);
	EXPECT_EQ(check_le, result_le);
	EXPECT_EQ(check_gt, result_gt);
	EXPECT_EQ(check_ge, result_ge);
}

TEST(vec4, magnitude3_compare_is_eager)
{
	vec4 a = { 1.0f, 0.0f, 0.0f, 0.0f };
	vec4 b = { 2.0f, 0.0f, 0.0f, 0.0f };

	bool check = true;
	bool result = magnitude3(a) < magnitude3(b);

	EXPECT_TRUE((std::same_as<decltype(result), bool>));
	EXPECT_EQ(check, result);
}

TEST(naive_vec4, magnitude4_basic)
{
	vec4 v = { 1.0f, 2.0f, 2.0f, 4.0f };
	EXPECT_FLOAT_EQ(magnitude4(v), 5.0f);
}

TEST(naive_vec4, magnitude4_counts_w)
{
	vec4 v = { 0.0f, 3.0f, 4.0f, 12.0f };
	EXPECT_FLOAT_EQ(magnitude3(v), 5.0f);
	EXPECT_FLOAT_EQ(magnitude4(v), 13.0f);
}

TEST(naive_vec4, magnitude4_sq_basic)
{
	vec4 v = { 1.0f, 2.0f, 2.0f, 4.0f };
	float check = 25.0f;
	float result = magnitude4_sq(v);

	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_vec4, magnitude4_sq_counts_w)
{
	vec4 v = { 0.0f, 3.0f, 4.0f, 12.0f };
	float check3 = 25.0f;
	float check4 = 169.0f;
	float result3 = magnitude3_sq(v);
	float result4 = magnitude4_sq(v);

	EXPECT_FLOAT_EQ(check3, result3);
	EXPECT_FLOAT_EQ(check4, result4);
}

}