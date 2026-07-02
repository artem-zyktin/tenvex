#include "tenvex.h"

#include "gtest/gtest.h"

namespace tnvx
{

TEST(quat, conjugate_flips_xyz_keeps_w)
{
	quat q = {1, 2, 3, 4};
	quat check(-1, -2, -3, 4);
	quat result = conj(q);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(quat, conjugate_is_quat_expr)
{
	quat q = {1, 2, 3, 4};
	EXPECT_TRUE((quat_expr<decltype(conj(q))>));
}

TEST(quat, conjugate_involutive)
{
	quat q = {1, 2, 3, 4};
	quat result = conj(conj(q));
	EXPECT_TRUE(approx_eq(q, result));
}

TEST(quat, add_quat_quat)
{
	quat p = { 1.0f, 2.0f, 3.0f, 4.0f };
	quat q = { 10.0f, 20.0f, 30.0f, 40.0f };
	quat check = { 11.0f, 22.0f, 33.0f, 44.0f };
	quat result = p + q;

	EXPECT_TRUE(approx_eq(check, result));
	EXPECT_TRUE((quat_expr<decltype(p + q)>));
}

TEST(quat, sub_quat_quat)
{
	quat p = { 1.0f, 2.0f, 3.0f, 4.0f };
	quat q = { 10.0f, 20.0f, 30.0f, 40.0f };
	quat check = { 9.0f, 18.0f, 27.0f, 36.0f };
	quat result = q - p;

	EXPECT_TRUE(approx_eq(check, result));
	EXPECT_TRUE((quat_expr<decltype(q - p)>));
}

TEST(quat, add_composes_with_conjugate)
{
	quat p = { 1.0f, 2.0f, 3.0f, 4.0f };
	quat q = { 10.0f, 20.0f, 30.0f, 40.0f };
	quat check = { 9.0f, 18.0f, 27.0f, 44.0f };
	quat result = conj(p) + q;

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(quat, mul_quat_float_scales_all_lanes)
{
	quat q = {1.0f, 2.0f, 3.0f, 4.0f};
	quat check = {2.0f, 4.0f, 6.0f, 8.0f};
	quat result = q * 2.0f;
	EXPECT_TRUE(approx_eq(check, result));
	EXPECT_TRUE((quat_expr<decltype(result)>));
}

TEST(quat, mul_float_quat)
{
	quat q = {1.0f, 2.0f, 3.0f, 4.0f};
	quat check = {3.0f, 6.0f, 9.0f, 12.0f};
	quat result = 3.0f * q;
	EXPECT_TRUE(approx_eq(check, result));
	EXPECT_TRUE((quat_expr<decltype(result)>));
}

TEST(quat, mul_quat_scalar_expr)
{
	quat q = {1.0f, 2.0f, 3.0f, 4.0f};
	vec4 a = {1.0f, 0.0f, 3.0f, 0.0f};
	vec4 b = {1.0f, 2.0f, 3.0f, 0.0f};
	quat check = {10.0f, 20.0f, 30.0f, 40.0f};
	quat result1 = q * dot3(a, b);
	quat result2 = dot3(a, b) * q;
	EXPECT_TRUE(approx_eq(check, result1));
	EXPECT_TRUE(approx_eq(check, result2));
}

TEST(quat, mul_quat_scalar_disjoint_category)
{
	quat q = {1.0f, 2.0f, 3.0f, 4.0f};
	auto r = q * 2.0f;
	EXPECT_TRUE((quat_expr<decltype(r)>));
	EXPECT_FALSE((vec_expr<decltype(r)>));
	EXPECT_FALSE((scalar_expr<decltype(r)>));
}

TEST(quat, mul_composes_in_expression)
{
	quat p = {0.0f, 0.0f, 0.0f, 1.0f};
	quat q = {1.0f, 2.0f, 3.0f, 4.0f};
	quat check = {2.0f, 4.0f, 6.0f, 10.0f};
	quat result = (p + q) * 2.0f;
	EXPECT_TRUE(approx_eq(check, result));
}

}
