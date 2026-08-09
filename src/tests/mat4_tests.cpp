#include "tenvex/tenvex.h"

#include "gtest/gtest.h"

#include <cmath>

namespace tnvx
{

// ---------------------------------------------------------------------------
// Construction and layout
// ---------------------------------------------------------------------------

TEST(mat4, ctor_scalar_is_column_major)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	vec4 check = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 result = m.col(0);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, ctor_scalar_last_column)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	vec4 check = { 13.0f, 14.0f, 15.0f, 16.0f };
	vec4 result = m.col(3);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, ctor_vec4_columns)
{
	mat4 check = {  1.0f,  2.0f,  3.0f,  4.0f,
					5.0f,  6.0f,  7.0f,  8.0f,
					9.0f, 10.0f, 11.0f, 12.0f,
				   13.0f, 14.0f, 15.0f, 16.0f };
	mat4 result = { vec4 {  1.0f,  2.0f,  3.0f,  4.0f },
					vec4 {  5.0f,  6.0f,  7.0f,  8.0f },
					vec4 {  9.0f, 10.0f, 11.0f, 12.0f },
					vec4 { 13.0f, 14.0f, 15.0f, 16.0f } };
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, ctor_vf4_columns)
{
	mat4 check = {  1.0f,  2.0f,  3.0f,  4.0f,
					5.0f,  6.0f,  7.0f,  8.0f,
					9.0f, 10.0f, 11.0f, 12.0f,
				   13.0f, 14.0f, 15.0f, 16.0f };
	mat4 result = { detail::set( 1.0f,  2.0f,  3.0f,  4.0f),
					detail::set( 5.0f,  6.0f,  7.0f,  8.0f),
					detail::set( 9.0f, 10.0f, 11.0f, 12.0f),
					detail::set(13.0f, 14.0f, 15.0f, 16.0f) };
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, ctor_mf4_roundtrip)
{
	mat4 check = {  1.0f,  2.0f,  3.0f,  4.0f,
					5.0f,  6.0f,  7.0f,  8.0f,
					9.0f, 10.0f, 11.0f, 12.0f,
				   13.0f, 14.0f, 15.0f, 16.0f };
	mat4 result = mat4 { check.eval() };
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, at_matches_col)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	float check = m.col(1).z();
	float result = m.at<2, 1>();
	EXPECT_FLOAT_EQ(check, result);
}

// ---------------------------------------------------------------------------
// Named constants
// ---------------------------------------------------------------------------

TEST(mat4, zero_is_all_zeroes)
{
	mat4 check = { 0.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 0.0f, 0.0f };
	mat4 result = mat4::zero();
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, identity_matches_unit_scaling)
{
	mat4 check = mat4::identity();
	mat4 result = mat4::scaling(1.0f);
	EXPECT_TRUE(approx_eq(check, result));
}

// ---------------------------------------------------------------------------
// Scaling
// ---------------------------------------------------------------------------

TEST(mat4, scaling_uniform_matches_xyz)
{
	mat4 check = mat4::scaling(2.5f, 2.5f, 2.5f);
	mat4 result = mat4::scaling(2.5f);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, scaling_vec4_matches_scalar)
{
	mat4 check = mat4::scaling(2.0f, 3.0f, 4.0f);
	mat4 result = mat4::scaling(vec4 { 2.0f, 3.0f, 4.0f, 1.0f });
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, scaling_keeps_w_one)
{
	mat4 m = mat4::scaling(2.0f, 3.0f, 4.0f);
	float check = 1.0f;
	float result = m.at<3, 3>();
	EXPECT_FLOAT_EQ(check, result);
}

// ---------------------------------------------------------------------------
// Translation
// ---------------------------------------------------------------------------

TEST(mat4, translation_lands_in_last_column)
{
	mat4 check = { 1.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 1.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 1.0f, 0.0f,
				   4.0f, 5.0f, 6.0f, 1.0f };
	mat4 result = mat4::translation(4.0f, 5.0f, 6.0f);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, translation_scalar_matches_vec4)
{
	mat4 check = mat4::translation(vec4 { 4.0f, 5.0f, 6.0f, 1.0f });
	mat4 result = mat4::translation(4.0f, 5.0f, 6.0f);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, translation_ignores_input_w)
{
	mat4 check = mat4::translation(vec4 { 4.0f, 5.0f, 6.0f, 1.0f });
	mat4 result = mat4::translation(vec4 { 4.0f, 5.0f, 6.0f, 7.0f });
	EXPECT_TRUE(approx_eq(check, result));
}

// ---------------------------------------------------------------------------
// Rotation
// ---------------------------------------------------------------------------

TEST(mat4, from_quat_identity_is_identity)
{
	mat4 check = mat4::identity();
	mat4 result = mat4::from_quat(quat::identity());
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, from_quat_z90_matches_literal)
{
	constexpr float pi = 3.14159265f;
	quat q = quat::from_axis_angle(vec4 { 0.0f, 0.0f, 1.0f, 0.0f }, pi / 2.0f);
	mat4 check = {  0.0f, 1.0f, 0.0f, 0.0f,
				   -1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f };
	mat4 result = mat4::from_quat(q);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, from_quat_columns_are_rotated_basis)
{
	constexpr float pi = 3.14159265f;
	quat q = quat::from_axis_angle(vec4 { 1.0f, 2.0f, 3.0f, 0.0f }, pi / 3.0f);
	mat4 check = { rotate(vec4::unit_x(), q),
				   rotate(vec4::unit_y(), q),
				   rotate(vec4::unit_z(), q),
				   vec4::unit_w() };
	mat4 result = mat4::from_quat(q);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, from_rotation_matches_from_quat)
{
	constexpr float pi = 3.14159265f;
	vec4 axis = { 1.0f, 2.0f, 3.0f, 0.0f };
	mat4 check = mat4::from_quat(quat::from_axis_angle(axis, pi / 3.0f));
	mat4 result = mat4::from_rotation(axis, pi / 3.0f);
	EXPECT_TRUE(approx_eq(check, result));
}

}