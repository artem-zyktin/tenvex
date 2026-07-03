#include "tenvex.h"

#include "gtest/gtest.h"

namespace tnvx
{

// ---------------------------------------------------------------------------
// Construction, accessors, equality
// ---------------------------------------------------------------------------

TEST(quat, construct_and_accessors)
{
	quat q = { 1, 2, 3, 4 };
	EXPECT_FLOAT_EQ(1.0f, q.x());
	EXPECT_FLOAT_EQ(2.0f, q.y());
	EXPECT_FLOAT_EQ(3.0f, q.z());
	EXPECT_FLOAT_EQ(4.0f, q.w());
}

TEST(quat, equality_equal)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 1, 2, 3, 4 };
	EXPECT_TRUE(a == b);
	EXPECT_TRUE(approx_eq(a, b));
}

TEST(quat, equality_differs)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 1, 2, 3, 5 };
	EXPECT_FALSE(a == b);
	EXPECT_FALSE(approx_eq(a, b));
}

TEST(quat, approx_eq_respects_epsilon)
{
	quat a = { 1.0f, 2.0f, 3.0f, 4.0f };
	quat b = { 1.0f + 1e-4f, 2.0f, 3.0f, 4.0f };
	EXPECT_TRUE(approx_eq(a, b, 1e-3f));
	EXPECT_FALSE(approx_eq(a, b, 1e-6f));
}

TEST(quat, converting_ctor_from_expression)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat check = { 6, 8, 10, 12 };
	quat result = a + b;
	EXPECT_TRUE(approx_eq(check, result));
}

// ---------------------------------------------------------------------------
// Conjugate
// ---------------------------------------------------------------------------

TEST(quat, conjugate_flips_xyz_keeps_w)
{
	quat q = { 1, 2, 3, 4 };
	quat check = { -1, -2, -3, 4 };
	quat result = conj(q);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(quat, conjugate_is_quat_expr)
{
	quat q = { 1, 2, 3, 4 };
	EXPECT_TRUE((quat_expr<decltype(conj(q))>));
}

TEST(quat, conjugate_involutive)
{
	quat q = { 1, 2, 3, 4 };
	quat result = conj(conj(q));
	EXPECT_TRUE(approx_eq(q, result));
}

// ---------------------------------------------------------------------------
// Addition / subtraction (component-wise)
// ---------------------------------------------------------------------------

TEST(quat, add_quat_quat)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat check = { 6, 8, 10, 12 };
	quat result = a + b;
	EXPECT_TRUE(approx_eq(check, result));
	EXPECT_TRUE((quat_expr<decltype(a + b)>));
}

TEST(quat, sub_quat_quat)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat check = { -4, -4, -4, -4 };
	quat result = a - b;
	EXPECT_TRUE(approx_eq(check, result));
	EXPECT_TRUE((quat_expr<decltype(a - b)>));
}

TEST(quat, add_composes_with_conjugate)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat check = { 4, 4, 4, 12 };
	quat result = conj(a) + b;
	EXPECT_TRUE(approx_eq(check, result));
}

// ---------------------------------------------------------------------------
// Scalar scaling (routes through Mul, scales all four lanes incl. w)
// ---------------------------------------------------------------------------

TEST(quat, mul_quat_float_scales_all_lanes)
{
	quat q = { 1, 2, 3, 4 };
	quat check = { 2, 4, 6, 8 };
	quat result = q * 2.0f;
	EXPECT_TRUE(approx_eq(check, result));
	EXPECT_TRUE((quat_expr<decltype(q * 2.0f)>));
}

TEST(quat, mul_float_quat)
{
	quat q = { 1, 2, 3, 4 };
	quat check = { 3, 6, 9, 12 };
	quat result = 3.0f * q;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(quat, mul_quat_scalar_expr)
{
	quat q = { 1, 2, 3, 4 };
	vec4 u = { 1, 0, 3, 0 };
	vec4 v = { 1, 2, 3, 0 };
	quat check = { 10, 20, 30, 40 };
	EXPECT_TRUE(approx_eq(check, q * dot3(u, v)));
	EXPECT_TRUE(approx_eq(check, dot3(u, v) * q));
}

TEST(quat, mul_quat_scalar_disjoint_category)
{
	quat q = { 1, 2, 3, 4 };
	auto r = q * 2.0f;
	EXPECT_TRUE((quat_expr<decltype(r)>));
	EXPECT_FALSE((vec_expr<decltype(r)>));
	EXPECT_FALSE((scalar_expr<decltype(r)>));
}

// ---------------------------------------------------------------------------
// Hamilton product (quat * quat).  Expected values computed by hand.
// a = {1,2,3,4}, b = {5,6,7,8}, c = {2,-1,4,-3}.
// ---------------------------------------------------------------------------

TEST(quat, hamilton_product)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat check = { 24, 48, 48, -6 };
	quat result = a * b;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(quat, hamilton_non_commutative)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat check = { 32, 32, 56, -6 };
	quat result = b * a;
	EXPECT_TRUE(approx_eq(check, result));
	EXPECT_FALSE(approx_eq(quat(a * b), quat(b * a)));
}

TEST(quat, hamilton_basis_units)
{
	quat i = { 1, 0, 0, 0 };
	quat j = { 0, 1, 0, 0 };
	quat k = { 0, 0, 1, 0 };
	EXPECT_TRUE(approx_eq(quat(0, 0, 1, 0), i * j));
	EXPECT_TRUE(approx_eq(quat(0, 0, -1, 0), j * i));
	EXPECT_TRUE(approx_eq(quat(1, 0, 0, 0), j * k));
	EXPECT_TRUE(approx_eq(quat(0, 1, 0, 0), k * i));
}

TEST(quat, hamilton_identity)
{
	quat a = { 1, 2, 3, 4 };
	quat id = { 0, 0, 0, 1 };
	EXPECT_TRUE(approx_eq(a, a * id));
	EXPECT_TRUE(approx_eq(a, id * a));
}

TEST(quat, hamilton_associative)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat c = { 2, -1, 4, -3 };
	quat check = { 156, -138, -288, -174 };
	EXPECT_TRUE(approx_eq(check, (a * b) * c));
	EXPECT_TRUE(approx_eq(check, a * (b * c)));
}

TEST(quat, hamilton_distributes_over_add)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat c = { 2, -1, 4, -3 };
	quat check = { 40, 40, 50, -30 };
	EXPECT_TRUE(approx_eq(check, a * (b + c)));
	EXPECT_TRUE(approx_eq(check, quat(a * b) + quat(a * c)));
}

TEST(quat, hamilton_times_conjugate_is_pure_real)
{
	quat a = { 1, 2, 3, 4 };
	quat check = { 0, 0, 0, 30 };
	quat result = a * conj(a);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(quat, hamilton_category)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	EXPECT_TRUE((quat_expr<decltype(a * b)>));
	EXPECT_FALSE((vec_expr<decltype(a * b)>));
	EXPECT_FALSE((scalar_expr<decltype(a * b)>));
}

TEST(quat, hamilton_composes_and_scales)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat check = { 48, 96, 96, -12 };
	quat result = (a * b) * 2.0f;
	EXPECT_TRUE(approx_eq(check, result));
}

}