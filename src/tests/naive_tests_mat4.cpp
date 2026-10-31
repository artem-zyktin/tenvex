#include "naive/naive_mat4.h"

#include "gtest/gtest.h"

#include <cmath>

namespace naive
{

TEST(naive_mat4, ctor_scalar_is_column_major)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	vec4 check = { 1.0f, 2.0f, 3.0f, 4.0f };
	vec4 result = m.col(0);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, ctor_scalar_last_column)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	vec4 check = { 13.0f, 14.0f, 15.0f, 16.0f };
	vec4 result = m.col(3);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, ctor_vec4_columns)
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

TEST(naive_mat4, at_matches_col)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	float check = m.col(1).z();
	float result = m.at(2, 1);

	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_mat4, zero_is_all_zeroes)
{
	mat4 check = { 0.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 0.0f, 0.0f };
	mat4 result = mat4::zero();

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, identity_matches_unit_scaling)
{
	mat4 check = mat4::identity();
	mat4 result = mat4::scaling(1.0f);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, scaling_uniform_matches_xyz)
{
	mat4 check = mat4::scaling(2.5f, 2.5f, 2.5f);
	mat4 result = mat4::scaling(2.5f);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, scaling_vec4_matches_scalar)
{
	mat4 check = mat4::scaling(2.0f, 3.0f, 4.0f);
	mat4 result = mat4::scaling(vec4 { 2.0f, 3.0f, 4.0f, 1.0f });

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, scaling_keeps_w_one)
{
	mat4 m = mat4::scaling(2.0f, 3.0f, 4.0f);
	float check = 1.0f;
	float result = m.at(3, 3);

	EXPECT_FLOAT_EQ(check, result);
}

TEST(naive_mat4, translation_lands_in_last_column)
{
	mat4 check = { 1.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 1.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 1.0f, 0.0f,
				   4.0f, 5.0f, 6.0f, 1.0f };
	mat4 result = mat4::translation(4.0f, 5.0f, 6.0f);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, translation_scalar_matches_vec4)
{
	mat4 check = mat4::translation(vec4 { 4.0f, 5.0f, 6.0f, 1.0f });
	mat4 result = mat4::translation(4.0f, 5.0f, 6.0f);

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, translation_ignores_input_w)
{
	mat4 check = mat4::translation(vec4 { 4.0f, 5.0f, 6.0f, 1.0f });
	mat4 result = mat4::translation(vec4 { 4.0f, 5.0f, 6.0f, 7.0f });

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, from_quat_identity_is_identity)
{
	mat4 check = mat4::identity();
	mat4 result = mat4::from_quat(quat::identity());

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, from_quat_z90_matches_literal)
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

TEST(naive_mat4, from_quat_columns_are_rotated_basis)
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

TEST(naive_mat4, from_rotation_matches_from_quat)
{
	constexpr float pi = 3.14159265f;
	vec4 axis = { 1.0f, 2.0f, 3.0f, 0.0f };
	mat4 check = mat4::from_quat(quat::from_axis_angle(axis, pi / 3.0f));
	mat4 result = mat4::from_rotation(axis, pi / 3.0f);

	EXPECT_TRUE(approx_eq(check, result));
}

// ---------------------------------------------------------------------------
// Transform, product, transpose
// ---------------------------------------------------------------------------

TEST(naive_mat4, transform_matches_hand_computed)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	vec4 check = { 90.0f, 100.0f, 110.0f, 120.0f };
	vec4 result = m * vec4 { 1.0f, 2.0f, 3.0f, 4.0f };

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, transform_named_matches_operator)
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

TEST(naive_mat4, transform_translates_a_point)
{
	mat4 t = mat4::translation(1.0f, 2.0f, 3.0f);
	vec4 check = { 11.0f, 22.0f, 33.0f, 1.0f };
	vec4 result = t * vec4 { 10.0f, 20.0f, 30.0f, 1.0f };

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, transform_leaves_a_direction_untranslated)
{
	mat4 t = mat4::translation(1.0f, 2.0f, 3.0f);
	vec4 check = { 10.0f, 20.0f, 30.0f, 0.0f };
	vec4 result = t * check;

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, transform_by_rotation_matches_quat_rotate)
{
	constexpr float pi = 3.14159265f;
	quat q = quat::from_axis_angle(vec4 { 1.0f, 2.0f, 3.0f, 0.0f }, pi / 3.0f);
	vec4 v = { 0.4f, -1.2f, 2.5f, 0.0f };
	vec4 check = rotate(v, q);
	vec4 result = mat4::from_quat(q) * v;

	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(naive_mat4, product_matches_hand_computed)
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

TEST(naive_mat4, product_with_identity_is_a_noop)
{
	mat4 check = {  1.0f,  2.0f,  3.0f,  4.0f,
					5.0f,  6.0f,  7.0f,  8.0f,
					9.0f, 10.0f, 11.0f, 12.0f,
				   13.0f, 14.0f, 15.0f, 16.0f };

	EXPECT_TRUE(approx_eq(check, check * mat4::identity()));
	EXPECT_TRUE(approx_eq(check, mat4::identity() * check));
}

TEST(naive_mat4, product_applies_right_to_left)
{
	mat4 t = mat4::translation(1.0f, 2.0f, 3.0f);
	mat4 s = mat4::scaling(2.0f);
	vec4 p = { 1.0f, 0.0f, 0.0f, 1.0f };
	vec4 check = t * (s * p);
	vec4 result = (t * s) * p;

	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(naive_mat4, transpose_swaps_rows_and_columns)
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

TEST(naive_mat4, transpose_is_involutive)
{
	mat4 check = {  1.0f,  2.0f,  3.0f,  4.0f,
					5.0f,  6.0f,  7.0f,  8.0f,
					9.0f, 10.0f, 11.0f, 12.0f,
				   13.0f, 14.0f, 15.0f, 16.0f };
	mat4 result = transpose(transpose(check));

	EXPECT_TRUE(approx_eq(check, result));
}

// ---------------------------------------------------------------------------
// Element-wise arithmetic
// ---------------------------------------------------------------------------

TEST(naive_mat4, add_doubles_every_lane)
{
	mat4 m = mat4::identity();
	mat4 check = m * 2.0f;
	mat4 result = m + m;

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, sub_of_self_is_zero)
{
	mat4 m = mat4::identity();
	mat4 check = mat4::zero();
	mat4 result = m - m;

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, neg_cancels_under_add)
{
	mat4 m = mat4::identity();
	mat4 check = mat4::zero();
	mat4 result = m + -m;

	EXPECT_TRUE(approx_eq(check, result));
}

TEST(naive_mat4, mul_float_on_either_side)
{
	mat4 m = mat4::identity();
	mat4 check = m * 2.0f;
	mat4 result = 2.0f * m;

	EXPECT_TRUE(approx_eq(check, result));
}

// ---------------------------------------------------------------------------
// Determinant and inverse
// ---------------------------------------------------------------------------

TEST(naive_mat4, determinant_of_identity_is_one)
{
	EXPECT_FLOAT_EQ(1.0f, determinant(mat4::identity()));
}

TEST(naive_mat4, determinant_of_scaling_is_the_product_of_the_scales)
{
	EXPECT_NEAR(24.0f, determinant(mat4::scaling(2.0f, 3.0f, 4.0f)), 1e-4f);
}

TEST(naive_mat4, determinant_of_a_singular_matrix_is_zero)
{
	mat4 m = {  1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
			   13.0f, 14.0f, 15.0f, 16.0f };
	EXPECT_NEAR(0.0f, determinant(m), 1e-3f);
}

TEST(naive_mat4, determinant_block_diagonal)
{
	mat4 m = { 1.0f, 3.0f, 0.0f, 0.0f,
			   2.0f, 4.0f, 0.0f, 0.0f,
			   0.0f, 0.0f, 5.0f, 7.0f,
			   0.0f, 0.0f, 6.0f, 8.0f };
	EXPECT_NEAR(4.0f, determinant(m), 1e-4f);
}

TEST(naive_mat4, inverse_times_self_is_identity)
{
	mat4 m = mat4::translation(1.0f, 2.0f, 3.0f)
			 * (mat4::from_rotation(vec4 { 0.3f, 0.5f, -0.8f, 0.0f }, 0.7f)
				* mat4::scaling(2.0f, 0.5f, 3.0f));
	mat4 check = mat4::identity();

	EXPECT_TRUE(approx_eq(check, m * inverse(m), 1e-5f));
}

TEST(naive_mat4, inverse_of_translation_negates_it)
{
	mat4 check = mat4::translation(-1.0f, -2.0f, -3.0f);
	mat4 result = inverse(mat4::translation(1.0f, 2.0f, 3.0f));

	EXPECT_TRUE(approx_eq(check, result, 1e-6f));
}

TEST(naive_mat4, inverse_of_rotation_is_its_transpose)
{
	mat4 r = mat4::from_rotation(vec4 { 1.0f, -2.0f, 0.5f, 0.0f }, 1.1f);
	mat4 check = transpose(r);
	mat4 result = inverse(r);

	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

// ---------------------------------------------------------------------------
// View and projection
// ---------------------------------------------------------------------------

TEST(naive_mat4, look_at_maps_the_eye_to_the_origin)
{
	vec4 eye = { 3.0f, 4.0f, 5.0f, 1.0f };
	mat4 view = mat4::look_at(eye, vec4 { 0.0f, 0.0f, 0.0f, 1.0f }, vec4::unit_y());
	vec4 check = { 0.0f, 0.0f, 0.0f, 1.0f };
	vec4 result = view * eye;

	EXPECT_TRUE(approx_eq(check, result, 1e-5f));
}

TEST(naive_mat4, perspective_maps_the_depth_range_to_zero_one)
{
	mat4 proj = mat4::perspective(1.0471975f, 16.0f / 9.0f, 0.1f, 100.0f);
	vec4 near_clip = proj * vec4 { 0.0f, 0.0f, -0.1f, 1.0f };
	vec4 far_clip = proj * vec4 { 0.0f, 0.0f, -100.0f, 1.0f };

	EXPECT_NEAR(0.0f, near_clip.z() / near_clip.w(), 1e-5f);
	EXPECT_NEAR(1.0f, far_clip.z() / far_clip.w(), 1e-5f);
}

TEST(naive_mat4, orthographic_maps_the_depth_range_to_zero_one)
{
	mat4 proj = mat4::orthographic(-2.0f, 2.0f, -1.0f, 1.0f, 0.5f, 50.0f);

	EXPECT_NEAR(0.0f, (proj * vec4 { 0.0f, 0.0f, -0.5f, 1.0f }).z(), 1e-5f);
	EXPECT_NEAR(1.0f, (proj * vec4 { 0.0f, 0.0f, -50.0f, 1.0f }).z(), 1e-5f);
}

}
