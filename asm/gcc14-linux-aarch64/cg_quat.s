# g++ (Debian 14.2.0-19) 14.2.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_quat.cpp
	.arch armv8-a
	.file	"cg_quat.cpp"
	.text
	.align	2
	.p2align 5,,15
	.global	cg_hamilton
	.type	cg_hamilton, %function
cg_hamilton:
.LFB5348:
	.cfi_startproc
	cbz	x3, .L9
	adrp	x6, .LC1
	adrp	x5, .LC0
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	lsl	x3, x3, 4
	ldr	q28, [x6, #:lo12:.LC1]
	adrp	x6, .LC2
	ldr	q29, [x5, #:lo12:.LC0]
	add	x5, sp, 32
	ldr	q27, [x6, #:lo12:.LC2]
	adrp	x6, .LC3
	mov	x4, 0
	ldr	q26, [x6, #:lo12:.LC3]
	.p2align 5,,15
.L3:
	ldr	q2, [x1, x4]
	ldr	q4, [x0, x4]
	mov	v30.16b, v2.16b
	mov	v31.16b, v2.16b
	ext	v0.16b, v2.16b, v2.16b, #8
	stp	q4, q2, [sp]
	rev64	v24.4s, v2.4s
	stp	q4, q2, [x5]
	tbl	v30.16b, {v30.16b - v31.16b}, v29.16b
	fmul	v0.4s, v0.4s, v4.s[1]
	fmul	v24.4s, v24.4s, v4.s[2]
	fmul	v30.4s, v30.4s, v4.s[0]
	eor	v0.16b, v0.16b, v27.16b
	eor	v24.16b, v24.16b, v26.16b
	eor	v30.16b, v30.16b, v28.16b
	fadd	v24.4s, v0.4s, v24.4s
	fmla	v30.4s, v2.4s, v4.s[3]
	fadd	v24.4s, v24.4s, v30.4s
	str	q24, [x2, x4]
	add	x4, x4, 16
	cmp	x3, x4
	bne	.L3
	add	sp, sp, 64
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L9:
	ret
	.cfi_endproc
.LFE5348:
	.size	cg_hamilton, .-cg_hamilton
	.align	2
	.p2align 5,,15
	.global	cg_rotate
	.type	cg_rotate, %function
cg_rotate:
.LFB5349:
	.cfi_startproc
	cbz	x3, .L21
	adrp	x6, .LC5
	adrp	x5, .LC4
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	lsl	x3, x3, 4
	ldr	q30, [x6, #:lo12:.LC5]
	mov	x4, 0
	ldr	q31, [x5, #:lo12:.LC4]
	add	x5, sp, 32
	.p2align 5,,15
.L15:
	ldr	q4, [x0, x4]
	ldr	q2, [x1, x4]
	tbl	v29.16b, {v4.16b}, v30.16b
	tbl	v0.16b, {v4.16b}, v31.16b
	tbl	v23.16b, {v2.16b}, v31.16b
	stp	q4, q2, [sp]
	tbl	v28.16b, {v2.16b}, v30.16b
	stp	q4, q2, [x5]
	fmul	v29.4s, v23.4s, v29.4s
	dup	v24.4s, v2.s[3]
	fmls	v29.4s, v28.4s, v0.4s
	fadd	v24.4s, v24.4s, v24.4s
	tbl	v26.16b, {v29.16b}, v30.16b
	tbl	v27.16b, {v29.16b}, v31.16b
	fmul	v26.4s, v23.4s, v26.4s
	fmls	v26.4s, v28.4s, v27.4s
	fadd	v26.4s, v26.4s, v26.4s
	fmla	v26.4s, v29.4s, v24.4s
	fadd	v26.4s, v4.4s, v26.4s
	str	q26, [x2, x4]
	add	x4, x4, 16
	cmp	x3, x4
	bne	.L15
	add	sp, sp, 64
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L21:
	ret
	.cfi_endproc
.LFE5349:
	.size	cg_rotate, .-cg_rotate
	.align	2
	.p2align 5,,15
	.global	cg_conj_scale
	.type	cg_conj_scale, %function
cg_conj_scale:
.LFB5350:
	.cfi_startproc
	cbz	x2, .L24
	adrp	x4, .LC6
	lsl	x2, x2, 4
	mov	x3, 0
	ldr	q31, [x4, #:lo12:.LC6]
	.p2align 5,,15
.L26:
	ldr	q30, [x0, x3]
	eor	v30.16b, v30.16b, v31.16b
	fadd	v30.4s, v30.4s, v30.4s
	str	q30, [x1, x3]
	add	x3, x3, 16
	cmp	x2, x3
	bne	.L26
.L24:
	ret
	.cfi_endproc
.LFE5350:
	.size	cg_conj_scale, .-cg_conj_scale
	.align	2
	.p2align 5,,15
	.global	cg_quat_inverse
	.type	cg_quat_inverse, %function
cg_quat_inverse:
.LFB5351:
	.cfi_startproc
	cbz	x2, .L31
	adrp	x4, .LC6
	lsl	x2, x2, 4
	mov	x3, 0
	ldr	q31, [x4, #:lo12:.LC6]
	.p2align 5,,15
.L33:
	ldr	q30, [x0, x3]
	fmul	v29.4s, v30.4s, v30.4s
	eor	v30.16b, v30.16b, v31.16b
	faddp	v29.4s, v29.4s, v29.4s
	faddp	v29.4s, v29.4s, v29.4s
	dup	v29.4s, v29.s[0]
	fdiv	v29.4s, v30.4s, v29.4s
	str	q29, [x1, x3]
	add	x3, x3, 16
	cmp	x2, x3
	bne	.L33
.L31:
	ret
	.cfi_endproc
.LFE5351:
	.size	cg_quat_inverse, .-cg_quat_inverse
	.section	.rodata.cst16,"aM",@progbits,16
	.align	4
.LC0:
	.byte	12
	.byte	13
	.byte	14
	.byte	15
	.byte	8
	.byte	9
	.byte	10
	.byte	11
	.byte	4
	.byte	5
	.byte	6
	.byte	7
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.align	4
.LC1:
	.word	0
	.word	-2147483648
	.word	0
	.word	-2147483648
	.align	4
.LC2:
	.word	0
	.word	0
	.word	-2147483648
	.word	-2147483648
	.align	4
.LC3:
	.word	-2147483648
	.word	0
	.word	0
	.word	-2147483648
	.align	4
.LC4:
	.byte	4
	.byte	5
	.byte	6
	.byte	7
	.byte	8
	.byte	9
	.byte	10
	.byte	11
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	12
	.byte	13
	.byte	14
	.byte	15
	.align	4
.LC5:
	.byte	8
	.byte	9
	.byte	10
	.byte	11
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	4
	.byte	5
	.byte	6
	.byte	7
	.byte	12
	.byte	13
	.byte	14
	.byte	15
	.align	4
.LC6:
	.word	-2147483648
	.word	-2147483648
	.word	-2147483648
	.word	0
	.ident	"GCC: (Debian 14.2.0-19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
