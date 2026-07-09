#include "tenvex.h"

// Compile-time protocol boundary tests: the full operand matrix for every
// public operation. A runtime test cannot fail when an overload set
// silently widens - that negative space is only testable here.
//
// Negative checks go through can_* concepts: outside a template GCC treats
// an invalid non-dependent expression as a hard error instead of false.

namespace tnvx::protocol_tests
{

template<typename L, typename R> concept can_add          = requires (L l, R r) { l + r; };
template<typename L, typename R> concept can_sub          = requires (L l, R r) { l - r; };
template<typename L, typename R> concept can_mul          = requires (L l, R r) { l * r; };
template<typename L, typename R> concept can_div          = requires (L l, R r) { l / r; };
template<typename L, typename R> concept can_eq           = requires (L l, R r) { l == r; };
template<typename L, typename R> concept can_dot3         = requires (L l, R r) { dot3(l, r); };
template<typename L, typename R> concept can_dot4         = requires (L l, R r) { dot4(l, r); };
template<typename L, typename R> concept can_cross3       = requires (L l, R r) { cross3(l, r); };
template<typename L, typename R> concept can_hadamard     = requires (L l, R r) { hadamard(l, r); };
template<typename L, typename R> concept can_min          = requires (L l, R r) { min(l, r); };
template<typename L, typename R> concept can_max          = requires (L l, R r) { max(l, r); };
template<typename L, typename R> concept can_with_w       = requires (L l, R r) { with_w(l, r); };
template<typename L, typename R> concept can_rotate       = requires (L l, R r) { rotate(l, r); };
template<typename L, typename R> concept can_distance3    = requires (L l, R r) { distance3(l, r); };
template<typename L, typename R> concept can_distance3_sq = requires (L l, R r) { distance3_sq(l, r); };
template<typename L, typename R> concept can_lerp         = requires (L l, R r) { lerp(l, r, 0.5f); };
template<typename L, typename R> concept can_slerp        = requires (L l, R r) { slerp(l, r, 0.5f); };
template<typename L, typename R> concept can_nlerp        = requires (L l, R r) { nlerp(l, r, 0.5f); };
template<typename L, typename R> concept can_clamp        = requires (L l, R r) { clamp(l, l, r); };

template<typename E> concept can_neg             = requires (E e) { -e; };
template<typename E> concept can_abs             = requires (E e) { abs(e); };
template<typename E> concept can_floor           = requires (E e) { floor(e); };
template<typename E> concept can_ceil            = requires (E e) { ceil(e); };
template<typename E> concept can_round           = requires (E e) { round(e); };
template<typename E> concept can_frac            = requires (E e) { frac(e); };
template<typename E> concept can_magnitude3      = requires (E e) { magnitude3(e); };
template<typename E> concept can_magnitude3_sq   = requires (E e) { magnitude3_sq(e); };
template<typename E> concept can_magnitude4      = requires (E e) { magnitude4(e); };
template<typename E> concept can_magnitude4_sq   = requires (E e) { magnitude4_sq(e); };
template<typename E> concept can_normalize3      = requires (E e) { normalize3(e); };
template<typename E> concept can_normalize3_fast = requires (E e) { normalize3_fast(e); };
template<typename E> concept can_normalize4      = requires (E e) { normalize4(e); };
template<typename E> concept can_conjugate       = requires (E e) { conjugate(e); };
template<typename E> concept can_inverse         = requires (E e) { inverse(e); };
template<typename E> concept can_saturate        = requires (E e) { saturate(e); };
template<typename E> concept can_orthogonal      = requires (E e) { orthogonal(e); };

static_assert(vec_expr<vec4>);
static_assert(quat_expr<quat>);
static_assert(scalar_expr<Scalar>);
static_assert(packed_expr<vec4>);
static_assert(packed_expr<quat>);
static_assert(!scalar_expr<vec4>);
static_assert(!vec_expr<quat>);
static_assert(!quat_expr<vec4>);

static_assert(std::same_as<vec4::result_t, vf4>);
static_assert(std::same_as<quat::result_t, vf4>);

static_assert(!expression<float>);
static_assert(!expression<vf4>);

static_assert(vec_expr<decltype(vec4{} + vec4{})>);
static_assert(quat_expr<decltype(quat{} + quat{})>);
static_assert(vec_expr<decltype(vec4{} * 2.0f)>);
static_assert(quat_expr<decltype(quat{} * 2.0f)>);
static_assert(vec_expr<decltype(vec4{} / 2.0f)>);
static_assert(quat_expr<decltype(quat{} / 2.0f)>);
static_assert(scalar_expr<decltype(dot3(vec4{}, vec4{}))>);
static_assert(scalar_expr<decltype(dot4(quat{}, quat{}))>);
static_assert(scalar_expr<decltype(dot3(vec4{}, vec4{}) + 1.0f)>);
static_assert(vec_expr<decltype(normalize3(vec4{}))>);
static_assert(quat_expr<decltype(normalize3(quat{}))>);
static_assert(vec_expr<decltype(normalize4(vec4{}))>);
static_assert(quat_expr<decltype(normalize4(quat{}))>);
static_assert(vec_expr<decltype(rotate(vec4{}, quat{}))>);

static_assert(can_add<vec4, vec4>);
static_assert(!can_add<vec4, quat>);
static_assert(!can_add<vec4, Scalar>);
static_assert(!can_add<vec4, float>);
static_assert(!can_add<quat, vec4>);
static_assert(can_add<quat, quat>);
static_assert(!can_add<quat, Scalar>);
static_assert(!can_add<quat, float>);
static_assert(!can_add<Scalar, vec4>);
static_assert(!can_add<Scalar, quat>);
static_assert(can_add<Scalar, Scalar>);
static_assert(can_add<Scalar, float>);
static_assert(!can_add<float, vec4>);
static_assert(!can_add<float, quat>);
static_assert(can_add<float, Scalar>);
static_assert(can_add<float, float>);

static_assert(can_sub<vec4, vec4>);
static_assert(!can_sub<vec4, quat>);
static_assert(!can_sub<vec4, Scalar>);
static_assert(!can_sub<vec4, float>);
static_assert(!can_sub<quat, vec4>);
static_assert(can_sub<quat, quat>);
static_assert(!can_sub<quat, Scalar>);
static_assert(!can_sub<quat, float>);
static_assert(!can_sub<Scalar, vec4>);
static_assert(!can_sub<Scalar, quat>);
static_assert(can_sub<Scalar, Scalar>);
static_assert(can_sub<Scalar, float>);
static_assert(!can_sub<float, vec4>);
static_assert(!can_sub<float, quat>);
static_assert(can_sub<float, Scalar>);
static_assert(can_sub<float, float>);

static_assert(!can_mul<vec4, vec4>);
static_assert(!can_mul<vec4, quat>);
static_assert(can_mul<vec4, Scalar>);
static_assert(can_mul<vec4, float>);
static_assert(!can_mul<quat, vec4>);
static_assert(can_mul<quat, quat>);
static_assert(can_mul<quat, Scalar>);
static_assert(can_mul<quat, float>);
static_assert(can_mul<Scalar, vec4>);
static_assert(can_mul<Scalar, quat>);
static_assert(can_mul<Scalar, Scalar>);
static_assert(can_mul<Scalar, float>);
static_assert(can_mul<float, vec4>);
static_assert(can_mul<float, quat>);
static_assert(can_mul<float, Scalar>);
static_assert(can_mul<float, float>);

static_assert(!can_div<vec4, vec4>);
static_assert(!can_div<vec4, quat>);
static_assert(can_div<vec4, Scalar>);
static_assert(can_div<vec4, float>);
static_assert(!can_div<quat, vec4>);
static_assert(!can_div<quat, quat>);
static_assert(can_div<quat, Scalar>);
static_assert(can_div<quat, float>);
static_assert(!can_div<Scalar, vec4>);
static_assert(!can_div<Scalar, quat>);
static_assert(!can_div<Scalar, Scalar>);
static_assert(!can_div<Scalar, float>);
static_assert(!can_div<float, vec4>);
static_assert(!can_div<float, quat>);
static_assert(!can_div<float, Scalar>);
static_assert(can_div<float, float>);

static_assert(can_eq<vec4, vec4>);
static_assert(!can_eq<vec4, quat>);
static_assert(!can_eq<vec4, Scalar>);
static_assert(!can_eq<vec4, float>);
static_assert(!can_eq<quat, vec4>);
static_assert(can_eq<quat, quat>);
static_assert(!can_eq<quat, Scalar>);
static_assert(!can_eq<quat, float>);
static_assert(!can_eq<Scalar, vec4>);
static_assert(!can_eq<Scalar, quat>);
static_assert(!can_eq<Scalar, Scalar>);
static_assert(!can_eq<Scalar, float>);
static_assert(!can_eq<float, vec4>);
static_assert(!can_eq<float, quat>);
static_assert(!can_eq<float, Scalar>);
static_assert(can_eq<float, float>);

static_assert(can_dot3<vec4, vec4>);
static_assert(!can_dot3<vec4, quat>);
static_assert(!can_dot3<vec4, Scalar>);
static_assert(!can_dot3<quat, vec4>);
static_assert(!can_dot3<quat, quat>);
static_assert(!can_dot3<quat, Scalar>);
static_assert(!can_dot3<Scalar, vec4>);
static_assert(!can_dot3<Scalar, quat>);
static_assert(!can_dot3<Scalar, Scalar>);

static_assert(can_dot4<vec4, vec4>);
static_assert(!can_dot4<vec4, quat>);
static_assert(!can_dot4<vec4, Scalar>);
static_assert(!can_dot4<quat, vec4>);
static_assert(can_dot4<quat, quat>);
static_assert(!can_dot4<quat, Scalar>);
static_assert(!can_dot4<Scalar, vec4>);
static_assert(!can_dot4<Scalar, quat>);
static_assert(!can_dot4<Scalar, Scalar>);

static_assert(can_cross3<vec4, vec4>);
static_assert(!can_cross3<vec4, quat>);
static_assert(!can_cross3<vec4, Scalar>);
static_assert(!can_cross3<quat, vec4>);
static_assert(!can_cross3<quat, quat>);
static_assert(!can_cross3<quat, Scalar>);
static_assert(!can_cross3<Scalar, vec4>);
static_assert(!can_cross3<Scalar, quat>);
static_assert(!can_cross3<Scalar, Scalar>);

static_assert(can_hadamard<vec4, vec4>);
static_assert(!can_hadamard<vec4, quat>);
static_assert(!can_hadamard<vec4, Scalar>);
static_assert(!can_hadamard<quat, vec4>);
static_assert(!can_hadamard<quat, quat>);
static_assert(!can_hadamard<quat, Scalar>);
static_assert(!can_hadamard<Scalar, vec4>);
static_assert(!can_hadamard<Scalar, quat>);
static_assert(!can_hadamard<Scalar, Scalar>);

static_assert(can_min<vec4, vec4>);
static_assert(!can_min<vec4, quat>);
static_assert(!can_min<vec4, Scalar>);
static_assert(!can_min<quat, vec4>);
static_assert(!can_min<quat, quat>);
static_assert(!can_min<quat, Scalar>);
static_assert(!can_min<Scalar, vec4>);
static_assert(!can_min<Scalar, quat>);
static_assert(!can_min<Scalar, Scalar>);

static_assert(can_max<vec4, vec4>);
static_assert(!can_max<vec4, quat>);
static_assert(!can_max<vec4, Scalar>);
static_assert(!can_max<quat, vec4>);
static_assert(!can_max<quat, quat>);
static_assert(!can_max<quat, Scalar>);
static_assert(!can_max<Scalar, vec4>);
static_assert(!can_max<Scalar, quat>);
static_assert(!can_max<Scalar, Scalar>);

static_assert(can_with_w<vec4, vec4>);
static_assert(!can_with_w<vec4, quat>);
static_assert(!can_with_w<vec4, Scalar>);
static_assert(!can_with_w<quat, vec4>);
static_assert(!can_with_w<quat, quat>);
static_assert(!can_with_w<quat, Scalar>);
static_assert(!can_with_w<Scalar, vec4>);
static_assert(!can_with_w<Scalar, quat>);
static_assert(!can_with_w<Scalar, Scalar>);

static_assert(!can_rotate<vec4, vec4>);
static_assert(can_rotate<vec4, quat>);
static_assert(!can_rotate<vec4, Scalar>);
static_assert(!can_rotate<quat, vec4>);
static_assert(!can_rotate<quat, quat>);
static_assert(!can_rotate<quat, Scalar>);
static_assert(!can_rotate<Scalar, vec4>);
static_assert(!can_rotate<Scalar, quat>);
static_assert(!can_rotate<Scalar, Scalar>);

static_assert(can_distance3<vec4, vec4>);
static_assert(!can_distance3<vec4, quat>);
static_assert(!can_distance3<vec4, Scalar>);
static_assert(!can_distance3<quat, vec4>);
static_assert(!can_distance3<quat, quat>);
static_assert(!can_distance3<quat, Scalar>);
static_assert(!can_distance3<Scalar, vec4>);
static_assert(!can_distance3<Scalar, quat>);
static_assert(!can_distance3<Scalar, Scalar>);

static_assert(can_distance3_sq<vec4, vec4>);
static_assert(!can_distance3_sq<vec4, quat>);
static_assert(!can_distance3_sq<vec4, Scalar>);
static_assert(!can_distance3_sq<quat, vec4>);
static_assert(!can_distance3_sq<quat, quat>);
static_assert(!can_distance3_sq<quat, Scalar>);
static_assert(!can_distance3_sq<Scalar, vec4>);
static_assert(!can_distance3_sq<Scalar, quat>);
static_assert(!can_distance3_sq<Scalar, Scalar>);

static_assert(can_lerp<vec4, vec4>);
static_assert(!can_lerp<vec4, quat>);
static_assert(!can_lerp<vec4, Scalar>);
static_assert(!can_lerp<quat, vec4>);
static_assert(!can_lerp<quat, quat>);
static_assert(!can_lerp<quat, Scalar>);
static_assert(!can_lerp<Scalar, vec4>);
static_assert(!can_lerp<Scalar, quat>);
static_assert(!can_lerp<Scalar, Scalar>);

static_assert(!can_slerp<vec4, vec4>);
static_assert(!can_slerp<vec4, quat>);
static_assert(!can_slerp<vec4, Scalar>);
static_assert(!can_slerp<quat, vec4>);
static_assert(can_slerp<quat, quat>);
static_assert(!can_slerp<quat, Scalar>);
static_assert(!can_slerp<Scalar, vec4>);
static_assert(!can_slerp<Scalar, quat>);
static_assert(!can_slerp<Scalar, Scalar>);

static_assert(!can_nlerp<vec4, vec4>);
static_assert(!can_nlerp<vec4, quat>);
static_assert(!can_nlerp<vec4, Scalar>);
static_assert(!can_nlerp<quat, vec4>);
static_assert(can_nlerp<quat, quat>);
static_assert(!can_nlerp<quat, Scalar>);
static_assert(!can_nlerp<Scalar, vec4>);
static_assert(!can_nlerp<Scalar, quat>);
static_assert(!can_nlerp<Scalar, Scalar>);

static_assert(can_clamp<vec4, vec4>);
static_assert(!can_clamp<vec4, quat>);
static_assert(!can_clamp<vec4, Scalar>);
static_assert(!can_clamp<quat, vec4>);
static_assert(!can_clamp<quat, quat>);
static_assert(!can_clamp<quat, Scalar>);
static_assert(!can_clamp<Scalar, vec4>);
static_assert(!can_clamp<Scalar, quat>);
static_assert(!can_clamp<Scalar, Scalar>);

static_assert(can_neg<vec4>);
static_assert(can_neg<quat>);
static_assert(can_neg<Scalar>);

static_assert(can_abs<vec4>);
static_assert(!can_abs<quat>);
static_assert(!can_abs<Scalar>);

static_assert(can_floor<vec4>);
static_assert(!can_floor<quat>);
static_assert(!can_floor<Scalar>);

static_assert(can_ceil<vec4>);
static_assert(!can_ceil<quat>);
static_assert(!can_ceil<Scalar>);

static_assert(can_round<vec4>);
static_assert(!can_round<quat>);
static_assert(!can_round<Scalar>);

static_assert(can_frac<vec4>);
static_assert(!can_frac<quat>);
static_assert(!can_frac<Scalar>);

static_assert(can_magnitude3<vec4>);
static_assert(!can_magnitude3<quat>);
static_assert(!can_magnitude3<Scalar>);

static_assert(can_magnitude3_sq<vec4>);
static_assert(!can_magnitude3_sq<quat>);
static_assert(!can_magnitude3_sq<Scalar>);

static_assert(can_magnitude4<vec4>);
static_assert(can_magnitude4<quat>);
static_assert(!can_magnitude4<Scalar>);

static_assert(can_magnitude4_sq<vec4>);
static_assert(can_magnitude4_sq<quat>);
static_assert(!can_magnitude4_sq<Scalar>);

static_assert(can_normalize3<vec4>);
static_assert(can_normalize3<quat>);
static_assert(!can_normalize3<Scalar>);

static_assert(can_normalize3_fast<vec4>);
static_assert(can_normalize3_fast<quat>);
static_assert(!can_normalize3_fast<Scalar>);

static_assert(can_normalize4<vec4>);
static_assert(can_normalize4<quat>);
static_assert(!can_normalize4<Scalar>);

static_assert(!can_conjugate<vec4>);
static_assert(can_conjugate<quat>);
static_assert(!can_conjugate<Scalar>);

static_assert(!can_inverse<vec4>);
static_assert(can_inverse<quat>);
static_assert(!can_inverse<Scalar>);

static_assert(can_saturate<vec4>);
static_assert(!can_saturate<quat>);
static_assert(!can_saturate<Scalar>);

static_assert(can_orthogonal<vec4>);
static_assert(!can_orthogonal<quat>);
static_assert(!can_orthogonal<Scalar>);

}
