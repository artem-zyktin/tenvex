# g++ (Debian 14.2.0-19) 14.2.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_reductions.cpp
	.arch armv8-a
	.file	"cg_reductions.cpp"
	.text
	.align	2
	.p2align 5,,15
	.global	cg_dot3
	.type	cg_dot3, %function
cg_dot3:
.LFB5348:
	.cfi_startproc
	cbz	x3, .L9
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	lsl	x3, x3, 4
	add	x5, sp, 32
	mov	x4, 0
	.p2align 5,,15
.L3:
	ldr	q29, [x1, x4]
	ldr	q0, [x0, x4]
	add	x4, x4, 16
	fmul	v31.4s, v29.4s, v0.4s
	stp	q0, q29, [sp]
	stp	q0, q29, [x5]
	ins	v31.s[3], wzr
	faddp	v31.4s, v31.4s, v31.4s
	faddp	v31.4s, v31.4s, v31.4s
	str	s31, [x2], 4
	cmp	x4, x3
	bne	.L3
	add	sp, sp, 64
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L9:
	ret
	.cfi_endproc
.LFE5348:
	.size	cg_dot3, .-cg_dot3
	.align	2
	.p2align 5,,15
	.global	cg_dot4
	.type	cg_dot4, %function
cg_dot4:
.LFB5349:
	.cfi_startproc
	cbz	x3, .L21
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	lsl	x3, x3, 4
	add	x5, sp, 32
	mov	x4, 0
	.p2align 5,,15
.L15:
	ldr	q29, [x1, x4]
	ldr	q0, [x0, x4]
	add	x4, x4, 16
	fmul	v31.4s, v29.4s, v0.4s
	stp	q0, q29, [sp]
	stp	q0, q29, [x5]
	faddp	v31.4s, v31.4s, v31.4s
	faddp	v31.4s, v31.4s, v31.4s
	str	s31, [x2], 4
	cmp	x4, x3
	bne	.L15
	add	sp, sp, 64
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L21:
	ret
	.cfi_endproc
.LFE5349:
	.size	cg_dot4, .-cg_dot4
	.align	2
	.p2align 5,,15
	.global	cg_magnitude3
	.type	cg_magnitude3, %function
cg_magnitude3:
.LFB5350:
	.cfi_startproc
	cbz	x2, .L24
	mov	x3, 0
	.p2align 5,,15
.L26:
	lsl	x4, x3, 4
	ldr	q31, [x0, x4]
	fmul	v31.4s, v31.4s, v31.4s
	ins	v31.s[3], wzr
	faddp	v31.4s, v31.4s, v31.4s
	faddp	v31.4s, v31.4s, v31.4s
	dup	v31.4s, v31.s[0]
	fsqrt	v31.4s, v31.4s
	str	s31, [x1, x3, lsl 2]
	add	x3, x3, 1
	cmp	x2, x3
	bne	.L26
.L24:
	ret
	.cfi_endproc
.LFE5350:
	.size	cg_magnitude3, .-cg_magnitude3
	.align	2
	.p2align 5,,15
	.global	cg_magnitude3_sq
	.type	cg_magnitude3_sq, %function
cg_magnitude3_sq:
.LFB5351:
	.cfi_startproc
	cbz	x2, .L31
	mov	x3, 0
	.p2align 5,,15
.L33:
	lsl	x4, x3, 4
	ldr	q31, [x0, x4]
	fmul	v31.4s, v31.4s, v31.4s
	ins	v31.s[3], wzr
	faddp	v31.4s, v31.4s, v31.4s
	faddp	v31.4s, v31.4s, v31.4s
	str	s31, [x1, x3, lsl 2]
	add	x3, x3, 1
	cmp	x2, x3
	bne	.L33
.L31:
	ret
	.cfi_endproc
.LFE5351:
	.size	cg_magnitude3_sq, .-cg_magnitude3_sq
	.align	2
	.p2align 5,,15
	.global	cg_mag3_lt_mag3
	.type	cg_mag3_lt_mag3, %function
cg_mag3_lt_mag3:
.LFB5352:
	.cfi_startproc
	cbz	x3, .L38
	lsl	x5, x3, 4
	mov	x4, 0
	.p2align 5,,15
.L40:
	ldr	q31, [x0, x4]
	ldr	q30, [x1, x4]
	add	x4, x4, 16
	fmul	v31.4s, v31.4s, v31.4s
	fmul	v30.4s, v30.4s, v30.4s
	ins	v31.s[3], wzr
	faddp	v31.4s, v31.4s, v31.4s
	ins	v30.s[3], wzr
	faddp	v30.4s, v30.4s, v30.4s
	faddp	v31.4s, v31.4s, v31.4s
	faddp	v30.4s, v30.4s, v30.4s
	fcmpe	s31, s30
	cset	w3, mi
	strb	w3, [x2], 1
	cmp	x5, x4
	bne	.L40
.L38:
	ret
	.cfi_endproc
.LFE5352:
	.size	cg_mag3_lt_mag3, .-cg_mag3_lt_mag3
	.align	2
	.p2align 5,,15
	.global	cg_mag3_lt_scalar
	.type	cg_mag3_lt_scalar, %function
cg_mag3_lt_scalar:
.LFB5353:
	.cfi_startproc
	mov	x5, x2
	cbz	x2, .L45
	fcmpe	s0, #0.0
	bmi	.L47
	fmul	s0, s0, s0
	mov	x3, 0
	.p2align 5,,15
.L48:
	lsl	x4, x3, 4
	ldr	q31, [x0, x4]
	fmul	v31.4s, v31.4s, v31.4s
	ins	v31.s[3], wzr
	faddp	v31.4s, v31.4s, v31.4s
	faddp	v31.4s, v31.4s, v31.4s
	fcmpe	s0, s31
	cset	w4, gt
	strb	w4, [x1, x3]
	add	x3, x3, 1
	cmp	x5, x3
	bne	.L48
.L45:
	ret
	.p2align 2,,3
.L47:
	mov	x0, x1
	mov	w1, 0
	b	memset
	.cfi_endproc
.LFE5353:
	.size	cg_mag3_lt_scalar, .-cg_mag3_lt_scalar
	.ident	"GCC: (Debian 14.2.0-19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
