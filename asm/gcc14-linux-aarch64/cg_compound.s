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
	.global	cg_compound_value
	.type	cg_compound_value, %function
cg_compound_value:
.LFB5349:
	.cfi_startproc
	ldr	q30, [x1]
	sub	sp, sp, #128
	.cfi_def_cfa_offset 128
	ldr	q29, [x0]
	fmov	v28.4s, 2.0e+0
	ldr	q0, [x2]
	add	sp, sp, 128
	.cfi_def_cfa_offset 0
	fmov	v31.4s, 3.0e+0
	fmla	v29.4s, v30.4s, v28.4s
	fmul	v30.4s, v30.4s, v0.4s
	fmul	v0.4s, v0.4s, v31.4s
	fmul	v31.4s, v29.4s, v29.4s
	ins	v30.s[3], wzr
	faddp	v30.4s, v30.4s, v30.4s
	ins	v31.s[3], wzr
	faddp	v31.4s, v31.4s, v31.4s
	faddp	v30.4s, v30.4s, v30.4s
	faddp	v31.4s, v31.4s, v31.4s
	dup	v31.4s, v31.s[0]
	fsqrt	v31.4s, v31.4s
	fdiv	v31.4s, v29.4s, v31.4s
	ins	v31.s[3], v29.s[3]
	fmla	v0.4s, v31.4s, v30.s[0]
	ret
	.cfi_endproc
.LFE5349:
	.size	cg_compound_value, .-cg_compound_value
	.align	2
	.p2align 5,,15
	.global	cg_compound_manual
	.type	cg_compound_manual, %function
cg_compound_manual:
.LFB5350:
	.cfi_startproc
	cbz	x4, .L13
	fmov	v31.4s, 2.0e+0
	mov	x5, 0
	fmov	v30.4s, 3.0e+0
	mov	x6, 0
	.p2align 5,,15
.L15:
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
	bne	.L15
.L13:
	ret
	.cfi_endproc
.LFE5350:
	.size	cg_compound_manual, .-cg_compound_manual
	.align	2
	.p2align 5,,15
	.global	cg_compound_intrin
	.type	cg_compound_intrin, %function
cg_compound_intrin:
.LFB5353:
	.cfi_startproc
	cbz	x4, .L20
	fmov	v31.4s, 2.0e+0
	mov	x5, 0
	fmov	v30.4s, 3.0e+0
	mov	x6, 0
	.p2align 5,,15
.L22:
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
	bne	.L22
.L20:
	ret
	.cfi_endproc
.LFE5353:
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
