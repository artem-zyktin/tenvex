# g++ (Debian 14.2.0-19) 14.2.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_normalize.cpp
	.arch armv8-a
	.file	"cg_normalize.cpp"
	.text
	.align	2
	.p2align 5,,15
	.global	cg_normalize3
	.type	cg_normalize3, %function
cg_normalize3:
.LFB5348:
	.cfi_startproc
	cbz	x2, .L1
	mov	x3, 0
	mov	x4, 0
	.p2align 5,,15
.L3:
	ldr	q31, [x0, x3]
	add	x4, x4, 1
	fmul	v30.4s, v31.4s, v31.4s
	ins	v30.s[3], wzr
	faddp	v30.4s, v30.4s, v30.4s
	faddp	v30.4s, v30.4s, v30.4s
	dup	v30.4s, v30.s[0]
	fsqrt	v30.4s, v30.4s
	fdiv	v30.4s, v31.4s, v30.4s
	ins	v30.s[3], v31.s[3]
	str	q30, [x1, x3]
	add	x3, x3, 16
	cmp	x2, x4
	bne	.L3
.L1:
	ret
	.cfi_endproc
.LFE5348:
	.size	cg_normalize3, .-cg_normalize3
	.align	2
	.p2align 5,,15
	.global	cg_normalize3_fast
	.type	cg_normalize3_fast, %function
cg_normalize3_fast:
.LFB5349:
	.cfi_startproc
	cbz	x2, .L9
	lsl	x2, x2, 4
	mov	x3, 0
	.p2align 5,,15
.L11:
	ldr	q31, [x0, x3]
	fmul	v30.4s, v31.4s, v31.4s
	ins	v30.s[3], wzr
	faddp	v30.4s, v30.4s, v30.4s
	faddp	v30.4s, v30.4s, v30.4s
	dup	v30.4s, v30.s[0]
	frsqrte	v29.4s, v30.4s
	fmul	v30.4s, v30.4s, v29.4s
	frsqrts	v30.4s, v30.4s, v29.4s
	fmul	v30.4s, v29.4s, v30.4s
	fmul	v30.4s, v30.4s, v31.4s
	ins	v30.s[3], v31.s[3]
	str	q30, [x1, x3]
	add	x3, x3, 16
	cmp	x2, x3
	bne	.L11
.L9:
	ret
	.cfi_endproc
.LFE5349:
	.size	cg_normalize3_fast, .-cg_normalize3_fast
	.align	2
	.p2align 5,,15
	.global	cg_normalize4
	.type	cg_normalize4, %function
cg_normalize4:
.LFB5350:
	.cfi_startproc
	cbz	x2, .L16
	mov	x3, 0
	mov	x4, 0
	.p2align 5,,15
.L18:
	ldr	q31, [x0, x3]
	add	x4, x4, 1
	fmul	v30.4s, v31.4s, v31.4s
	faddp	v30.4s, v30.4s, v30.4s
	faddp	v30.4s, v30.4s, v30.4s
	dup	v30.4s, v30.s[0]
	fsqrt	v30.4s, v30.4s
	fdiv	v30.4s, v31.4s, v30.4s
	str	q30, [x1, x3]
	add	x3, x3, 16
	cmp	x2, x4
	bne	.L18
.L16:
	ret
	.cfi_endproc
.LFE5350:
	.size	cg_normalize4, .-cg_normalize4
	.align	2
	.p2align 5,,15
	.global	cg_normalize3_value
	.type	cg_normalize3_value, %function
cg_normalize3_value:
.LFB5351:
	.cfi_startproc
	ldr	q31, [x0]
	fmul	v0.4s, v31.4s, v31.4s
	ins	v0.s[3], wzr
	faddp	v0.4s, v0.4s, v0.4s
	faddp	v0.4s, v0.4s, v0.4s
	dup	v0.4s, v0.s[0]
	fsqrt	v0.4s, v0.4s
	fdiv	v0.4s, v31.4s, v0.4s
	ins	v0.s[3], v31.s[3]
	ret
	.cfi_endproc
.LFE5351:
	.size	cg_normalize3_value, .-cg_normalize3_value
	.align	2
	.p2align 5,,15
	.global	cg_normalize3_fast_value
	.type	cg_normalize3_fast_value, %function
cg_normalize3_fast_value:
.LFB5352:
	.cfi_startproc
	ldr	q30, [x0]
	fmul	v31.4s, v30.4s, v30.4s
	ins	v31.s[3], wzr
	faddp	v31.4s, v31.4s, v31.4s
	faddp	v31.4s, v31.4s, v31.4s
	dup	v31.4s, v31.s[0]
	frsqrte	v0.4s, v31.4s
	fmul	v31.4s, v31.4s, v0.4s
	frsqrts	v31.4s, v31.4s, v0.4s
	fmul	v0.4s, v0.4s, v31.4s
	fmul	v0.4s, v0.4s, v30.4s
	ins	v0.s[3], v30.s[3]
	ret
	.cfi_endproc
.LFE5352:
	.size	cg_normalize3_fast_value, .-cg_normalize3_fast_value
	.ident	"GCC: (Debian 14.2.0-19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
