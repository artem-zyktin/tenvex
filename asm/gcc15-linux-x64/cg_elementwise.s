# g++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_elementwise.cpp
	.file	"cg_elementwise.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	cg_aabb
	.type	cg_aabb, @function
cg_aabb:
.LFB2080:
	.cfi_startproc
	endbr64
	movaps	xmm1, XMMWORD PTR [rdi]
	cmp	rsi, 1
	jbe	.L4
	sal	rsi, 4
	lea	rax, 16[rdi]
	movaps	xmm2, xmm1
	add	rdi, rsi
	.p2align 5
	.p2align 4
	.p2align 3
.L3:
	movaps	xmm0, XMMWORD PTR [rax]
	add	rax, 16
	minps	xmm1, xmm0
	maxps	xmm2, xmm0
	cmp	rdi, rax
	jne	.L3
	movaps	XMMWORD PTR [rdx], xmm1
	movaps	XMMWORD PTR [rcx], xmm2
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	movaps	xmm2, xmm1
	movaps	XMMWORD PTR [rdx], xmm1
	movaps	XMMWORD PTR [rcx], xmm2
	ret
	.cfi_endproc
.LFE2080:
	.size	cg_aabb, .-cg_aabb
	.p2align 4
	.globl	cg_saturate
	.type	cg_saturate, @function
cg_saturate:
.LFB2081:
	.cfi_startproc
	endbr64
	test	rdx, rdx
	je	.L7
	movss	xmm3, DWORD PTR .LC1[rip]
	sal	rdx, 4
	xor	eax, eax
	shufps	xmm3, xmm3, 0
	.p2align 5
	.p2align 4
	.p2align 3
.L9:
	movaps	xmm0, XMMWORD PTR [rdi+rax]
	pxor	xmm1, xmm1
	cmpltps	xmm1, xmm0
	andps	xmm0, xmm1
	minps	xmm0, xmm3
	movaps	XMMWORD PTR [rsi+rax], xmm0
	add	rax, 16
	cmp	rdx, rax
	jne	.L9
.L7:
	ret
	.cfi_endproc
.LFE2081:
	.size	cg_saturate, .-cg_saturate
	.p2align 4
	.globl	cg_with_w_expr
	.type	cg_with_w_expr, @function
cg_with_w_expr:
.LFB2082:
	.cfi_startproc
	endbr64
	test	rcx, rcx
	je	.L14
	sal	rcx, 4
	xor	eax, eax
	.p2align 5
	.p2align 4
	.p2align 3
.L16:
	movaps	xmm1, XMMWORD PTR [rdi+rax]
	movaps	xmm0, XMMWORD PTR [rsi+rax]
	addps	xmm0, xmm1
	blendps	xmm0, xmm1, 8
	movaps	XMMWORD PTR [rdx+rax], xmm0
	add	rax, 16
	cmp	rcx, rax
	jne	.L16
.L14:
	ret
	.cfi_endproc
.LFE2082:
	.size	cg_with_w_expr, .-cg_with_w_expr
	.p2align 4
	.globl	cg_cross3
	.type	cg_cross3, @function
cg_cross3:
.LFB2083:
	.cfi_startproc
	endbr64
	test	rcx, rcx
	je	.L21
	sal	rcx, 4
	xor	eax, eax
	.p2align 6
	.p2align 4
	.p2align 3
.L23:
	movaps	xmm2, XMMWORD PTR [rsi+rax]
	movaps	xmm1, XMMWORD PTR [rdi+rax]
	movaps	xmm0, xmm2
	shufps	xmm0, xmm2, 201
	mulps	xmm0, xmm1
	shufps	xmm1, xmm1, 201
	mulps	xmm1, xmm2
	subps	xmm0, xmm1
	shufps	xmm0, xmm0, 201
	movaps	XMMWORD PTR [rdx+rax], xmm0
	add	rax, 16
	cmp	rcx, rax
	jne	.L23
.L21:
	ret
	.cfi_endproc
.LFE2083:
	.size	cg_cross3, .-cg_cross3
	.p2align 4
	.globl	cg_cross3_value
	.type	cg_cross3_value, @function
cg_cross3_value:
.LFB2084:
	.cfi_startproc
	endbr64
	movaps	xmm2, XMMWORD PTR [rsi]
	movaps	xmm1, XMMWORD PTR [rdi]
	movaps	xmm0, xmm2
	shufps	xmm0, xmm2, 201
	mulps	xmm0, xmm1
	shufps	xmm1, xmm1, 201
	mulps	xmm1, xmm2
	subps	xmm0, xmm1
	shufps	xmm0, xmm0, 201
	ret
	.cfi_endproc
.LFE2084:
	.size	cg_cross3_value, .-cg_cross3_value
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC1:
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
