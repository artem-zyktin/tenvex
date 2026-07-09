# g++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_compound.cpp
	.file	"cg_compound.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	cg_compound_et
	.type	cg_compound_et, @function
cg_compound_et:
.LFB2080:
	.cfi_startproc
	endbr64
	test	r8, r8
	je	.L1
	movss	xmm4, DWORD PTR .LC1[rip]
	sal	r8, 4
	xor	eax, eax
	shufps	xmm4, xmm4, 0
	.p2align 4
	.p2align 3
.L3:
	movaps	xmm1, XMMWORD PTR [rsi+rax]
	movaps	xmm5, XMMWORD PTR [rdx+rax]
	movaps	xmm2, xmm1
	addps	xmm1, xmm1
	addps	xmm1, XMMWORD PTR [rdi+rax]
	mulps	xmm2, xmm5
	mulps	xmm5, xmm4
	movaps	xmm3, xmm2
	movaps	xmm0, xmm2
	shufps	xmm3, xmm2, 85
	addss	xmm0, xmm3
	movaps	xmm3, xmm1
	movhlps	xmm2, xmm2
	mulps	xmm3, xmm1
	addss	xmm0, xmm2
	movaps	xmm6, xmm3
	movaps	xmm2, xmm3
	shufps	xmm0, xmm0, 0
	shufps	xmm6, xmm3, 85
	addss	xmm2, xmm6
	movhlps	xmm3, xmm3
	addss	xmm2, xmm3
	movaps	xmm3, xmm1
	shufps	xmm2, xmm2, 0
	sqrtps	xmm2, xmm2
	divps	xmm3, xmm2
	blendps	xmm3, xmm1, 8
	mulps	xmm0, xmm3
	addps	xmm0, xmm5
	movaps	XMMWORD PTR [rcx+rax], xmm0
	add	rax, 16
	cmp	r8, rax
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE2080:
	.size	cg_compound_et, .-cg_compound_et
	.p2align 4
	.globl	cg_compound_manual
	.type	cg_compound_manual, @function
cg_compound_manual:
.LFB2081:
	.cfi_startproc
	endbr64
	test	r8, r8
	je	.L9
	movss	xmm4, DWORD PTR .LC1[rip]
	sal	r8, 4
	xor	eax, eax
	shufps	xmm4, xmm4, 0
	.p2align 4
	.p2align 3
.L11:
	movaps	xmm0, XMMWORD PTR [rsi+rax]
	movaps	xmm5, XMMWORD PTR [rdx+rax]
	movaps	xmm3, xmm0
	addps	xmm3, xmm0
	addps	xmm3, XMMWORD PTR [rdi+rax]
	mulps	xmm0, xmm5
	mulps	xmm5, xmm4
	movaps	xmm2, xmm3
	mulps	xmm2, xmm3
	movaps	xmm6, xmm2
	movaps	xmm1, xmm2
	shufps	xmm6, xmm2, 85
	addss	xmm1, xmm6
	movhlps	xmm2, xmm2
	addss	xmm1, xmm2
	movaps	xmm2, xmm3
	shufps	xmm1, xmm1, 0
	sqrtps	xmm1, xmm1
	divps	xmm2, xmm1
	movaps	xmm1, xmm0
	blendps	xmm2, xmm3, 8
	movaps	xmm3, xmm0
	shufps	xmm3, xmm0, 85
	addss	xmm1, xmm3
	movhlps	xmm0, xmm0
	addss	xmm1, xmm0
	shufps	xmm1, xmm1, 0
	mulps	xmm1, xmm2
	addps	xmm1, xmm5
	movaps	XMMWORD PTR [rcx+rax], xmm1
	add	rax, 16
	cmp	r8, rax
	jne	.L11
.L9:
	ret
	.cfi_endproc
.LFE2081:
	.size	cg_compound_manual, .-cg_compound_manual
	.p2align 4
	.globl	cg_compound_intrin
	.type	cg_compound_intrin, @function
cg_compound_intrin:
.LFB2084:
	.cfi_startproc
	endbr64
	test	r8, r8
	je	.L16
	movss	xmm5, DWORD PTR .LC1[rip]
	sal	r8, 4
	xor	eax, eax
	shufps	xmm5, xmm5, 0
	.p2align 4
	.p2align 3
.L18:
	movaps	xmm3, XMMWORD PTR [rsi+rax]
	movaps	xmm0, XMMWORD PTR [rdx+rax]
	movaps	xmm1, xmm3
	addps	xmm1, xmm3
	addps	xmm1, XMMWORD PTR [rdi+rax]
	dpps	xmm3, xmm0, 127
	mulps	xmm0, xmm5
	movaps	xmm4, xmm1
	movaps	xmm2, xmm1
	dpps	xmm4, xmm1, 127
	sqrtps	xmm4, xmm4
	divps	xmm2, xmm4
	blendps	xmm2, xmm1, 8
	mulps	xmm2, xmm3
	addps	xmm0, xmm2
	movaps	XMMWORD PTR [rcx+rax], xmm0
	add	rax, 16
	cmp	r8, rax
	jne	.L18
.L16:
	ret
	.cfi_endproc
.LFE2084:
	.size	cg_compound_intrin, .-cg_compound_intrin
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC1:
	.long	1077936128
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
