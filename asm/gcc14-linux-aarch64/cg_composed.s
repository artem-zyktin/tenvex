# g++ (Debian 14.2.0-19) 14.2.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_composed.cpp
	.arch armv8-a
	.file	"cg_composed.cpp"
	.text
	.align	2
	.p2align 5,,15
	.global	cg_lerp
	.type	cg_lerp, %function
cg_lerp:
.LFB5348:
	.cfi_startproc
	cbz	x3, .L7
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	lsl	x4, x3, 4
	dup	v0.4s, v0.s[0]
	mov	x5, sp
	mov	x3, 0
	.p2align 5,,15
.L3:
	ldr	q1, [x0, x3]
	ldr	q2, [x1, x3]
	mov	v31.16b, v1.16b
	fsub	v30.4s, v2.4s, v1.4s
	stp	q2, q1, [sp, 32]
	stp	q2, q1, [x5]
	fmla	v31.4s, v30.4s, v0.4s
	str	q31, [x2, x3]
	add	x3, x3, 16
	cmp	x4, x3
	bne	.L3
	add	sp, sp, 64
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L7:
	ret
	.cfi_endproc
.LFE5348:
	.size	cg_lerp, .-cg_lerp
	.align	2
	.p2align 5,,15
	.global	cg_clamp
	.type	cg_clamp, %function
cg_clamp:
.LFB5349:
	.cfi_startproc
	cbz	x4, .L19
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	lsl	x4, x4, 4
	mov	x6, sp
	mov	x5, 0
	.p2align 5,,15
.L13:
	ldr	q0, [x1, x5]
	ldr	q1, [x0, x5]
	ldr	q29, [x2, x5]
	fmax	v31.4s, v1.4s, v0.4s
	stp	q1, q0, [sp, 32]
	stp	q1, q0, [x6]
	fmin	v31.4s, v31.4s, v29.4s
	str	q31, [x3, x5]
	add	x5, x5, 16
	cmp	x4, x5
	bne	.L13
	add	sp, sp, 64
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L19:
	ret
	.cfi_endproc
.LFE5349:
	.size	cg_clamp, .-cg_clamp
	.align	2
	.p2align 5,,15
	.global	cg_reflect
	.type	cg_reflect, %function
cg_reflect:
.LFB5350:
	.cfi_startproc
	cbz	x3, .L30
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	lsl	x3, x3, 4
	mov	x5, sp
	mov	x4, 0
	.p2align 5,,15
.L24:
	ldr	q0, [x0, x4]
	ldr	q30, [x1, x4]
	mov	v31.16b, v0.16b
	fmul	v29.4s, v30.4s, v0.4s
	stp	q0, q30, [sp, 32]
	stp	q0, q30, [x5]
	ins	v29.s[3], wzr
	faddp	v29.4s, v29.4s, v29.4s
	faddp	v29.4s, v29.4s, v29.4s
	fadd	s29, s29, s29
	fmls	v31.4s, v30.4s, v29.s[0]
	str	q31, [x2, x4]
	add	x4, x4, 16
	cmp	x3, x4
	bne	.L24
	add	sp, sp, 64
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L30:
	ret
	.cfi_endproc
.LFE5350:
	.size	cg_reflect, .-cg_reflect
	.align	2
	.p2align 5,,15
	.global	cg_distance3_sq
	.type	cg_distance3_sq, %function
cg_distance3_sq:
.LFB5351:
	.cfi_startproc
	cbz	x3, .L41
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	lsl	x3, x3, 4
	mov	x5, sp
	mov	x4, 0
	.p2align 5,,15
.L35:
	ldr	q29, [x1, x4]
	ldr	q0, [x0, x4]
	add	x4, x4, 16
	fsub	v31.4s, v0.4s, v29.4s
	stp	q0, q29, [sp, 32]
	stp	q0, q29, [x5]
	fmul	v31.4s, v31.4s, v31.4s
	ins	v31.s[3], wzr
	faddp	v31.4s, v31.4s, v31.4s
	faddp	v31.4s, v31.4s, v31.4s
	str	s31, [x2], 4
	cmp	x4, x3
	bne	.L35
	add	sp, sp, 64
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L41:
	ret
	.cfi_endproc
.LFE5351:
	.size	cg_distance3_sq, .-cg_distance3_sq
	.align	2
	.p2align 5,,15
	.global	cg_orthogonal
	.type	cg_orthogonal, %function
cg_orthogonal:
.LFB5352:
	.cfi_startproc
	cbz	x2, .L56
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	lsl	x6, x2, 4
	mov	x3, 0
	.p2align 5,,15
.L49:
	add	x2, x0, x3
	ldr	s29, [x0, x3]
	ldp	s31, s30, [x2, 4]
	fabs	s27, s29
	fabs	s28, s30
	fneg	s26, s31
	fcmpe	s27, s28
	bgt	.L50
	fneg	s30, s30
	fmov	w2, s31
	mov	x8, 0
	mov	x7, 0
	bfi	x4, x8, 0, 32
	fmov	x8, d30
	bfi	x5, x2, 0, 32
	bfi	x5, x7, 32, 32
	bfi	x4, x8, 32, 32
	fmov	d31, x4
	ins	v31.d[1], x5
	str	q31, [x1, x3]
	add	x3, x3, 16
	cmp	x6, x3
	bne	.L49
	add	sp, sp, 16
	.cfi_remember_state
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L50:
	.cfi_restore_state
	str	xzr, [sp, 8]
	stp	s26, s29, [sp]
	ldr	q31, [sp]
	str	q31, [x1, x3]
	add	x3, x3, 16
	cmp	x3, x6
	bne	.L49
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L56:
	ret
	.cfi_endproc
.LFE5352:
	.size	cg_orthogonal, .-cg_orthogonal
	.align	2
	.p2align 5,,15
	.global	cg_nlerp
	.type	cg_nlerp, %function
cg_nlerp:
.LFB5353:
	.cfi_startproc
	cbz	x3, .L69
	fmov	s31, 1.0e+0
	sub	sp, sp, #96
	.cfi_def_cfa_offset 96
	fneg	s30, s0
	mov	x7, sp
	fsub	s31, s31, s0
	add	x6, sp, 32
	mov	x4, 0
	mov	x5, 0
	dup	v31.4s, v31.s[0]
	.p2align 5,,15
.L63:
	ldr	q28, [x1, x4]
	add	x5, x5, 1
	ldr	q29, [x0, x4]
	fmul	v2.4s, v29.4s, v28.4s
	stp	q29, q31, [x7]
	str	q28, [sp, 64]
	faddp	v2.4s, v2.4s, v2.4s
	faddp	v2.4s, v2.4s, v2.4s
	fcmpe	s2, #0.0
	fcsel	s1, s30, s0, mi
	dup	v1.4s, v1.s[0]
	fmul	v27.4s, v1.4s, v28.4s
	stp	q28, q1, [x6]
	str	q1, [sp, 80]
	fmla	v27.4s, v31.4s, v29.4s
	fmul	v26.4s, v27.4s, v27.4s
	faddp	v26.4s, v26.4s, v26.4s
	faddp	v26.4s, v26.4s, v26.4s
	dup	v26.4s, v26.s[0]
	fsqrt	v26.4s, v26.4s
	fdiv	v26.4s, v27.4s, v26.4s
	str	q26, [x2, x4]
	add	x4, x4, 16
	cmp	x3, x5
	bne	.L63
	add	sp, sp, 96
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L69:
	ret
	.cfi_endproc
.LFE5353:
	.size	cg_nlerp, .-cg_nlerp
	.ident	"GCC: (Debian 14.2.0-19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
