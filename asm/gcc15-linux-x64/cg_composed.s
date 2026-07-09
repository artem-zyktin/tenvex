# g++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_composed.cpp
	.file	"cg_composed.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	cg_lerp
	.type	cg_lerp, @function
cg_lerp:
.LFB2080:
	.cfi_startproc
	endbr64
	mov	r8, rdi
	mov	rdi, rsi
	mov	rsi, rdx
	mov	rdx, rcx
	sal	rdx, 4
	xor	eax, eax
	shufps	xmm0, xmm0, 0
	test	rcx, rcx
	je	.L1
	.p2align 5
	.p2align 4
	.p2align 3
.L3:
	movaps	xmm2, XMMWORD PTR [r8+rax]
	movaps	xmm1, XMMWORD PTR [rdi+rax]
	subps	xmm1, xmm2
	mulps	xmm1, xmm0
	addps	xmm1, xmm2
	movaps	XMMWORD PTR [rsi+rax], xmm1
	add	rax, 16
	cmp	rdx, rax
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE2080:
	.size	cg_lerp, .-cg_lerp
	.p2align 4
	.globl	cg_clamp
	.type	cg_clamp, @function
cg_clamp:
.LFB2081:
	.cfi_startproc
	endbr64
	test	r8, r8
	je	.L8
	sal	r8, 4
	xor	eax, eax
	.p2align 5
	.p2align 4
	.p2align 3
.L10:
	movaps	xmm0, XMMWORD PTR [rdi+rax]
	maxps	xmm0, XMMWORD PTR [rsi+rax]
	minps	xmm0, XMMWORD PTR [rdx+rax]
	movaps	XMMWORD PTR [rcx+rax], xmm0
	add	rax, 16
	cmp	r8, rax
	jne	.L10
.L8:
	ret
	.cfi_endproc
.LFE2081:
	.size	cg_clamp, .-cg_clamp
	.p2align 4
	.globl	cg_reflect
	.type	cg_reflect, @function
cg_reflect:
.LFB2082:
	.cfi_startproc
	endbr64
	test	rcx, rcx
	je	.L15
	sal	rcx, 4
	xor	eax, eax
	.p2align 6
	.p2align 4
	.p2align 3
.L17:
	movaps	xmm3, XMMWORD PTR [rsi+rax]
	movaps	xmm2, XMMWORD PTR [rdi+rax]
	movaps	xmm1, xmm3
	mulps	xmm1, xmm2
	movaps	xmm4, xmm1
	movaps	xmm0, xmm1
	shufps	xmm4, xmm1, 85
	addss	xmm0, xmm4
	movhlps	xmm1, xmm1
	addss	xmm0, xmm1
	shufps	xmm0, xmm0, 0
	addps	xmm0, xmm0
	mulps	xmm0, xmm3
	subps	xmm2, xmm0
	movaps	XMMWORD PTR [rdx+rax], xmm2
	add	rax, 16
	cmp	rcx, rax
	jne	.L17
.L15:
	ret
	.cfi_endproc
.LFE2082:
	.size	cg_reflect, .-cg_reflect
	.p2align 4
	.globl	cg_distance3_sq
	.type	cg_distance3_sq, @function
cg_distance3_sq:
.LFB2083:
	.cfi_startproc
	endbr64
	test	rcx, rcx
	je	.L22
	sal	rcx, 4
	xor	eax, eax
	.p2align 6
	.p2align 4
	.p2align 3
.L24:
	movaps	xmm0, XMMWORD PTR [rdi+rax]
	subps	xmm0, XMMWORD PTR [rsi+rax]
	add	rax, 16
	add	rdx, 4
	mulps	xmm0, xmm0
	movaps	xmm2, xmm0
	movaps	xmm1, xmm0
	shufps	xmm2, xmm0, 85
	addss	xmm1, xmm2
	movhlps	xmm0, xmm0
	addss	xmm1, xmm0
	movss	DWORD PTR -4[rdx], xmm1
	cmp	rcx, rax
	jne	.L24
.L22:
	ret
	.cfi_endproc
.LFE2083:
	.size	cg_distance3_sq, .-cg_distance3_sq
	.p2align 4
	.globl	cg_orthogonal
	.type	cg_orthogonal, @function
cg_orthogonal:
.LFB2084:
	.cfi_startproc
	endbr64
	test	rdx, rdx
	je	.L29
	sal	rdx, 4
	xor	eax, eax
	.p2align 4
	.p2align 3
.L34:
	lea	rcx, [rdi+rax]
	movss	xmm1, DWORD PTR 8[rcx]
	movss	xmm2, DWORD PTR [rcx]
	movss	xmm0, DWORD PTR 4[rcx]
	movaps	xmm3, xmm1
	movaps	xmm4, xmm2
	andps	xmm3, XMMWORD PTR .LC0[rip]
	andps	xmm4, XMMWORD PTR .LC0[rip]
	comiss	xmm4, xmm3
	jbe	.L39
	xorps	xmm0, XMMWORD PTR .LC1[rip]
	unpcklps	xmm0, xmm2
	movq	xmm0, xmm0
	movaps	XMMWORD PTR [rsi+rax], xmm0
	add	rax, 16
	cmp	rdx, rax
	jne	.L34
	ret
	.p2align 4,,10
	.p2align 3
.L39:
	xorps	xmm1, XMMWORD PTR .LC1[rip]
	pxor	xmm2, xmm2
	pxor	xmm6, xmm6
	unpcklps	xmm0, xmm6
	unpcklps	xmm2, xmm1
	movaps	xmm1, xmm2
	movlhps	xmm1, xmm0
	movaps	XMMWORD PTR [rsi+rax], xmm1
	add	rax, 16
	cmp	rdx, rax
	jne	.L34
.L29:
	ret
	.cfi_endproc
.LFE2084:
	.size	cg_orthogonal, .-cg_orthogonal
	.p2align 4
	.globl	cg_nlerp
	.type	cg_nlerp, @function
cg_nlerp:
.LFB2085:
	.cfi_startproc
	endbr64
	movaps	xmm4, xmm0
	test	rcx, rcx
	je	.L40
	movaps	xmm6, xmm0
	xorps	xmm6, XMMWORD PTR .LC1[rip]
	sal	rcx, 4
	xor	eax, eax
	movss	xmm3, DWORD PTR .LC3[rip]
	pxor	xmm2, xmm2
	subss	xmm3, xmm0
	shufps	xmm3, xmm3, 0
	.p2align 4
	.p2align 3
.L44:
	movaps	xmm5, XMMWORD PTR [rsi+rax]
	movaps	xmm1, XMMWORD PTR [rdi+rax]
	movaps	xmm7, xmm4
	movaps	xmm0, xmm5
	mulps	xmm0, xmm1
	mulps	xmm1, xmm3
	haddps	xmm0, xmm0
	haddps	xmm0, xmm0
	cmpltss	xmm0, xmm2
	blendvps	xmm7, xmm6, xmm0
	movaps	xmm0, xmm7
	shufps	xmm0, xmm0, 0
	mulps	xmm0, xmm5
	addps	xmm1, xmm0
	movaps	xmm0, xmm1
	mulps	xmm0, xmm1
	haddps	xmm0, xmm0
	haddps	xmm0, xmm0
	sqrtps	xmm0, xmm0
	divps	xmm1, xmm0
	movaps	XMMWORD PTR [rdx+rax], xmm1
	add	rax, 16
	cmp	rcx, rax
	jne	.L44
.L40:
	ret
	.cfi_endproc
.LFE2085:
	.size	cg_nlerp, .-cg_nlerp
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	2147483647
	.long	0
	.long	0
	.long	0
	.align 16
.LC1:
	.long	-2147483648
	.long	0
	.long	0
	.long	0
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC3:
	.long	1065353216
	.ident	"GCC: (Ubuntu 15.2.0-16ubuntu1) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
