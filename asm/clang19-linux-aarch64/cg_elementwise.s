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
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          // -- Begin function cg_cross3
.LCPI3_0:
	.byte	4                               // 0x4
	.byte	5                               // 0x5
	.byte	6                               // 0x6
	.byte	7                               // 0x7
	.byte	8                               // 0x8
	.byte	9                               // 0x9
	.byte	10                              // 0xa
	.byte	11                              // 0xb
	.byte	0                               // 0x0
	.byte	1                               // 0x1
	.byte	2                               // 0x2
	.byte	3                               // 0x3
	.byte	12                              // 0xc
	.byte	13                              // 0xd
	.byte	14                              // 0xe
	.byte	15                              // 0xf
.LCPI3_1:
	.byte	8                               // 0x8
	.byte	9                               // 0x9
	.byte	10                              // 0xa
	.byte	11                              // 0xb
	.byte	0                               // 0x0
	.byte	1                               // 0x1
	.byte	2                               // 0x2
	.byte	3                               // 0x3
	.byte	4                               // 0x4
	.byte	5                               // 0x5
	.byte	6                               // 0x6
	.byte	7                               // 0x7
	.byte	12                              // 0xc
	.byte	13                              // 0xd
	.byte	14                              // 0xe
	.byte	15                              // 0xf
	.text
	.globl	cg_cross3
	.p2align	2
	.type	cg_cross3,@function
cg_cross3:                              // @cg_cross3
	.cfi_startproc
// %bb.0:
	cbz	x3, .LBB3_3
// %bb.1:
	adrp	x8, .LCPI3_0
	adrp	x9, .LCPI3_1
	ldr	q0, [x8, :lo12:.LCPI3_0]
	ldr	q1, [x9, :lo12:.LCPI3_1]
.LBB3_2:                                // =>This Inner Loop Header: Depth=1
	ldr	q2, [x0], #16
	subs	x3, x3, #1
	ldr	q3, [x1], #16
	tbl	v4.16b, { v2.16b }, v0.16b
	tbl	v2.16b, { v2.16b }, v1.16b
	tbl	v5.16b, { v3.16b }, v1.16b
	tbl	v3.16b, { v3.16b }, v0.16b
	fmul	v4.4s, v4.4s, v5.4s
	fmul	v2.4s, v2.4s, v3.4s
	fsub	v2.4s, v4.4s, v2.4s
	str	q2, [x2], #16
	b.ne	.LBB3_2
.LBB3_3:
	ret
.Lfunc_end3:
	.size	cg_cross3, .Lfunc_end3-cg_cross3
	.cfi_endproc
                                        // -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          // -- Begin function cg_cross3_value
.LCPI4_0:
	.byte	4                               // 0x4
	.byte	5                               // 0x5
	.byte	6                               // 0x6
	.byte	7                               // 0x7
	.byte	8                               // 0x8
	.byte	9                               // 0x9
	.byte	10                              // 0xa
	.byte	11                              // 0xb
	.byte	0                               // 0x0
	.byte	1                               // 0x1
	.byte	2                               // 0x2
	.byte	3                               // 0x3
	.byte	12                              // 0xc
	.byte	13                              // 0xd
	.byte	14                              // 0xe
	.byte	15                              // 0xf
.LCPI4_1:
	.byte	8                               // 0x8
	.byte	9                               // 0x9
	.byte	10                              // 0xa
	.byte	11                              // 0xb
	.byte	0                               // 0x0
	.byte	1                               // 0x1
	.byte	2                               // 0x2
	.byte	3                               // 0x3
	.byte	4                               // 0x4
	.byte	5                               // 0x5
	.byte	6                               // 0x6
	.byte	7                               // 0x7
	.byte	12                              // 0xc
	.byte	13                              // 0xd
	.byte	14                              // 0xe
	.byte	15                              // 0xf
	.text
	.globl	cg_cross3_value
	.p2align	2
	.type	cg_cross3_value,@function
cg_cross3_value:                        // @cg_cross3_value
	.cfi_startproc
// %bb.0:
	adrp	x8, .LCPI4_0
	ldr	q0, [x0]
	ldr	q2, [x1]
	ldr	q1, [x8, :lo12:.LCPI4_0]
	adrp	x8, .LCPI4_1
	ldr	q3, [x8, :lo12:.LCPI4_1]
	tbl	v4.16b, { v0.16b }, v1.16b
	tbl	v1.16b, { v2.16b }, v1.16b
	tbl	v5.16b, { v2.16b }, v3.16b
	tbl	v0.16b, { v0.16b }, v3.16b
	fmul	v2.4s, v4.4s, v5.4s
	fmul	v0.4s, v0.4s, v1.4s
	fsub	v0.4s, v2.4s, v0.4s
	ret
.Lfunc_end4:
	.size	cg_cross3_value, .Lfunc_end4-cg_cross3_value
	.cfi_endproc
                                        // -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"Debian clang version 19.1.7 (3+b1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_aabb
	.addrsig_sym cg_saturate
	.addrsig_sym cg_with_w_expr
	.addrsig_sym cg_cross3
	.addrsig_sym cg_cross3_value
	.addrsig_sym __gxx_personality_v0
