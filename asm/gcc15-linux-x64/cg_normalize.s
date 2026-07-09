# g++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_normalize.cpp
	.file	"cg_normalize.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	cg_normalize3
	.type	cg_normalize3, @function
cg_normalize3:
.LFB2080:
	.cfi_startproc
	endbr64
	test	rdx, rdx
	je	.L1
	sal	rdx, 4
	xor	eax, eax
	.p2align 4
	.p2align 3
.L3:
	movaps	xmm2, XMMWORD PTR [rdi+rax]
	movaps	xmm1, xmm2
	mulps	xmm1, xmm2
	movaps	xmm3, xmm1
	movaps	xmm0, xmm1
	shufps	xmm3, xmm1, 85
	addss	xmm0, xmm3
	movhlps	xmm1, xmm1
	addss	xmm0, xmm1
	movaps	xmm1, xmm2
	shufps	xmm0, xmm0, 0
	sqrtps	xmm0, xmm0
	divps	xmm1, xmm0
	movaps	xmm0, xmm1
	blendps	xmm0, xmm2, 8
	movaps	XMMWORD PTR [rsi+rax], xmm0
	add	rax, 16
	cmp	rdx, rax
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE2080:
	.size	cg_normalize3, .-cg_normalize3
	.p2align 4
	.globl	cg_normalize3_fast
	.type	cg_normalize3_fast, @function
cg_normalize3_fast:
.LFB2081:
	.cfi_startproc
	endbr64
	test	rdx, rdx
	je	.L9
	movss	xmm5, DWORD PTR .LC1[rip]
	movss	xmm4, DWORD PTR .LC3[rip]
	sal	rdx, 4
	xor	eax, eax
	shufps	xmm5, xmm5, 0
	shufps	xmm4, xmm4, 0
	.p2align 4
	.p2align 3
.L11:
	movaps	xmm2, XMMWORD PTR [rdi+rax]
	movaps	xmm1, xmm2
	mulps	xmm1, xmm2
	movaps	xmm3, xmm1
	movaps	xmm0, xmm1
	shufps	xmm3, xmm1, 85
	addss	xmm0, xmm3
	movhlps	xmm1, xmm1
	addss	xmm0, xmm1
	shufps	xmm0, xmm0, 0
	rsqrtps	xmm1, xmm0
	mulps	xmm0, xmm5
	movaps	xmm3, xmm1
	mulps	xmm3, xmm1
	mulps	xmm3, xmm0
	movaps	xmm0, xmm4
	subps	xmm0, xmm3
	mulps	xmm0, xmm1
	mulps	xmm0, xmm2
	blendps	xmm0, xmm2, 8
	movaps	XMMWORD PTR [rsi+rax], xmm0
	add	rax, 16
	cmp	rdx, rax
	jne	.L11
.L9:
	ret
	.cfi_endproc
.LFE2081:
	.size	cg_normalize3_fast, .-cg_normalize3_fast
	.p2align 4
	.globl	cg_normalize4
	.type	cg_normalize4, @function
cg_normalize4:
.LFB2082:
	.cfi_startproc
	endbr64
	test	rdx, rdx
	je	.L16
	sal	rdx, 4
	xor	eax, eax
	.p2align 6
	.p2align 4
	.p2align 3
.L18:
	movaps	xmm1, XMMWORD PTR [rdi+rax]
	movaps	xmm0, xmm1
	mulps	xmm0, xmm1
	haddps	xmm0, xmm0
	haddps	xmm0, xmm0
	sqrtps	xmm0, xmm0
	divps	xmm1, xmm0
	movaps	XMMWORD PTR [rsi+rax], xmm1
	add	rax, 16
	cmp	rdx, rax
	jne	.L18
.L16:
	ret
	.cfi_endproc
.LFE2082:
	.size	cg_normalize4, .-cg_normalize4
	.p2align 4
	.globl	cg_normalize3_value
	.type	cg_normalize3_value, @function
cg_normalize3_value:
.LFB2083:
	.cfi_startproc
	endbr64
	movaps	xmm2, XMMWORD PTR [rdi]
	movaps	xmm1, xmm2
	mulps	xmm1, xmm2
	movaps	xmm3, xmm1
	movaps	xmm0, xmm1
	shufps	xmm3, xmm1, 85
	addss	xmm0, xmm3
	movhlps	xmm1, xmm1
	addss	xmm0, xmm1
	shufps	xmm0, xmm0, 0
	sqrtps	xmm1, xmm0
	movaps	xmm0, xmm2
	divps	xmm0, xmm1
	blendps	xmm0, xmm2, 8
	ret
	.cfi_endproc
.LFE2083:
	.size	cg_normalize3_value, .-cg_normalize3_value
	.p2align 4
	.globl	cg_normalize3_fast_value
	.type	cg_normalize3_fast_value, @function
cg_normalize3_fast_value:
.LFB2084:
	.cfi_startproc
	endbr64
	movaps	xmm2, XMMWORD PTR [rdi]
	movss	xmm4, DWORD PTR .LC1[rip]
	movaps	xmm0, xmm2
	shufps	xmm4, xmm4, 0
	mulps	xmm0, xmm2
	movaps	xmm3, xmm0
	movaps	xmm1, xmm0
	shufps	xmm3, xmm0, 85
	addss	xmm1, xmm3
	movhlps	xmm0, xmm0
	addss	xmm1, xmm0
	shufps	xmm1, xmm1, 0
	rsqrtps	xmm3, xmm1
	mulps	xmm1, xmm4
	movaps	xmm0, xmm3
	mulps	xmm0, xmm3
	mulps	xmm1, xmm0
	movss	xmm0, DWORD PTR .LC3[rip]
	shufps	xmm0, xmm0, 0
	subps	xmm0, xmm1
	mulps	xmm0, xmm3
	mulps	xmm0, xmm2
	blendps	xmm0, xmm2, 8
	ret
	.cfi_endproc
.LFE2084:
	.size	cg_normalize3_fast_value, .-cg_normalize3_fast_value
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC1:
	.long	1056964608
	.align 4
.LC3:
	.long	1069547520
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
