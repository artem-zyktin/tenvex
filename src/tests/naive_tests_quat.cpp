#include "naive_quat.h"

#include "gtest/gtest.h"

namespace naive
{

// Naive quaternion baseline, checked against the same hand-computed literals
// as the tenvex quat tests. a = {1,2,3,4}, b = {5,6,7,8}, c = {2,-1,4,-3}.

TEST(naive_quat, equality)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 1, 2, 3, 4 };
	EXPECT_TRUE(a == b);
	EXPECT_TRUE(approx_eq(a, b));
}

TEST(naive_quat, add)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat check = { 6, 8, 10, 12 };
	quat result = a + b;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_quat, sub)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat check = { -4, -4, -4, -4 };
	quat result = a - b;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_quat, mul_quat_float)
{
	quat q = { 1, 2, 3, 4 };
	quat check = { 2, 4, 6, 8 };
	quat result = q * 2.0f;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_quat, mul_float_quat)
{
	quat q = { 1, 2, 3, 4 };
	quat check = { 3, 6, 9, 12 };
	quat result = 3.0f * q;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_quat, hamilton_product)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat check = { 24, 48, 48, -6 };
	quat result = a * b;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_quat, hamilton_non_commutative)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat check = { 32, 32, 56, -6 };
	quat result = b * a;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_quat, hamilton_basis_ij)
{
	quat i = { 1, 0, 0, 0 };
	quat j = { 0, 1, 0, 0 };
	quat check = { 0, 0, 1, 0 };
	quat result = i * j;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_quat, hamilton_basis_ji)
{
	quat i = { 1, 0, 0, 0 };
	quat j = { 0, 1, 0, 0 };
	quat check = { 0, 0, -1, 0 };
	quat result = j * i;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_quat, hamilton_identity)
{
	quat a = { 1, 2, 3, 4 };
	quat id = { 0, 0, 0, 1 };
	quat result1 = a * id;
	quat result2 = id * a;
	EXPECT_TRUE(approx_eq(a, result1));
	EXPECT_TRUE(approx_eq(a, result2));
}

TEST(naive_quat, hamilton_associative)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat c = { 2, -1, 4, -3 };
	quat check = { 156, -138, -288, -174 };
	quat result1 = (a * b) * c;
	quat result2 = a * (b * c);
	EXPECT_TRUE(approx_eq(check, result1));
	EXPECT_TRUE(approx_eq(check, result2));
}

TEST(naive_quat, hamilton_distributes_over_add)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat c = { 2, -1, 4, -3 };
	quat check = { 40, 40, 50, -30 };
	quat result1 = a * (b + c);
	quat result2 = a * b + a * c;
	EXPECT_TRUE(approx_eq(check, result1));
	EXPECT_TRUE(approx_eq(check, result2));
}

// ---------------------------------------------------------------------------
// Conjugate: flip the imaginary part (x,y,z), keep the real part (w).
// ---------------------------------------------------------------------------

TEST(naive_quat, conj_flips_xyz_keeps_w)
{
	quat q = { 1, 2, 3, 4 };
	quat check = { -1, -2, -3, 4 };
	quat result = conj(q);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_quat, conj_of_pure_negates_xyz)
{
	quat v = { 1, 2, 3, 0 };
	quat check = { -1, -2, -3, 0 };
	quat result = conj(v);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_quat, conj_involutive)
{
	quat q = { 1, 2, 3, 4 };
	quat result = conj(conj(q));
	EXPECT_TRUE(approx_eq(q, result));
}

TEST(naive_quat, conj_anti_homomorphism)
{
	// conj(a * b) == conj(b) * conj(a)
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat check = { -24, -48, -48, -6 };
	quat result1 = conj(a * b);
	quat result2 = conj(b) * conj(a);
	EXPECT_TRUE(approx_eq(check, result1));
	EXPECT_TRUE(approx_eq(check, result2));
}

// ---------------------------------------------------------------------------
// Rotation (sandwich q * v * conj(q)); vector v is a pure quaternion (w = 0).
// qz = 90 deg about Z: sin45 = cos45 = 0.70710678.
// ---------------------------------------------------------------------------

TEST(naive_quat, rotate_z90_x)
{
	quat q = { 0, 0, 0.70710678f, 0.70710678f };
	vec4 check = { 0, 1, 0, 0 };
	vec4 result = rotate(vec4 { 1, 0, 0, 0 }, q);
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(naive_quat, rotate_z90_y)
{
	quat q = { 0, 0, 0.70710678f, 0.70710678f };
	vec4 check = { -1, 0, 0, 0 };
	vec4 result = rotate(vec4 { 0, 1, 0, 0 }, q);
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(naive_quat, rotate_z90_z_axis_fixed)
{
	quat qz = { 0, 0, 0.70710678f, 0.70710678f };
	vec4 check = { 0, 0, 1, 0 };
	vec4 result = rotate(vec4 { 0, 0, 1, 0 }, qz);
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(naive_quat, rotate_identity_is_noop)
{
	quat id = { 0, 0, 0, 1 };
	vec4 v = { 1, 2, 3, 0 };
	vec4 result = rotate(vec4 { 1, 2, 3, 0 }, id);
	EXPECT_TRUE(approx_eq(v, result, 1e-6f));
}

TEST(naive_quat, rotate_composition)
{
	quat qz = { 0, 0, 0.70710678f, 0.70710678f };
	vec4 x = { 1, 0, 0, 0 };
	vec4 check = { -1, 0, 0, 0 };
	vec4 twice = rotate(rotate(x, qz), qz);
	vec4 once = rotate(x, qz * qz);
	EXPECT_TRUE(approx_eq(check, twice, 1e-4f));
	EXPECT_TRUE(approx_eq(once, twice, 1e-4f));
}

TEST(naive_quat, dot4_basic)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	EXPECT_FLOAT_EQ(70.0f, dot4(a, b));
}

TEST(naive_quat, dot4_uses_all_four_lanes)
{
	quat a = { 0, 0, 0, 2 };
	quat b = { 1, 1, 1, 3 };
	EXPECT_FLOAT_EQ(6.0f, dot4(a, b));

}

TEST(naive_quat, magnitude4_basic)
{
	quat q = { 1, 2, 2, 4 };
	EXPECT_FLOAT_EQ(magnitude4(q), 5.0f);
}

TEST(naive_quat, magnitude4_sq_basic)
{
	quat q = { 1, 2, 2, 4 };
	float check = 25.0f;
	float result = magnitude4_sq(q);

	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_quat, inverse_scalar_quat)
{
	quat q = { 0, 0, 0, 2 };
	quat check = { 0, 0, 0, 0.5f };
	quat result = inverse(q);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_quat, inverse_of_unit_equals_conj)
{
	quat q = { 0, 0, 0.70710678f, 0.70710678f };
	quat check = { 0, 0, -0.70710678f, 0.70710678f };
	quat result = inverse(q);
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

}
