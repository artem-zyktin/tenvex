# g++ (Debian 14.2.0-19) 14.2.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_compound.cpp
	.arch armv8-a
	.file	"cg_compound.cpp"
	.text
	.align	2
	.p2align 5,,15
	.global	cg_compound_et
	.type	cg_compound_et, %function
cg_compound_et:
.LFB5348:
	.cfi_startproc
	cbz	x4, .L7
	sub	sp, sp, #128
	.cfi_def_cfa_offset 128
	mov	x5, 0
	fmov	v31.4s, 2.0e+0
	add	x8, sp, 96
	fmov	v30.4s, 3.0e+0
	add	x9, sp, 32
	mov	x7, sp
	mov	x6, 0
	.p2align 5,,15
.L2:
	ldr	q29, [x1, x5]
	str	q30, [sp, 80]
	adrp	x10, .LC0
	ldr	q28, [x0, x5]
	str	q29, [x8]
	add	x6, x6, 1
	ldr	q27, [x2, x5]
	fmla	v28.4s, v29.4s, v31.4s
	ldr	q25, [x10, #:lo12:.LC0]
	stp	q29, q27, [x9]
	fmul	v26.4s, v28.4s, v28.4s
	fmul	v29.4s, v29.4s, v27.4s
	stp	q27, q25, [x7]
	movi	v24.4s, 0x40, lsl 24
	str	q27, [sp, 64]
	ins	v26.s[3], wzr
	faddp	v26.4s, v26.4s, v26.4s
	ins	v29.s[3], wzr
	faddp	v29.4s, v29.4s, v29.4s
	fmul	v27.4s, v27.4s, v30.4s
	str	q24, [x8, 16]
	faddp	v26.4s, v26.4s, v26.4s
	faddp	v29.4s, v29.4s, v29.4s
	dup	v26.4s, v26.s[0]
	fsqrt	v26.4s, v26.4s
	fdiv	v26.4s, v28.4s, v26.4s
	ins	v26.s[3], v28.s[3]
	fmla	v27.4s, v26.4s, v29.s[0]
	str	q27, [x3, x5]
	add	x5, x5, 16
	cmp	x4, x6
	bne	.L2
	add	sp, sp, 128
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L7:
	ret
	.cfi_endproc
.LFE5348:
	.size	cg_compound_et, .-cg_compound_et
	.align	2
	.p2align 5,,15
	.global	cg_compound_manual
	.type	cg_compound_manual, %function
cg_compound_manual:
.LFB5349:
	.cfi_startproc
	cbz	x4, .L11
	fmov	v31.4s, 2.0e+0
	mov	x5, 0
	fmov	v30.4s, 3.0e+0
	mov	x6, 0
	.p2align 5,,15
.L13:
	ldr	q29, [x1, x5]
	add	x6, x6, 1
	ldr	q27, [x0, x5]
	ldr	q28, [x2, x5]
	fmla	v27.4s, v29.4s, v31.4s
	fmul	v29.4s, v28.4s, v29.4s
	fmul	v28.4s, v28.4s, v30.4s
	fmul	v26.4s, v27.4s, v27.4s
	ins	v29.s[3], wzr
	faddp	v29.4s, v29.4s, v29.4s
	ins	v26.s[3], wzr
	faddp	v26.4s, v26.4s, v26.4s
	faddp	v29.4s, v29.4s, v29.4s
	faddp	v26.4s, v26.4s, v26.4s
	dup	v26.4s, v26.s[0]
	fsqrt	v26.4s, v26.4s
	fdiv	v26.4s, v27.4s, v26.4s
	ins	v26.s[3], v27.s[3]
	fmla	v28.4s, v26.4s, v29.s[0]
	str	q28, [x3, x5]
	add	x5, x5, 16
	cmp	x4, x6
	bne	.L13
.L11:
	ret
	.cfi_endproc
.LFE5349:
	.size	cg_compound_manual, .-cg_compound_manual
	.align	2
	.p2align 5,,15
	.global	cg_compound_intrin
	.type	cg_compound_intrin, %function
cg_compound_intrin:
.LFB5352:
	.cfi_startproc
	cbz	x4, .L18
	fmov	v31.4s, 2.0e+0
	mov	x5, 0
	fmov	v30.4s, 3.0e+0
	mov	x6, 0
	.p2align 5,,15
.L20:
	ldr	q29, [x1, x5]
	add	x6, x6, 1
	ldr	q27, [x0, x5]
	ldr	q28, [x2, x5]
	fmla	v27.4s, v29.4s, v31.4s
	fmul	v29.4s, v28.4s, v29.4s
	fmul	v28.4s, v28.4s, v30.4s
	fmul	v26.4s, v27.4s, v27.4s
	ins	v29.s[3], wzr
	faddp	v29.4s, v29.4s, v29.4s
	ins	v26.s[3], wzr
	faddp	v26.4s, v26.4s, v26.4s
	faddp	v29.4s, v29.4s, v29.4s
	faddp	v26.4s, v26.4s, v26.4s
	dup	v26.4s, v26.s[0]
	fsqrt	v26.4s, v26.4s
	fdiv	v26.4s, v27.4s, v26.4s
	ins	v26.s[3], v27.s[3]
	fmla	v28.4s, v26.4s, v29.s[0]
	str	q28, [x3, x5]
	add	x5, x5, 16
	cmp	x4, x6
	bne	.L20
.L18:
	ret
	.cfi_endproc
.LFE5352:
	.size	cg_compound_intrin, .-cg_compound_intrin
	.section	.rodata.cst16,"aM",@progbits,16
	.align	4
.LC0:
	.word	1077936128
	.word	1077936128
	.word	1077936128
	.word	1077936128
	.ident	"GCC: (Debian 14.2.0-19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
