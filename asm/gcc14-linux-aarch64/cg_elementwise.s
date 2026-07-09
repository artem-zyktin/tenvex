# g++ (Debian 14.2.0-19) 14.2.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_elementwise.cpp
	.arch armv8-a
	.file	"cg_elementwise.cpp"
	.text
	.align	2
	.p2align 5,,15
	.global	cg_aabb
	.type	cg_aabb, %function
cg_aabb:
.LFB5348:
	.cfi_startproc
	ldr	q31, [x0]
	sub	sp, sp, #96
	.cfi_def_cfa_offset 96
	mov	v30.16b, v31.16b
	cmp	x1, 1
	bls	.L2
	add	x1, x0, x1, lsl 4
	add	x0, x0, 16
	.p2align 5,,15
.L3:
	ldr	q29, [x0], 16
	fmin	v31.4s, v31.4s, v29.4s
	fmax	v30.4s, v30.4s, v29.4s
	cmp	x1, x0
	bne	.L3
.L2:
	str	q31, [x2]
	str	q30, [x3]
	add	sp, sp, 96
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE5348:
	.size	cg_aabb, .-cg_aabb
	.align	2
	.p2align 5,,15
	.global	cg_saturate
	.type	cg_saturate, %function
cg_saturate:
.LFB5349:
	.cfi_startproc
	cbz	x2, .L16
	movi	v31.4s, 0
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	fmov	v30.4s, 1.0e+0
	lsl	x2, x2, 4
	mov	x3, 0
	.p2align 5,,15
.L10:
	ldr	q29, [x0, x3]
	str	q29, [sp]
	fmax	v29.4s, v29.4s, v31.4s
	fmin	v29.4s, v29.4s, v30.4s
	str	q29, [x1, x3]
	add	x3, x3, 16
	cmp	x2, x3
	bne	.L10
	add	sp, sp, 32
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L16:
	ret
	.cfi_endproc
.LFE5349:
	.size	cg_saturate, .-cg_saturate
	.align	2
	.p2align 5,,15
	.global	cg_with_w_expr
	.type	cg_with_w_expr, %function
cg_with_w_expr:
.LFB5350:
	.cfi_startproc
	cbz	x3, .L27
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	lsl	x3, x3, 4
	add	x5, sp, 32
	mov	x4, 0
	.p2align 5,,15
.L21:
	ldr	q30, [x1, x4]
	ldr	q31, [x0, x4]
	str	q30, [sp, 16]
	stp	q31, q30, [x5]
	fadd	v30.4s, v30.4s, v31.4s
	str	q31, [sp]
	ins	v30.s[3], v31.s[3]
	str	q30, [x2, x4]
	add	x4, x4, 16
	cmp	x3, x4
	bne	.L21
	add	sp, sp, 64
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L27:
	ret
	.cfi_endproc
.LFE5350:
	.size	cg_with_w_expr, .-cg_with_w_expr
	.align	2
	.p2align 5,,15
	.global	cg_cross3
	.type	cg_cross3, %function
cg_cross3:
.LFB5351:
	.cfi_startproc
	cbz	x3, .L38
	adrp	x6, .LC1
	adrp	x5, .LC0
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	lsl	x3, x3, 4
	ldr	q30, [x6, #:lo12:.LC1]
	mov	x4, 0
	ldr	q31, [x5, #:lo12:.LC0]
	add	x5, sp, 32
	.p2align 5,,15
.L32:
	ldr	q3, [x0, x4]
	ldr	q1, [x1, x4]
	tbl	v27.16b, {v3.16b}, v31.16b
	tbl	v29.16b, {v3.16b}, v30.16b
	tbl	v26.16b, {v1.16b}, v30.16b
	stp	q3, q1, [sp]
	tbl	v28.16b, {v1.16b}, v31.16b
	stp	q3, q1, [x5]
	fmul	v26.4s, v27.4s, v26.4s
	fmls	v26.4s, v29.4s, v28.4s
	str	q26, [x2, x4]
	add	x4, x4, 16
	cmp	x3, x4
	bne	.L32
	add	sp, sp, 64
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L38:
	ret
	.cfi_endproc
.LFE5351:
	.size	cg_cross3, .-cg_cross3
	.align	2
	.p2align 5,,15
	.global	cg_cross3_value
	.type	cg_cross3_value, %function
cg_cross3_value:
.LFB5352:
	.cfi_startproc
	ldr	q30, [x0]
	adrp	x2, .LC0
	adrp	x0, .LC1
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	ldr	q29, [x1]
	ldr	q31, [x2, #:lo12:.LC0]
	ldr	q28, [x0, #:lo12:.LC1]
	add	sp, sp, 64
	.cfi_def_cfa_offset 0
	tbl	v0.16b, {v30.16b}, v31.16b
	tbl	v31.16b, {v29.16b}, v31.16b
	tbl	v29.16b, {v29.16b}, v28.16b
	tbl	v30.16b, {v30.16b}, v28.16b
	fmul	v0.4s, v0.4s, v29.4s
	fmls	v0.4s, v30.4s, v31.4s
	ret
	.cfi_endproc
.LFE5352:
	.size	cg_cross3_value, .-cg_cross3_value
	.section	.rodata.cst16,"aM",@progbits,16
	.align	4
.LC0:
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
.LC1:
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
	.ident	"GCC: (Debian 14.2.0-19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
