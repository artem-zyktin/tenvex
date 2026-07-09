# Debian clang version 19.1.7 (3+b1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_quat.cpp
	.text
	.file	"cg_quat.cpp"
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          // -- Begin function cg_hamilton
.LCPI0_0:
	.word	0                               // 0x0
	.word	0                               // 0x0
	.word	2147483648                      // 0x80000000
	.word	2147483648                      // 0x80000000
.LCPI0_1:
	.word	2147483648                      // 0x80000000
	.word	0                               // 0x0
	.word	0                               // 0x0
	.word	2147483648                      // 0x80000000
	.text
	.globl	cg_hamilton
	.p2align	2
	.type	cg_hamilton,@function
cg_hamilton:                            // @cg_hamilton
	.cfi_startproc
// %bb.0:
	cbz	x3, .LBB0_3
// %bb.1:
	movi	v0.2d, #0000000000000000
	adrp	x8, .LCPI0_0
	adrp	x9, .LCPI0_1
	ldr	q1, [x8, :lo12:.LCPI0_0]
	ldr	q2, [x9, :lo12:.LCPI0_1]
	fneg	v0.2d, v0.2d
.LBB0_2:                                // =>This Inner Loop Header: Depth=1
	ldr	q3, [x1], #16
	subs	x3, x3, #1
	ldr	q7, [x0], #16
	ext	v4.16b, v3.16b, v3.16b, #8
	rev64	v5.4s, v3.4s
	fmul	v3.4s, v3.4s, v7.s[3]
	rev64	v6.4s, v4.4s
	fmul	v4.4s, v4.4s, v7.s[1]
	fmul	v5.4s, v5.4s, v7.s[2]
	fmul	v6.4s, v6.4s, v7.s[0]
	eor	v4.16b, v4.16b, v1.16b
	eor	v5.16b, v5.16b, v2.16b
	fadd	v4.4s, v4.4s, v5.4s
	eor	v6.16b, v6.16b, v0.16b
	fadd	v3.4s, v3.4s, v6.4s
	fadd	v3.4s, v4.4s, v3.4s
	str	q3, [x2], #16
	b.ne	.LBB0_2
.LBB0_3:
	ret
.Lfunc_end0:
	.size	cg_hamilton, .Lfunc_end0-cg_hamilton
	.cfi_endproc
                                        // -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          // -- Begin function cg_rotate
.LCPI1_0:
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
.LCPI1_1:
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
	.globl	cg_rotate
	.p2align	2
	.type	cg_rotate,@function
cg_rotate:                              // @cg_rotate
	.cfi_startproc
// %bb.0:
	cbz	x3, .LBB1_3
// %bb.1:
	adrp	x8, .LCPI1_0
	adrp	x9, .LCPI1_1
	ldr	q0, [x8, :lo12:.LCPI1_0]
	ldr	q1, [x9, :lo12:.LCPI1_1]
.LBB1_2:                                // =>This Inner Loop Header: Depth=1
	ldr	q2, [x1], #16
	subs	x3, x3, #1
	ldr	q3, [x0], #16
	tbl	v4.16b, { v2.16b }, v0.16b
	tbl	v6.16b, { v2.16b }, v1.16b
	fadd	v2.4s, v2.4s, v2.4s
	tbl	v5.16b, { v3.16b }, v1.16b
	tbl	v7.16b, { v3.16b }, v0.16b
	fmul	v5.4s, v4.4s, v5.4s
	fmul	v7.4s, v6.4s, v7.4s
	fsub	v5.4s, v5.4s, v7.4s
	tbl	v7.16b, { v5.16b }, v1.16b
	tbl	v16.16b, { v5.16b }, v0.16b
	fmul	v2.4s, v5.4s, v2.s[3]
	fmul	v4.4s, v4.4s, v7.4s
	fmul	v6.4s, v6.4s, v16.4s
	fsub	v4.4s, v4.4s, v6.4s
	fadd	v4.4s, v4.4s, v4.4s
	fadd	v2.4s, v2.4s, v4.4s
	fadd	v2.4s, v3.4s, v2.4s
	str	q2, [x2], #16
	b.ne	.LBB1_2
.LBB1_3:
	ret
.Lfunc_end1:
	.size	cg_rotate, .Lfunc_end1-cg_rotate
	.cfi_endproc
                                        // -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          // -- Begin function cg_conj_scale
.LCPI2_0:
	.word	2147483648                      // 0x80000000
	.word	2147483648                      // 0x80000000
	.word	2147483648                      // 0x80000000
	.word	0                               // 0x0
	.text
	.globl	cg_conj_scale
	.p2align	2
	.type	cg_conj_scale,@function
cg_conj_scale:                          // @cg_conj_scale
	.cfi_startproc
// %bb.0:
	cbz	x2, .LBB2_3
// %bb.1:
	adrp	x8, .LCPI2_0
	ldr	q0, [x8, :lo12:.LCPI2_0]
.LBB2_2:                                // =>This Inner Loop Header: Depth=1
	ldr	q1, [x0], #16
	subs	x2, x2, #1
	eor	v1.16b, v1.16b, v0.16b
	fadd	v1.4s, v1.4s, v1.4s
	str	q1, [x1], #16
	b.ne	.LBB2_2
.LBB2_3:
	ret
.Lfunc_end2:
	.size	cg_conj_scale, .Lfunc_end2-cg_conj_scale
	.cfi_endproc
                                        // -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          // -- Begin function cg_quat_inverse
.LCPI3_0:
	.word	2147483648                      // 0x80000000
	.word	2147483648                      // 0x80000000
	.word	2147483648                      // 0x80000000
	.word	0                               // 0x0
	.text
	.globl	cg_quat_inverse
	.p2align	2
	.type	cg_quat_inverse,@function
cg_quat_inverse:                        // @cg_quat_inverse
	.cfi_startproc
// %bb.0:
	cbz	x2, .LBB3_3
// %bb.1:
	adrp	x8, .LCPI3_0
	ldr	q0, [x8, :lo12:.LCPI3_0]
.LBB3_2:                                // =>This Inner Loop Header: Depth=1
	ldr	q1, [x0], #16
	subs	x2, x2, #1
	fmul	v2.4s, v1.4s, v1.4s
	eor	v1.16b, v1.16b, v0.16b
	faddp	v2.4s, v2.4s, v2.4s
	faddp	s2, v2.2s
	dup	v2.4s, v2.s[0]
	fdiv	v1.4s, v1.4s, v2.4s
	str	q1, [x1], #16
	b.ne	.LBB3_2
.LBB3_3:
	ret
.Lfunc_end3:
	.size	cg_quat_inverse, .Lfunc_end3-cg_quat_inverse
	.cfi_endproc
                                        // -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          // -- Begin function cg_rotate_fused
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
	.globl	cg_rotate_fused
	.p2align	2
	.type	cg_rotate_fused,@function
cg_rotate_fused:                        // @cg_rotate_fused
	.cfi_startproc
// %bb.0:
	cbz	x4, .LBB4_3
// %bb.1:
	adrp	x8, .LCPI4_0
	adrp	x9, .LCPI4_1
	ldr	q0, [x8, :lo12:.LCPI4_0]
	ldr	q1, [x9, :lo12:.LCPI4_1]
.LBB4_2:                                // =>This Inner Loop Header: Depth=1
	ldr	q2, [x2], #16
	subs	x4, x4, #1
	ldr	q3, [x0], #16
	tbl	v4.16b, { v2.16b }, v0.16b
	tbl	v6.16b, { v2.16b }, v1.16b
	fadd	v2.4s, v2.4s, v2.4s
	tbl	v5.16b, { v3.16b }, v1.16b
	tbl	v7.16b, { v3.16b }, v0.16b
	fmul	v5.4s, v4.4s, v5.4s
	fmul	v7.4s, v6.4s, v7.4s
	fsub	v5.4s, v5.4s, v7.4s
	tbl	v7.16b, { v5.16b }, v1.16b
	tbl	v16.16b, { v5.16b }, v0.16b
	fmul	v2.4s, v5.4s, v2.s[3]
	fmul	v4.4s, v4.4s, v7.4s
	fmul	v6.4s, v6.4s, v16.4s
	fsub	v4.4s, v4.4s, v6.4s
	fadd	v4.4s, v4.4s, v4.4s
	fadd	v2.4s, v2.4s, v4.4s
	ldr	q4, [x1], #16
	fadd	v2.4s, v3.4s, v2.4s
	fadd	v3.4s, v4.4s, v4.4s
	fadd	v2.4s, v3.4s, v2.4s
	str	q2, [x3], #16
	b.ne	.LBB4_2
.LBB4_3:
	ret
.Lfunc_end4:
	.size	cg_rotate_fused, .Lfunc_end4-cg_rotate_fused
	.cfi_endproc
                                        // -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          // -- Begin function cg_hamilton_value
.LCPI5_0:
	.word	0                               // 0x0
	.word	0                               // 0x0
	.word	2147483648                      // 0x80000000
	.word	2147483648                      // 0x80000000
.LCPI5_1:
	.word	2147483648                      // 0x80000000
	.word	0                               // 0x0
	.word	0                               // 0x0
	.word	2147483648                      // 0x80000000
	.text
	.globl	cg_hamilton_value
	.p2align	2
	.type	cg_hamilton_value,@function
cg_hamilton_value:                      // @cg_hamilton_value
	.cfi_startproc
// %bb.0:
	ldr	q1, [x1]
	movi	v0.2d, #0000000000000000
	ldr	q5, [x0]
	adrp	x8, .LCPI5_0
	adrp	x9, .LCPI5_1
	ext	v2.16b, v1.16b, v1.16b, #8
	rev64	v4.4s, v1.4s
	ldr	q6, [x8, :lo12:.LCPI5_0]
	ldr	q7, [x9, :lo12:.LCPI5_1]
	fmul	v1.4s, v1.4s, v5.s[3]
	fneg	v0.2d, v0.2d
	rev64	v3.4s, v2.4s
	fmul	v2.4s, v2.4s, v5.s[1]
	fmul	v4.4s, v4.4s, v5.s[2]
	fmul	v3.4s, v3.4s, v5.s[0]
	eor	v2.16b, v2.16b, v6.16b
	eor	v0.16b, v3.16b, v0.16b
	eor	v3.16b, v4.16b, v7.16b
	fadd	v0.4s, v1.4s, v0.4s
	fadd	v1.4s, v2.4s, v3.4s
	fadd	v0.4s, v1.4s, v0.4s
	ret
.Lfunc_end5:
	.size	cg_hamilton_value, .Lfunc_end5-cg_hamilton_value
	.cfi_endproc
                                        // -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          // -- Begin function cg_rotate_value
.LCPI6_0:
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
.LCPI6_1:
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
	.globl	cg_rotate_value
	.p2align	2
	.type	cg_rotate_value,@function
cg_rotate_value:                        // @cg_rotate_value
	.cfi_startproc
// %bb.0:
	adrp	x8, .LCPI6_0
	ldr	q0, [x1]
	ldr	q2, [x0]
	ldr	q1, [x8, :lo12:.LCPI6_0]
	adrp	x8, .LCPI6_1
	ldr	q3, [x8, :lo12:.LCPI6_1]
	tbl	v4.16b, { v0.16b }, v1.16b
	tbl	v7.16b, { v2.16b }, v1.16b
	tbl	v5.16b, { v2.16b }, v3.16b
	tbl	v6.16b, { v0.16b }, v3.16b
	fadd	v0.4s, v0.4s, v0.4s
	fmul	v5.4s, v4.4s, v5.4s
	fmul	v7.4s, v6.4s, v7.4s
	fsub	v5.4s, v5.4s, v7.4s
	tbl	v3.16b, { v5.16b }, v3.16b
	tbl	v1.16b, { v5.16b }, v1.16b
	fmul	v0.4s, v5.4s, v0.s[3]
	fmul	v3.4s, v4.4s, v3.4s
	fmul	v1.4s, v6.4s, v1.4s
	fsub	v1.4s, v3.4s, v1.4s
	fadd	v1.4s, v1.4s, v1.4s
	fadd	v0.4s, v0.4s, v1.4s
	fadd	v0.4s, v2.4s, v0.4s
	ret
.Lfunc_end6:
	.size	cg_rotate_value, .Lfunc_end6-cg_rotate_value
	.cfi_endproc
                                        // -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"Debian clang version 19.1.7 (3+b1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_hamilton
	.addrsig_sym cg_rotate
	.addrsig_sym cg_conj_scale
	.addrsig_sym cg_quat_inverse
	.addrsig_sym cg_rotate_fused
	.addrsig_sym cg_hamilton_value
	.addrsig_sym cg_rotate_value
	.addrsig_sym __gxx_personality_v0
