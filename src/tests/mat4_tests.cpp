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

// ---------------------------------------------------------------------------
// Transform (M * v)
// ---------------------------------------------------------------------------

TEST(mat4, transform_matches_hand_computed)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	vec4 v = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 check = { 90.0f, 100.0f, 110.0f, 120.0f };
	vec4 result = m * v;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, transform_named_matches_operator)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	vec4 v = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 check = m * v;
	vec4 result = transform(v, m);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, transform_of_basis_is_a_column)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	EXPECT_TRUE(approx_eq(m.col(0), vec4(m * vec4::unit_x())));
	EXPECT_TRUE(approx_eq(m.col(1), vec4(m * vec4::unit_y())));
	EXPECT_TRUE(approx_eq(m.col(2), vec4(m * vec4::unit_z())));
	EXPECT_TRUE(approx_eq(m.col(3), vec4(m * vec4::unit_w())));
}

TEST(mat4, transform_by_identity_is_a_noop)
{
	vec4 check = { 1.0f, -2.0f, 3.5f, 1.0f };
	vec4 result = mat4::identity() * check;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, transform_translates_a_point)
{
	mat4 t = mat4::translation(1.0f, 2.0f, 3.0f);
	vec4 check = { 11.0f, 22.0f, 33.0f, 1.0f };
	vec4 result = t * vec4 { 10.0f, 20.0f, 30.0f, 1.0f };
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, transform_leaves_a_direction_untranslated)
{
	mat4 t = mat4::translation(1.0f, 2.0f, 3.0f);
	vec4 check = { 10.0f, 20.0f, 30.0f, 0.0f };
	vec4 result = t * check;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, transform_scales_each_axis)
{
	mat4 s = mat4::scaling(2.0f, 3.0f, 4.0f);
	vec4 check = { 2.0f, 3.0f, 4.0f, 1.0f };
	vec4 result = s * vec4 { 1.0f, 1.0f, 1.0f, 1.0f };
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, transform_by_rotation_matches_quat_rotate)
{
	constexpr float pi = 3.14159265f;
	quat q = quat::from_axis_angle(vec4 { 1.0f, 2.0f, 3.0f, 0.0f }, pi / 3.0f);
	vec4 v = { 0.4f, -1.2f, 2.5f, 0.0f };
	vec4 check = rotate(v, q);
	vec4 result = mat4::from_quat(q) * v;
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(mat4, transform_is_linear)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	vec4 a = { 1.0f, -2.0f, 3.0f, 1.0f };
	vec4 b = { 0.5f, 4.0f, -1.0f, 1.0f };
	vec4 check = vec4(m * a) + vec4(m * b);
	vec4 result = m * (a + b);
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(mat4, transform_is_vec_expr)
{
	mat4 m = mat4::identity();
	vec4 v = vec4::unit_x();
	EXPECT_TRUE((vec_expr<decltype(m * v)>));
	EXPECT_TRUE((vec_expr<decltype(transform(v, m))>));
}

TEST(mat4, transform_fuses_into_a_vector_expression)
{
	mat4 m = mat4::scaling(2.0f);
	vec4 v = { 1.0f, 2.0f, 3.0f, 0.0f };
	vec4 check = { 3.0f, 5.0f, 7.0f, 0.0f };
	vec4 result = m * v + vec4::one() * 1.0f - vec4::unit_w();
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, transform_feeds_a_reduction)
{
	mat4 m = mat4::identity();
	vec4 v = { 3.0f, 4.0f, 0.0f, 0.0f };
	float check = 5.0f;
	float result = magnitude3(transform(v, m));
	EXPECT_NEAR(check, result, 1e-5f);
}

// ---------------------------------------------------------------------------
// Matrix product
// ---------------------------------------------------------------------------

TEST(mat4, product_matches_hand_computed)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	mat4 check = {  90.0f, 100.0f, 110.0f, 120.0f,
				   202.0f, 228.0f, 254.0f, 280.0f,
				   314.0f, 356.0f, 398.0f, 440.0f,
				   426.0f, 484.0f, 542.0f, 600.0f };
	mat4 result = m * m;
	EXPECT_TRUE(approx_eq(check, result, 1e-4f));
}

TEST(mat4, product_with_identity_is_a_noop)
{
	mat4 check = {  1.0f,  2.0f,  3.0f,  4.0f,
					5.0f,  6.0f,  7.0f,  8.0f,
					9.0f, 10.0f, 11.0f, 12.0f,
				   13.0f, 14.0f, 15.0f, 16.0f };
	mat4 id = mat4::identity();
	EXPECT_TRUE(approx_eq(check, mat4(check * id)));
	EXPECT_TRUE(approx_eq(check, mat4(id * check)));
}

TEST(mat4, product_is_not_commutative)
{
	mat4 t = mat4::translation(1.0f, 0.0f, 0.0f);
	mat4 s = mat4::scaling(2.0f);
	EXPECT_FALSE(approx_eq(mat4(t * s), mat4(s * t)));
}

TEST(mat4, product_is_associative)
{
	mat4 a = mat4::translation(1.0f, 2.0f, 3.0f);
	mat4 b = mat4::from_rotation(vec4 { 0.0f, 0.0f, 1.0f, 0.0f }, 0.7f);
	mat4 c = mat4::scaling(2.0f, 3.0f, 4.0f);
	mat4 check = mat4(a * b) * c;
	mat4 result = a * mat4(b * c);
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(mat4, product_applies_right_to_left)
{
	constexpr float pi = 3.14159265f;
	mat4 t = mat4::translation(1.0f, 2.0f, 3.0f);
	mat4 r = mat4::from_rotation(vec4 { 0.0f, 0.0f, 1.0f, 0.0f }, pi / 2.0f);
	mat4 s = mat4::scaling(2.0f);
	vec4 p = { 1.0f, 0.0f, 0.0f, 1.0f };

	// scale first, then rotate, then translate
	vec4 check = s * p;
	check = r * vec4(check);
	check = t * vec4(check);

	vec4 result = mat4(t * r * s) * p;
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(mat4, product_of_transforms_matches_applying_both)
{
	mat4 a = mat4::translation(1.0f, 2.0f, 3.0f);
	mat4 b = mat4::scaling(2.0f);
	vec4 p = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4 check = a * vec4(b * p);
	vec4 result = mat4(a * b) * p;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, product_is_mat_expr)
{
	mat4 m = mat4::identity();
	EXPECT_TRUE((mat_expr<decltype(m * m)>));
}

// ---------------------------------------------------------------------------
// Element-wise arithmetic
// ---------------------------------------------------------------------------

TEST(mat4, add_doubles_every_lane)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	mat4 check = {  2.0f,  4.0f,  6.0f,  8.0f,
				   10.0f, 12.0f, 14.0f, 16.0f,
				   18.0f, 20.0f, 22.0f, 24.0f,
				   26.0f, 28.0f, 30.0f, 32.0f };
	mat4 result = m + m;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, sub_of_self_is_zero)
{
	mat4 m = mat4::identity();
	mat4 check = mat4::zero();
	mat4 result = m - m;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, neg_cancels_under_add)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	mat4 check = mat4::zero();
	mat4 result = m + -m;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, neg_is_involutive)
{
	mat4 check = mat4::identity();
	mat4 result = -(-check);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, mul_by_float_matches_add)
{
	mat4 m = mat4::identity();
	mat4 check = m + m;
	mat4 result = m * 2.0f;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, mul_float_on_either_side)
{
	mat4 m = mat4::identity();
	mat4 check = m * 2.0f;
	mat4 result = 2.0f * m;
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, mul_by_scalar_expr)
{
	mat4 m = mat4::identity();
	vec4 v = { 2.0f, 0.0f, 0.0f, 0.0f };
	mat4 check = m * 2.0f;
	mat4 result = m * magnitude3(v);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, arithmetic_stays_mat_expr)
{
	mat4 a = mat4::identity();
	mat4 b = mat4::scaling(2.0f);
	EXPECT_TRUE((mat_expr<decltype(a + b)>));
	EXPECT_TRUE((mat_expr<decltype(a - b)>));
	EXPECT_TRUE((mat_expr<decltype(-a)>));
	EXPECT_TRUE((mat_expr<decltype(a * 2.0f)>));
	EXPECT_TRUE((mat_expr<decltype(a * b + a)>));
	EXPECT_TRUE((mat_expr<decltype(transpose(a * b) * 2.0f)>));
}

TEST(mat4, expression_mixes_product_sum_and_scale)
{
	mat4 a = mat4::scaling(1.0f, 2.0f, 3.0f);
	mat4 b = mat4::identity();
	mat4 check = mat4(a * 2.0f) + b;
	mat4 result = a * b * 2.0f + b;
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(mat4, expression_from_temporaries)
{
	vec4 p = { 1.0f, 0.0f, 0.0f, 1.0f };
	vec4 check = { 3.0f, 2.0f, 3.0f, 1.0f };
	vec4 result = mat4(mat4::translation(1.0f, 2.0f, 3.0f) * mat4::scaling(2.0f)) * p;
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

// ---------------------------------------------------------------------------
// Transpose
// ---------------------------------------------------------------------------

TEST(mat4, transpose_swaps_rows_and_columns)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	mat4 check = { 1.0f,  5.0f,  9.0f, 13.0f,
				   2.0f,  6.0f, 10.0f, 14.0f,
				   3.0f,  7.0f, 11.0f, 15.0f,
				   4.0f,  8.0f, 12.0f, 16.0f };
	mat4 result = transpose(m);
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, transpose_is_involutive)
{
	mat4 check = {  1.0f,  2.0f,  3.0f,  4.0f,
					5.0f,  6.0f,  7.0f,  8.0f,
					9.0f, 10.0f, 11.0f, 12.0f,
				   13.0f, 14.0f, 15.0f, 16.0f };
	mat4 result = transpose(transpose(check));
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, transpose_of_identity_is_identity)
{
	mat4 check = mat4::identity();
	mat4 result = transpose(mat4::identity());
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, transpose_reverses_a_product)
{
	mat4 a = mat4::translation(1.0f, 2.0f, 3.0f);
	mat4 b = mat4::scaling(2.0f, 3.0f, 4.0f);
	mat4 check = mat4(transpose(b)) * mat4(transpose(a));
	mat4 result = transpose(mat4(a * b));
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(mat4, transpose_is_mat_expr)
{
	mat4 m = mat4::identity();
	EXPECT_TRUE((mat_expr<decltype(transpose(m))>));
}

// ---------------------------------------------------------------------------
// Determinant
// ---------------------------------------------------------------------------

TEST(mat4, determinant_of_identity_is_one)
{
	EXPECT_FLOAT_EQ(1.0f, determinant(mat4::identity()));
}

TEST(mat4, determinant_of_scaling_is_the_product_of_the_scales)
{
	EXPECT_NEAR(24.0f, determinant(mat4::scaling(2.0f, 3.0f, 4.0f)), 1e-4f);
}

TEST(mat4, determinant_of_translation_is_one)
{
	EXPECT_FLOAT_EQ(1.0f, determinant(mat4::translation(5.0f, -3.0f, 2.0f)));
}

TEST(mat4, determinant_of_rotation_is_one)
{
	mat4 r = mat4::from_rotation(vec4 { 1.0f, 2.0f, 3.0f, 0.0f }, 0.9f);
	EXPECT_NEAR(1.0f, determinant(r), 1e-5f);
}

TEST(mat4, determinant_of_a_singular_matrix_is_zero)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	EXPECT_NEAR(0.0f, determinant(m), 1e-3f);
}

TEST(mat4, determinant_block_diagonal)
{
	// rows (1,2,0,0) (3,4,0,0) (0,0,5,6) (0,0,7,8):
	// det = (1*4 - 2*3) * (5*8 - 6*7) = (-2) * (-2) = 4
	mat4 m = { 1.0f, 3.0f, 0.0f, 0.0f,
			   2.0f, 4.0f, 0.0f, 0.0f,
			   0.0f, 0.0f, 5.0f, 7.0f,
			   0.0f, 0.0f, 6.0f, 8.0f };
	EXPECT_NEAR(4.0f, determinant(m), 1e-4f);
}

TEST(mat4, determinant_is_invariant_under_transpose)
{
	mat4 m = {  2.0f,  1.0f, 0.0f,  3.0f,
			   -1.0f,  4.0f, 2.0f,  0.0f,
				0.0f, -2.0f, 5.0f,  1.0f,
				3.0f,  0.0f, 1.0f, -1.0f };
	EXPECT_NEAR(float(determinant(m)), float(determinant(mat4(transpose(m)))), 1e-3f);
}

TEST(mat4, determinant_is_multiplicative)
{
	mat4 a = mat4::scaling(2.0f, 3.0f, 4.0f);
	mat4 b = mat4::from_rotation(vec4 { 0.0f, 1.0f, 0.0f, 0.0f }, 0.6f);
	EXPECT_NEAR(float(determinant(a)) * float(determinant(b)),
				float(determinant(mat4(a * b))), 1e-3f);
}

TEST(mat4, determinant_is_scalar_expr)
{
	mat4 m = mat4::identity();
	EXPECT_TRUE((scalar_expr<decltype(determinant(m))>));
}

TEST(mat4, determinant_times_literal_collapses)
{
	mat4 m = mat4::identity();

	auto r = determinant(m) * 2.0f;

	EXPECT_TRUE((!std::same_as<decltype(r), float>));
	EXPECT_TRUE((scalar_expr<decltype(r)>));
}

// ---------------------------------------------------------------------------
// Inverse
// ---------------------------------------------------------------------------

TEST(mat4, inverse_of_identity_is_identity)
{
	mat4 check = mat4::identity();
	mat4 result = inverse(mat4::identity());
	EXPECT_TRUE(approx_eq(check, result));
}

TEST(mat4, inverse_times_self_is_identity)
{
	mat4 m = mat4::translation(1.0f, 2.0f, 3.0f)
			 * mat4(mat4::from_rotation(vec4 { 0.3f, 0.5f, -0.8f, 0.0f }, 0.7f)
					* mat4::scaling(2.0f, 0.5f, 3.0f));
	mat4 check = mat4::identity();
	EXPECT_TRUE(approx_eq(check, mat4(m * inverse(m)), 1e-5f));
	EXPECT_TRUE(approx_eq(check, mat4(mat4(inverse(m)) * m), 1e-5f));
}

TEST(mat4, inverse_of_translation_negates_it)
{
	mat4 check = mat4::translation(-1.0f, -2.0f, -3.0f);
	mat4 result = inverse(mat4::translation(1.0f, 2.0f, 3.0f));
	EXPECT_TRUE(approx_eq(check, result, 1e-6f));
}

TEST(mat4, inverse_of_scaling_reciprocates_it)
{
	mat4 check = mat4::scaling(0.5f, 0.25f, 0.125f);
	mat4 result = inverse(mat4::scaling(2.0f, 4.0f, 8.0f));
	EXPECT_TRUE(approx_eq(check, result, 1e-6f));
}

TEST(mat4, inverse_of_rotation_is_its_transpose)
{
	mat4 r = mat4::from_rotation(vec4 { 1.0f, -2.0f, 0.5f, 0.0f }, 1.1f);
	mat4 check = transpose(r);
	mat4 result = inverse(r);
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(mat4, inverse_is_involutive)
{
	mat4 check = {  2.0f,  1.0f, 0.0f,  3.0f,
				   -1.0f,  4.0f, 2.0f,  0.0f,
					0.0f, -2.0f, 5.0f,  1.0f,
					3.0f,  0.0f, 1.0f, -1.0f };
	mat4 result = inverse(mat4(inverse(check)));
	EXPECT_TRUE(approx_eq(check, result, 1e-3f));
}

TEST(mat4, inverse_undoes_a_transform)
{
	mat4 m = mat4::translation(4.0f, -1.0f, 2.0f)
			 * mat4::from_rotation(vec4 { 0.0f, 0.0f, 1.0f, 0.0f }, 0.4f);
	vec4 check = { 1.0f, 2.0f, 3.0f, 1.0f };
	vec4 there = m * check;
	vec4 result = mat4(inverse(m)) * there;
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(mat4, inverse_of_singular_is_not_finite)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	mat4 result = inverse(m);
	EXPECT_FALSE(std::isfinite(result.at<0, 0>()));
}

TEST(mat4, inverse_is_mat_expr)
{
	mat4 m = mat4::identity();
	EXPECT_TRUE((mat_expr<decltype(inverse(m))>));
}

// ---------------------------------------------------------------------------
// View and projection
// ---------------------------------------------------------------------------

TEST(mat4, look_at_maps_the_eye_to_the_origin)
{
	vec4 eye = { 3.0f, 4.0f, 5.0f, 1.0f };
	mat4 view = mat4::look_at(eye, vec4 { 0.0f, 0.0f, 0.0f, 1.0f }, vec4::unit_y());
	vec4 check = { 0.0f, 0.0f, 0.0f, 1.0f };
	vec4 result = view * eye;
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(mat4, look_at_puts_the_target_down_negative_z)
{
	vec4 eye = { 0.0f, 0.0f, 5.0f, 1.0f };
	vec4 target = { 0.0f, 0.0f, 0.0f, 1.0f };
	mat4 view = mat4::look_at(eye, target, vec4::unit_y());
	vec4 check = { 0.0f, 0.0f, -5.0f, 1.0f };
	vec4 result = view * target;
	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(mat4, look_at_preserves_distances)
{
	mat4 view = mat4::look_at(vec4 { 3.0f, 4.0f, 5.0f, 1.0f },
							  vec4 { 1.0f, 0.0f, -2.0f, 1.0f },
							  vec4::unit_y());
	vec4 a = { 1.0f, 2.0f, 3.0f, 1.0f };
	vec4 b = { -2.0f, 0.5f, 4.0f, 1.0f };
	EXPECT_NEAR(distance3(a, b), distance3(vec4(view * a), vec4(view * b)), 1e-4f);
	EXPECT_NEAR(1.0f, determinant(view), 1e-5f);
}

TEST(mat4, perspective_maps_the_near_plane_to_zero)
{
	mat4 proj = mat4::perspective(1.0471975f, 16.0f / 9.0f, 0.1f, 100.0f);
	vec4 clip = proj * vec4 { 0.0f, 0.0f, -0.1f, 1.0f };
	EXPECT_NEAR(0.0f, clip.z() / clip.w(), 1e-5f);
}

TEST(mat4, perspective_maps_the_far_plane_to_one)
{
	mat4 proj = mat4::perspective(1.0471975f, 16.0f / 9.0f, 0.1f, 100.0f);
	vec4 clip = proj * vec4 { 0.0f, 0.0f, -100.0f, 1.0f };
	EXPECT_NEAR(1.0f, clip.z() / clip.w(), 1e-5f);
}

TEST(mat4, perspective_w_carries_the_view_depth)
{
	mat4 proj = mat4::perspective(1.0471975f, 1.0f, 0.5f, 50.0f);
	vec4 clip = proj * vec4 { 1.0f, 1.0f, -4.0f, 1.0f };
	EXPECT_NEAR(4.0f, clip.w(), 1e-5f);
}

TEST(mat4, perspective_divides_x_by_the_aspect_ratio)
{
	const float fov = 1.5707963f;   // 90 degrees, so tan(fov / 2) is 1
	mat4 proj = mat4::perspective(fov, 2.0f, 0.1f, 100.0f);
	vec4 clip = proj * vec4 { 2.0f, 1.0f, -1.0f, 1.0f };
	EXPECT_NEAR(1.0f, clip.x(), 1e-5f);
	EXPECT_NEAR(1.0f, clip.y(), 1e-5f);
}

TEST(mat4, orthographic_maps_the_depth_range_to_zero_one)
{
	mat4 proj = mat4::orthographic(-2.0f, 2.0f, -1.0f, 1.0f, 0.5f, 50.0f);
	vec4 near_clip = proj * vec4 { 0.0f, 0.0f, -0.5f, 1.0f };
	vec4 far_clip = proj * vec4 { 0.0f, 0.0f, -50.0f, 1.0f };
	EXPECT_NEAR(0.0f, near_clip.z(), 1e-5f);
	EXPECT_NEAR(1.0f, far_clip.z(), 1e-5f);
}

TEST(mat4, orthographic_maps_the_box_corner_to_the_cube_corner)
{
	mat4 proj = mat4::orthographic(-2.0f, 2.0f, -1.0f, 1.0f, 0.5f, 50.0f);
	vec4 corner = proj * vec4 { 2.0f, 1.0f, -0.5f, 1.0f };
	EXPECT_NEAR(1.0f, corner.x(), 1e-5f);
	EXPECT_NEAR(1.0f, corner.y(), 1e-5f);
	EXPECT_NEAR(1.0f, corner.w(), 1e-5f);
}

TEST(mat4, orthographic_off_centre_box_maps_its_centre_to_the_origin)
{
	mat4 proj = mat4::orthographic(1.0f, 5.0f, 2.0f, 6.0f, 0.5f, 50.0f);
	vec4 centre = proj * vec4 { 3.0f, 4.0f, -0.5f, 1.0f };
	EXPECT_NEAR(0.0f, centre.x(), 1e-5f);
	EXPECT_NEAR(0.0f, centre.y(), 1e-5f);
}

}
