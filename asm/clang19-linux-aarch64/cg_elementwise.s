# Debian clang version 19.1.7 (3+b1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_elementwise.cpp
	.text
	.file	"cg_elementwise.cpp"
	.globl	cg_aabb                         // -- Begin function cg_aabb
	.p2align	2
	.type	cg_aabb,@function
cg_aabb:                                // @cg_aabb
	.cfi_startproc
// %bb.0:
	ldr	q0, [x0]
	cmp	x1, #2
	b.lo	.LBB0_4
// %bb.1:
	mov	v1.16b, v0.16b
	sub	x8, x1, #1
	add	x9, x0, #16
.LBB0_2:                                // =>This Inner Loop Header: Depth=1
	ldr	q2, [x9], #16
	subs	x8, x8, #1
	fmin	v0.4s, v0.4s, v2.4s
	fmax	v1.4s, v1.4s, v2.4s
	b.ne	.LBB0_2
// %bb.3:
	str	q0, [x2]
	str	q1, [x3]
	ret
.LBB0_4:
	mov	v1.16b, v0.16b
	str	q0, [x2]
	str	q1, [x3]
	ret
.Lfunc_end0:
	.size	cg_aabb, .Lfunc_end0-cg_aabb
	.cfi_endproc
                                        // -- End function
	.globl	cg_saturate                     // -- Begin function cg_saturate
	.p2align	2
	.type	cg_saturate,@function
cg_saturate:                            // @cg_saturate
	.cfi_startproc
// %bb.0:
	cbz	x2, .LBB1_3
// %bb.1:
	movi	v0.2d, #0000000000000000
	fmov	v1.4s, #1.00000000
.LBB1_2:                                // =>This Inner Loop Header: Depth=1
	ldr	q2, [x0], #16
	subs	x2, x2, #1
	fmax	v2.4s, v2.4s, v0.4s
	fmin	v2.4s, v2.4s, v1.4s
	str	q2, [x1], #16
	b.ne	.LBB1_2
.LBB1_3:
	ret
.Lfunc_end1:
	.size	cg_saturate, .Lfunc_end1-cg_saturate
	.cfi_endproc
                                        // -- End function
	.globl	cg_with_w_expr                  // -- Begin function cg_with_w_expr
	.p2align	2
	.type	cg_with_w_expr,@function
cg_with_w_expr:                         // @cg_with_w_expr
	.cfi_startproc
// %bb.0:
	cbz	x3, .LBB2_2
.LBB2_1:                                // =>This Inner Loop Header: Depth=1
	ldr	q0, [x0], #16
	subs	x3, x3, #1
	ldr	q1, [x1], #16
	fadd	v1.4s, v0.4s, v1.4s
	mov	v1.s[3], v0.s[3]
	str	q1, [x2], #16
	b.ne	.LBB2_1
.LBB2_2:
	ret
.Lfunc_end2:
	.size	cg_with_w_expr, .Lfunc_end2-cg_with_w_expr
	.cfi_endproc
                                        // -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"Debian clang version 19.1.7 (3+b1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_aabb
	.addrsig_sym cg_saturate
	.addrsig_sym cg_with_w_expr
	.addrsig_sym __gxx_personality_v0
