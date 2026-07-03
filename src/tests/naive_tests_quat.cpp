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
	EXPECT_TRUE(approx_eq(a, a * id));
	EXPECT_TRUE(approx_eq(a, id * a));
}

TEST(naive_quat, hamilton_associative)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat c = { 2, -1, 4, -3 };
	quat check = { 156, -138, -288, -174 };
	EXPECT_TRUE(approx_eq(check, (a * b) * c));
	EXPECT_TRUE(approx_eq(check, a * (b * c)));
}

TEST(naive_quat, hamilton_distributes_over_add)
{
	quat a = { 1, 2, 3, 4 };
	quat b = { 5, 6, 7, 8 };
	quat c = { 2, -1, 4, -3 };
	quat check = { 40, 40, 50, -30 };
	EXPECT_TRUE(approx_eq(check, a * (b + c)));
	EXPECT_TRUE(approx_eq(check, quat(a * b) + quat(a * c)));
}

}