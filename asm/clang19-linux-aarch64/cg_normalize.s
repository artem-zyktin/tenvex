# Debian clang version 19.1.7 (3+b1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_normalize.cpp
	.text
	.file	"cg_normalize.cpp"
	.globl	cg_normalize3                   // -- Begin function cg_normalize3
	.p2align	2
	.type	cg_normalize3,@function
cg_normalize3:                          // @cg_normalize3
	.cfi_startproc
// %bb.0:
	cbz	x2, .LBB0_2
.LBB0_1:                                // =>This Inner Loop Header: Depth=1
	ldr	q0, [x0], #16
	subs	x2, x2, #1
	fmul	v1.4s, v0.4s, v0.4s
	mov	v1.s[3], wzr
	faddp	v1.4s, v1.4s, v1.4s
	faddp	s1, v1.2s
	dup	v1.4s, v1.s[0]
	fsqrt	v1.4s, v1.4s
	fdiv	v1.4s, v0.4s, v1.4s
	mov	v1.s[3], v0.s[3]
	str	q1, [x1], #16
	b.ne	.LBB0_1
.LBB0_2:
	ret
.Lfunc_end0:
	.size	cg_normalize3, .Lfunc_end0-cg_normalize3
	.cfi_endproc
                                        // -- End function
	.globl	cg_normalize3_fast              // -- Begin function cg_normalize3_fast
	.p2align	2
	.type	cg_normalize3_fast,@function
cg_normalize3_fast:                     // @cg_normalize3_fast
	.cfi_startproc
// %bb.0:
	cbz	x2, .LBB1_2
.LBB1_1:                                // =>This Inner Loop Header: Depth=1
	ldr	q0, [x0], #16
	subs	x2, x2, #1
	fmul	v1.4s, v0.4s, v0.4s
	mov	v1.s[3], wzr
	faddp	v1.4s, v1.4s, v1.4s
	faddp	s1, v1.2s
	dup	v2.4s, v1.s[0]
	frsqrte	v2.4s, v2.4s
	fmul	v1.4s, v2.4s, v1.s[0]
	frsqrts	v1.4s, v1.4s, v2.4s
	fmul	v1.4s, v2.4s, v1.4s
	fmul	v1.4s, v0.4s, v1.4s
	mov	v1.s[3], v0.s[3]
	str	q1, [x1], #16
	b.ne	.LBB1_1
.LBB1_2:
	ret
.Lfunc_end1:
	.size	cg_normalize3_fast, .Lfunc_end1-cg_normalize3_fast
	.cfi_endproc
                                        // -- End function
	.globl	cg_normalize4                   // -- Begin function cg_normalize4
	.p2align	2
	.type	cg_normalize4,@function
cg_normalize4:                          // @cg_normalize4
	.cfi_startproc
// %bb.0:
	cbz	x2, .LBB2_2
.LBB2_1:                                // =>This Inner Loop Header: Depth=1
	ldr	q0, [x0], #16
	subs	x2, x2, #1
	fmul	v1.4s, v0.4s, v0.4s
	faddp	v1.4s, v1.4s, v1.4s
	faddp	s1, v1.2s
	dup	v1.4s, v1.s[0]
	fsqrt	v1.4s, v1.4s
	fdiv	v0.4s, v0.4s, v1.4s
	str	q0, [x1], #16
	b.ne	.LBB2_1
.LBB2_2:
	ret
.Lfunc_end2:
	.size	cg_normalize4, .Lfunc_end2-cg_normalize4
	.cfi_endproc
                                        // -- End function
	.globl	cg_normalize3_value             // -- Begin function cg_normalize3_value
	.p2align	2
	.type	cg_normalize3_value,@function
cg_normalize3_value:                    // @cg_normalize3_value
	.cfi_startproc
// %bb.0:
	ldr	q1, [x0]
	fmul	v0.4s, v1.4s, v1.4s
	mov	v0.s[3], wzr
	faddp	v0.4s, v0.4s, v0.4s
	faddp	s0, v0.2s
	dup	v0.4s, v0.s[0]
	fsqrt	v0.4s, v0.4s
	fdiv	v0.4s, v1.4s, v0.4s
	mov	v0.s[3], v1.s[3]
	ret
.Lfunc_end3:
	.size	cg_normalize3_value, .Lfunc_end3-cg_normalize3_value
	.cfi_endproc
                                        // -- End function
	.globl	cg_normalize3_fast_value        // -- Begin function cg_normalize3_fast_value
	.p2align	2
	.type	cg_normalize3_fast_value,@function
cg_normalize3_fast_value:               // @cg_normalize3_fast_value
	.cfi_startproc
// %bb.0:
	ldr	q1, [x0]
	fmul	v0.4s, v1.4s, v1.4s
	mov	v0.s[3], wzr
	faddp	v0.4s, v0.4s, v0.4s
	faddp	s0, v0.2s
	dup	v2.4s, v0.s[0]
	frsqrte	v2.4s, v2.4s
	fmul	v0.4s, v2.4s, v0.s[0]
	frsqrts	v0.4s, v0.4s, v2.4s
	fmul	v0.4s, v2.4s, v0.4s
	fmul	v0.4s, v1.4s, v0.4s
	mov	v0.s[3], v1.s[3]
	ret
.Lfunc_end4:
	.size	cg_normalize3_fast_value, .Lfunc_end4-cg_normalize3_fast_value
	.cfi_endproc
                                        // -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"Debian clang version 19.1.7 (3+b1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_normalize3
	.addrsig_sym cg_normalize3_fast
	.addrsig_sym cg_normalize4
	.addrsig_sym cg_normalize3_value
	.addrsig_sym cg_normalize3_fast_value
	.addrsig_sym __gxx_personality_v0
