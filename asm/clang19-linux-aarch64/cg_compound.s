# Debian clang version 19.1.7 (3+b1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_compound.cpp
	.text
	.file	"cg_compound.cpp"
	.globl	cg_compound_et                  // -- Begin function cg_compound_et
	.p2align	2
	.type	cg_compound_et,@function
cg_compound_et:                         // @cg_compound_et
	.cfi_startproc
// %bb.0:
	cbz	x4, .LBB0_3
// %bb.1:
	fmov	v0.4s, #3.00000000
.LBB0_2:                                // =>This Inner Loop Header: Depth=1
	ldr	q1, [x1], #16
	subs	x4, x4, #1
	ldr	q3, [x0], #16
	fadd	v2.4s, v1.4s, v1.4s
	ldr	q4, [x2], #16
	fmul	v1.4s, v1.4s, v4.4s
	fadd	v2.4s, v2.4s, v3.4s
	mov	v1.s[3], wzr
	fmul	v3.4s, v2.4s, v2.4s
	faddp	v1.4s, v1.4s, v1.4s
	mov	v3.s[3], wzr
	faddp	s1, v1.2s
	faddp	v3.4s, v3.4s, v3.4s
	faddp	s3, v3.2s
	dup	v3.4s, v3.s[0]
	fsqrt	v3.4s, v3.4s
	fdiv	v3.4s, v2.4s, v3.4s
	mov	v3.s[3], v2.s[3]
	fmul	v2.4s, v4.4s, v0.4s
	fmul	v1.4s, v3.4s, v1.s[0]
	fadd	v1.4s, v2.4s, v1.4s
	str	q1, [x3], #16
	b.ne	.LBB0_2
.LBB0_3:
	ret
.Lfunc_end0:
	.size	cg_compound_et, .Lfunc_end0-cg_compound_et
	.cfi_endproc
                                        // -- End function
	.globl	cg_compound_manual              // -- Begin function cg_compound_manual
	.p2align	2
	.type	cg_compound_manual,@function
cg_compound_manual:                     // @cg_compound_manual
	.cfi_startproc
// %bb.0:
	cbz	x4, .LBB1_3
// %bb.1:
	fmov	v0.4s, #3.00000000
.LBB1_2:                                // =>This Inner Loop Header: Depth=1
	ldr	q1, [x1], #16
	subs	x4, x4, #1
	ldr	q3, [x0], #16
	fadd	v2.4s, v1.4s, v1.4s
	ldr	q4, [x2], #16
	fmul	v1.4s, v1.4s, v4.4s
	fadd	v2.4s, v3.4s, v2.4s
	mov	v1.s[3], wzr
	fmul	v3.4s, v2.4s, v2.4s
	faddp	v1.4s, v1.4s, v1.4s
	mov	v3.s[3], wzr
	faddp	s1, v1.2s
	faddp	v3.4s, v3.4s, v3.4s
	faddp	s3, v3.2s
	dup	v3.4s, v3.s[0]
	fsqrt	v3.4s, v3.4s
	fdiv	v3.4s, v2.4s, v3.4s
	mov	v3.s[3], v2.s[3]
	fmul	v2.4s, v4.4s, v0.4s
	fmul	v1.4s, v3.4s, v1.s[0]
	fadd	v1.4s, v2.4s, v1.4s
	str	q1, [x3], #16
	b.ne	.LBB1_2
.LBB1_3:
	ret
.Lfunc_end1:
	.size	cg_compound_manual, .Lfunc_end1-cg_compound_manual
	.cfi_endproc
                                        // -- End function
	.globl	cg_compound_intrin              // -- Begin function cg_compound_intrin
	.p2align	2
	.type	cg_compound_intrin,@function
cg_compound_intrin:                     // @cg_compound_intrin
	.cfi_startproc
// %bb.0:
	cbz	x4, .LBB2_3
// %bb.1:
	fmov	v0.4s, #3.00000000
.LBB2_2:                                // =>This Inner Loop Header: Depth=1
	ldr	q1, [x1], #16
	subs	x4, x4, #1
	ldr	q3, [x0], #16
	fadd	v2.4s, v1.4s, v1.4s
	ldr	q4, [x2], #16
	fmul	v1.4s, v1.4s, v4.4s
	fadd	v2.4s, v3.4s, v2.4s
	mov	v1.s[3], wzr
	fmul	v3.4s, v2.4s, v2.4s
	faddp	v1.4s, v1.4s, v1.4s
	mov	v3.s[3], wzr
	faddp	s1, v1.2s
	faddp	v3.4s, v3.4s, v3.4s
	faddp	s3, v3.2s
	dup	v3.4s, v3.s[0]
	fsqrt	v3.4s, v3.4s
	fdiv	v3.4s, v2.4s, v3.4s
	mov	v3.s[3], v2.s[3]
	fmul	v2.4s, v4.4s, v0.4s
	fmul	v1.4s, v3.4s, v1.s[0]
	fadd	v1.4s, v2.4s, v1.4s
	str	q1, [x3], #16
	b.ne	.LBB2_2
.LBB2_3:
	ret
.Lfunc_end2:
	.size	cg_compound_intrin, .Lfunc_end2-cg_compound_intrin
	.cfi_endproc
                                        // -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"Debian clang version 19.1.7 (3+b1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_compound_et
	.addrsig_sym cg_compound_manual
	.addrsig_sym cg_compound_intrin
	.addrsig_sym __gxx_personality_v0
