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

	EXPECT_FLOAT_EQ(min(a, b).w(), 3.0f);
	EXPECT_FLOAT_EQ(max(a, b).w(), 5.0f);
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

}