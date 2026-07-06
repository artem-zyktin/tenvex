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

TEST(quat, rotate_z90_axes)
{
	quat qz = { 0, 0, 0.70710678f, 0.70710678f };
	EXPECT_TRUE(approx_eq(vec4 { 0, 1, 0, 0 }, rotate(vec4 { 1, 0, 0, 0 }, qz), 1e-5f)); // x -> y
	EXPECT_TRUE(approx_eq(vec4 { -1, 0, 0, 0 }, rotate(vec4 { 0, 1, 0, 0 }, qz), 1e-5f)); // y -> -x
	EXPECT_TRUE(approx_eq(vec4 { 0, 0, 1, 0 }, rotate(vec4 { 0, 0, 1, 0 }, qz	), 1e-5f)); // z -> z
}

TEST(quat, rotate_identity_is_noop)
{
	quat id = { 0, 0, 0, 1 };
	vec4 v = { 1, 2, 3, 0 };
	EXPECT_TRUE(approx_eq(v, rotate(v, id), 1e-6f));
}

TEST(quat, rotate_perpendicular_equals_cross3)
{
	// 90 deg about n=z, applied to v perpendicular to n, equals cross3(n, v).
	quat qz = { 0, 0, 0.70710678f, 0.70710678f };
	vec4 n = { 0, 0, 1, 0 };
	vec4 v = { 1, 0, 0, 0 };
	EXPECT_TRUE(approx_eq(vec4(cross3(n, v)), rotate(v, qz), 1e-5f));
}

TEST(quat, rotate_leaves_axis_fixed)
{
	quat qz = { 0, 0, 0.70710678f, 0.70710678f };
	vec4 axis = { 0, 0, 1, 0 };
	EXPECT_TRUE(approx_eq(axis, rotate(axis, qz), 1e-6f));
}

TEST(quat, rotate_preserves_length)
{
	quat qz = { 0, 0, 0.70710678f, 0.70710678f };
	vec4 v = { 1, 2, 3, 0 };
	float rotated = magnitude3(rotate(v, qz));
	float original = magnitude3(v);
	EXPECT_NEAR(original, rotated, 1e-4f);
}

TEST(quat, rotate_preserves_dot)
{
	quat qz = { 0, 0, 0.70710678f, 0.70710678f };
	vec4 a = { 1, 2, 3, 0 };
	vec4 b = { 4, 5, 6, 0 };
	float before = dot3(a, b);
	float after = dot3(vec4(rotate(a, qz)), vec4(rotate(b, qz)));
	EXPECT_NEAR(before, after, 1e-3f);
}

TEST(quat, rotate_composition_matches_hamilton)
{
	// rotate(q, rotate(q, v)) == rotate(q*q, v).  q*q = 180 about z, so x -> -x.
	quat qz = { 0, 0, 0.70710678f, 0.70710678f };
	vec4 x = { 1, 0, 0, 0 };
	vec4 twice = rotate(rotate(x, qz), qz);
	vec4 once = rotate(x, qz * qz);
	EXPECT_TRUE(approx_eq(twice, once, 1e-4f));
	EXPECT_TRUE(approx_eq(vec4 { -1, 0, 0, 0 }, twice, 1e-4f));
}

TEST(quat, rotate_is_vec_expr)
{
	quat qz = { 0, 0, 0.70710678f, 0.70710678f };
	vec4 v = { 1, 0, 0, 0 };
	EXPECT_TRUE((vec_expr<decltype(rotate(v, qz))>));
	EXPECT_FALSE((quat_expr<decltype(rotate(v, qz))>));
}

TEST(quat, dot4_basic)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	// 1*5 + 2*6 + 3*7 + 4*8 = 5 + 12 + 21 + 32 = 70
	EXPECT_FLOAT_EQ(70.0f, float(dot4(a, b)));
}

TEST(quat, dot4_uses_all_four_lanes)
{
	quat a = { 0, 0, 0, 2 };
	quat b = { 1, 1, 1, 3 };
	EXPECT_FLOAT_EQ(6.0f, float(dot4(a, b)));
}

TEST(quat, dot4_commutative)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	EXPECT_FLOAT_EQ(float(dot4(a, b)), float(dot4(b, a)));
}

TEST(quat, dot4_is_scalar_expr)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	EXPECT_TRUE((scalar_expr<decltype(dot4(a, b))>));
	EXPECT_FALSE((quat_expr<decltype(dot4(a, b))>));
}

TEST(quat, dot4_rejects_mixed_category)
{
	// vec x quat is ill-formed by construction; the concept is the guard.
	EXPECT_TRUE((same_packed_category<quat, quat>));
	EXPECT_FALSE((same_packed_category<vec4, quat>));
}

// ---------------------------------------------------------------------------
// magnitude4: the 4-lane length. Same node as vec4 via packed_expr.
// ---------------------------------------------------------------------------

TEST(quat, magnitude4_basic)
{
	quat q = { 1, 2, 2, 4 };
	// sqrt(1 + 4 + 4 + 16) = 5
	EXPECT_FLOAT_EQ(5.0f, float(magnitude4(q)));
}

TEST(quat, magnitude4_of_unit_is_one)
{
	quat q = { 0, 0, 0.70710678f, 0.70710678f };
	EXPECT_NEAR(1.0f, float(magnitude4(q)), 1e-5f);
}

TEST(quat, magnitude4_is_scalar_expr)
{
	quat q = { 1, 2, 2, 4 };
	EXPECT_TRUE((scalar_expr<decltype(magnitude4(q))>));
	EXPECT_FALSE((quat_expr<decltype(magnitude4(q))>));
}

TEST(quat, magnitude4_sq_basic)
{
	quat q = { 1, 2, 2, 4 };
	float check = 25.0f;
	float result = magnitude4_sq(q);

	EXPECT_FLOAT_EQ(check, result);
}

TEST(quat, magnitude4_sq_of_unit_is_one)
{
	quat q = { 0, 0, 0.70710678f, 0.70710678f };
	float check = 1.0f;
	float result = magnitude4_sq(q);

	EXPECT_NEAR(check, result, 1e-5f);
}

TEST(quat, magnitude4_sq_is_scalar_expr)
{
	quat q = { 1, 2, 2, 4 };
	EXPECT_TRUE((scalar_expr<decltype(magnitude4_sq(q))>));
	EXPECT_FALSE((quat_expr<decltype(magnitude4_sq(q))>));
}

// ---------------------------------------------------------------------------
// inverse: conj(q) / magnitude4_sq(q). For a unit quaternion this equals conj.
// Quaternion-specific; stays a quat_expr.
// ---------------------------------------------------------------------------

TEST(quat, inverse_scalar_quat)
{
	quat q = { 0, 0, 0, 2 };
	quat check = { 0, 0, 0, 0.5f }; // conj / |q|^2 = (0,0,0,2) / 4
	quat result = inverse(q);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(quat, inverse_of_unit_equals_conj)
{
	quat q = { 0, 0, 0.70710678f, 0.70710678f };     // unit
	quat check = { 0, 0, -0.70710678f, 0.70710678f };
	quat result = inverse(q);
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(quat, inverse_times_self_is_identity)
{
	quat q = { 1, 2, 3, 4 };
	quat check = { 0, 0, 0, 1 };
	quat result = q * inverse(q);
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(quat, inverse_is_quat_expr)
{
	quat q = { 1, 2, 3, 4 };
	EXPECT_TRUE((quat_expr<decltype(inverse(q))>));
	EXPECT_FALSE((scalar_expr<decltype(inverse(q))>));
}

TEST(quat, normalize_scalar_quat)
{
	quat q = { 0, 0, 0, 2 };
	quat check = { 0, 0, 0, 1 };
	quat result = normalize(q);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(quat, normalize_uniform)
{
	quat q = { 1, 1, 1, 1 };
	quat check = { 0.5f, 0.5f, 0.5f, 0.5f };
	quat result = normalize(q);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(quat, normalize_yields_unit_length)
{
	quat q = { 1, 2, 3, 4 };
	float check = 1.0f;
	float result = magnitude4(normalize(q));
	EXPECT_NEAR(check, result, 1e-5f);
}

TEST(quat, normalize_is_quat_expr)
{
	quat q = { 1, 2, 3, 4 };
	EXPECT_TRUE((quat_expr<decltype(normalize(q))>));
	EXPECT_FALSE((scalar_expr<decltype(normalize(q))>));
}

}