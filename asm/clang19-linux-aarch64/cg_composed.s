# Debian clang version 19.1.7 (3+b1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_composed.cpp
	.text
	.file	"cg_composed.cpp"
	.globl	cg_lerp                         // -- Begin function cg_lerp
	.p2align	2
	.type	cg_lerp,@function
cg_lerp:                                // @cg_lerp
	.cfi_startproc
// %bb.0:
                                        // kill: def $s0 killed $s0 def $q0
	cbz	x3, .LBB0_2
.LBB0_1:                                // =>This Inner Loop Header: Depth=1
	ldr	q1, [x1], #16
	subs	x3, x3, #1
	ldr	q2, [x0], #16
	fsub	v1.4s, v1.4s, v2.4s
	fmul	v1.4s, v1.4s, v0.s[0]
	fadd	v1.4s, v2.4s, v1.4s
	str	q1, [x2], #16
	b.ne	.LBB0_1
.LBB0_2:
	ret
.Lfunc_end0:
	.size	cg_lerp, .Lfunc_end0-cg_lerp
	.cfi_endproc
                                        // -- End function
	.globl	cg_clamp                        // -- Begin function cg_clamp
	.p2align	2
	.type	cg_clamp,@function
cg_clamp:                               // @cg_clamp
	.cfi_startproc
// %bb.0:
	cbz	x4, .LBB1_2
.LBB1_1:                                // =>This Inner Loop Header: Depth=1
	ldr	q0, [x0], #16
	subs	x4, x4, #1
	ldr	q1, [x1], #16
	fmax	v0.4s, v0.4s, v1.4s
	ldr	q1, [x2], #16
	fmin	v0.4s, v0.4s, v1.4s
	str	q0, [x3], #16
	b.ne	.LBB1_1
.LBB1_2:
	ret
.Lfunc_end1:
	.size	cg_clamp, .Lfunc_end1-cg_clamp
	.cfi_endproc
                                        // -- End function
	.globl	cg_reflect                      // -- Begin function cg_reflect
	.p2align	2
	.type	cg_reflect,@function
cg_reflect:                             // @cg_reflect
	.cfi_startproc
// %bb.0:
	cbz	x3, .LBB2_2
.LBB2_1:                                // =>This Inner Loop Header: Depth=1
	ldr	q0, [x0], #16
	subs	x3, x3, #1
	ldr	q1, [x1], #16
	fmul	v2.4s, v0.4s, v1.4s
	mov	v2.s[3], wzr
	faddp	v2.4s, v2.4s, v2.4s
	faddp	s2, v2.2s
	fadd	s2, s2, s2
	fmul	v1.4s, v1.4s, v2.s[0]
	fsub	v0.4s, v0.4s, v1.4s
	str	q0, [x2], #16
	b.ne	.LBB2_1
.LBB2_2:
	ret
.Lfunc_end2:
	.size	cg_reflect, .Lfunc_end2-cg_reflect
	.cfi_endproc
                                        // -- End function
	.globl	cg_distance3_sq                 // -- Begin function cg_distance3_sq
	.p2align	2
	.type	cg_distance3_sq,@function
cg_distance3_sq:                        // @cg_distance3_sq
	.cfi_startproc
// %bb.0:
	cbz	x3, .LBB3_2
.LBB3_1:                                // =>This Inner Loop Header: Depth=1
	ldr	q0, [x0], #16
	subs	x3, x3, #1
	ldr	q1, [x1], #16
	fsub	v0.4s, v0.4s, v1.4s
	fmul	v0.4s, v0.4s, v0.4s
	mov	v0.s[3], wzr
	faddp	v0.4s, v0.4s, v0.4s
	faddp	s0, v0.2s
	str	s0, [x2], #4
	b.ne	.LBB3_1
.LBB3_2:
	ret
.Lfunc_end3:
	.size	cg_distance3_sq, .Lfunc_end3-cg_distance3_sq
	.cfi_endproc
                                        // -- End function
	.globl	cg_orthogonal                   // -- Begin function cg_orthogonal
	.p2align	2
	.type	cg_orthogonal,@function
cg_orthogonal:                          // @cg_orthogonal
	.cfi_startproc
// %bb.0:
	cbnz	x2, .LBB4_2
	b	.LBB4_4
.LBB4_1:                                //   in Loop: Header=BB4_2 Depth=1
	mov	s1, v0.s[1]
	fneg	s2, s1
	movi	v1.2d, #0000000000000000
	mov	v1.s[0], v2.s[0]
	mov	v1.s[1], v0.s[0]
	subs	x2, x2, #1
	add	x0, x0, #16
	str	q1, [x1], #16
	b.eq	.LBB4_4
.LBB4_2:                                // =>This Inner Loop Header: Depth=1
	ldr	q0, [x0]
	mov	s1, v0.s[2]
	fabs	s2, s0
	fabs	s3, s1
	fcmp	s2, s3
	b.gt	.LBB4_1
// %bb.3:                               //   in Loop: Header=BB4_2 Depth=1
	fneg	s2, s1
	movi	v1.2d, #0000000000000000
	mov	v1.s[1], v2.s[0]
	mov	v1.s[2], v0.s[1]
	subs	x2, x2, #1
	add	x0, x0, #16
	str	q1, [x1], #16
	b.ne	.LBB4_2
.LBB4_4:
	ret
.Lfunc_end4:
	.size	cg_orthogonal, .Lfunc_end4-cg_orthogonal
	.cfi_endproc
                                        // -- End function
	.globl	cg_nlerp                        // -- Begin function cg_nlerp
	.p2align	2
	.type	cg_nlerp,@function
cg_nlerp:                               // @cg_nlerp
	.cfi_startproc
// %bb.0:
	cbz	x3, .LBB5_5
// %bb.1:
	fmov	s1, #1.00000000
	fneg	s2, s0
	fsub	s1, s1, s0
	b	.LBB5_3
.LBB5_2:                                //   in Loop: Header=BB5_3 Depth=1
	fmul	v4.4s, v4.4s, v1.s[0]
	fmul	v3.4s, v3.4s, v5.s[0]
	subs	x3, x3, #1
	add	x1, x1, #16
	add	x0, x0, #16
	fadd	v3.4s, v4.4s, v3.4s
	fmul	v4.4s, v3.4s, v3.4s
	faddp	v4.4s, v4.4s, v4.4s
	faddp	s4, v4.2s
	dup	v4.4s, v4.s[0]
	fsqrt	v4.4s, v4.4s
	fdiv	v3.4s, v3.4s, v4.4s
	str	q3, [x2], #16
	b.eq	.LBB5_5
.LBB5_3:                                // =>This Inner Loop Header: Depth=1
	ldr	q4, [x0]
	ldr	q3, [x1]
	fmul	v5.4s, v4.4s, v3.4s
	faddp	v5.4s, v5.4s, v5.4s
	faddp	s5, v5.2s
	fcmp	s5, #0.0
	fmov	s5, s0
	b.pl	.LBB5_2
// %bb.4:                               //   in Loop: Header=BB5_3 Depth=1
	fmov	s5, s2
	b	.LBB5_2
.LBB5_5:
	ret
.Lfunc_end5:
	.size	cg_nlerp, .Lfunc_end5-cg_nlerp
	.cfi_endproc
                                        // -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"Debian clang version 19.1.7 (3+b1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_lerp
	.addrsig_sym cg_clamp
	.addrsig_sym cg_reflect
	.addrsig_sym cg_distance3_sq
	.addrsig_sym cg_orthogonal
	.addrsig_sym cg_nlerp
	.addrsig_sym __gxx_personality_v0
