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

}
