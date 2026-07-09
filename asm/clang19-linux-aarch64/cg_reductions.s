# Debian clang version 19.1.7 (3+b1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_reductions.cpp
	.text
	.file	"cg_reductions.cpp"
	.globl	cg_dot3                         // -- Begin function cg_dot3
	.p2align	2
	.type	cg_dot3,@function
cg_dot3:                                // @cg_dot3
	.cfi_startproc
// %bb.0:
	cbz	x3, .LBB0_2
.LBB0_1:                                // =>This Inner Loop Header: Depth=1
	ldr	q0, [x0], #16
	subs	x3, x3, #1
	ldr	q1, [x1], #16
	fmul	v0.4s, v0.4s, v1.4s
	mov	v0.s[3], wzr
	faddp	v0.4s, v0.4s, v0.4s
	faddp	s0, v0.2s
	str	s0, [x2], #4
	b.ne	.LBB0_1
.LBB0_2:
	ret
.Lfunc_end0:
	.size	cg_dot3, .Lfunc_end0-cg_dot3
	.cfi_endproc
                                        // -- End function
	.globl	cg_dot4                         // -- Begin function cg_dot4
	.p2align	2
	.type	cg_dot4,@function
cg_dot4:                                // @cg_dot4
	.cfi_startproc
// %bb.0:
	cbz	x3, .LBB1_2
.LBB1_1:                                // =>This Inner Loop Header: Depth=1
	ldr	q0, [x0], #16
	subs	x3, x3, #1
	ldr	q1, [x1], #16
	fmul	v0.4s, v0.4s, v1.4s
	faddp	v0.4s, v0.4s, v0.4s
	faddp	s0, v0.2s
	str	s0, [x2], #4
	b.ne	.LBB1_1
.LBB1_2:
	ret
.Lfunc_end1:
	.size	cg_dot4, .Lfunc_end1-cg_dot4
	.cfi_endproc
                                        // -- End function
	.globl	cg_magnitude3                   // -- Begin function cg_magnitude3
	.p2align	2
	.type	cg_magnitude3,@function
cg_magnitude3:                          // @cg_magnitude3
	.cfi_startproc
// %bb.0:
	cbz	x2, .LBB2_2
.LBB2_1:                                // =>This Inner Loop Header: Depth=1
	ldr	q0, [x0], #16
	subs	x2, x2, #1
	fmul	v0.4s, v0.4s, v0.4s
	mov	v0.s[3], wzr
	faddp	v0.4s, v0.4s, v0.4s
	faddp	s0, v0.2s
	dup	v0.4s, v0.s[0]
	fsqrt	v0.4s, v0.4s
	st1	{ v0.s }[0], [x1], #4
	b.ne	.LBB2_1
.LBB2_2:
	ret
.Lfunc_end2:
	.size	cg_magnitude3, .Lfunc_end2-cg_magnitude3
	.cfi_endproc
                                        // -- End function
	.globl	cg_magnitude3_sq                // -- Begin function cg_magnitude3_sq
	.p2align	2
	.type	cg_magnitude3_sq,@function
cg_magnitude3_sq:                       // @cg_magnitude3_sq
	.cfi_startproc
// %bb.0:
	cbz	x2, .LBB3_2
.LBB3_1:                                // =>This Inner Loop Header: Depth=1
	ldr	q0, [x0], #16
	subs	x2, x2, #1
	fmul	v0.4s, v0.4s, v0.4s
	mov	v0.s[3], wzr
	faddp	v0.4s, v0.4s, v0.4s
	faddp	s0, v0.2s
	str	s0, [x1], #4
	b.ne	.LBB3_1
.LBB3_2:
	ret
.Lfunc_end3:
	.size	cg_magnitude3_sq, .Lfunc_end3-cg_magnitude3_sq
	.cfi_endproc
                                        // -- End function
	.globl	cg_mag3_lt_mag3                 // -- Begin function cg_mag3_lt_mag3
	.p2align	2
	.type	cg_mag3_lt_mag3,@function
cg_mag3_lt_mag3:                        // @cg_mag3_lt_mag3
	.cfi_startproc
// %bb.0:
	cbz	x3, .LBB4_2
.LBB4_1:                                // =>This Inner Loop Header: Depth=1
	ldr	q0, [x0], #16
	ldr	q1, [x1], #16
	fmul	v0.4s, v0.4s, v0.4s
	fmul	v1.4s, v1.4s, v1.4s
	mov	v0.s[3], wzr
	mov	v1.s[3], wzr
	faddp	v0.4s, v0.4s, v0.4s
	faddp	v1.4s, v1.4s, v1.4s
	faddp	s0, v0.2s
	faddp	s1, v1.2s
	fcmp	s0, s1
	cset	w8, mi
	subs	x3, x3, #1
	strb	w8, [x2], #1
	b.ne	.LBB4_1
.LBB4_2:
	ret
.Lfunc_end4:
	.size	cg_mag3_lt_mag3, .Lfunc_end4-cg_mag3_lt_mag3
	.cfi_endproc
                                        // -- End function
	.globl	cg_mag3_lt_scalar               // -- Begin function cg_mag3_lt_scalar
	.p2align	2
	.type	cg_mag3_lt_scalar,@function
cg_mag3_lt_scalar:                      // @cg_mag3_lt_scalar
	.cfi_startproc
// %bb.0:
	cbz	x2, .LBB5_5
// %bb.1:
	fcmp	s0, #0.0
	b.pl	.LBB5_3
// %bb.2:
	mov	x0, x1
	mov	w1, wzr
	b	memset
.LBB5_3:
	fmul	s0, s0, s0
.LBB5_4:                                // =>This Inner Loop Header: Depth=1
	ldr	q1, [x0], #16
	fmul	v1.4s, v1.4s, v1.4s
	mov	v1.s[3], wzr
	faddp	v1.4s, v1.4s, v1.4s
	faddp	s1, v1.2s
	fcmp	s1, s0
	cset	w8, mi
	subs	x2, x2, #1
	strb	w8, [x1], #1
	b.ne	.LBB5_4
.LBB5_5:
	ret
.Lfunc_end5:
	.size	cg_mag3_lt_scalar, .Lfunc_end5-cg_mag3_lt_scalar
	.cfi_endproc
                                        // -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"Debian clang version 19.1.7 (3+b1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_dot3
	.addrsig_sym cg_dot4
	.addrsig_sym cg_magnitude3
	.addrsig_sym cg_magnitude3_sq
	.addrsig_sym cg_mag3_lt_mag3
	.addrsig_sym cg_mag3_lt_scalar
	.addrsig_sym __gxx_personality_v0
