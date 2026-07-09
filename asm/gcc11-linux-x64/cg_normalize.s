# g++ (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_normalize.cpp
	.file	"cg_normalize.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	cg_normalize3
	.type	cg_normalize3, @function
cg_normalize3:
.LFB2011:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	test	rdx, rdx
	je	.L1
	sal	rdx, 4
	xor	eax, eax
	.p2align 4,,10
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
.LFE2011:
	.size	cg_normalize3, .-cg_normalize3
	.p2align 4
	.globl	cg_normalize3_fast
	.type	cg_normalize3_fast, @function
cg_normalize3_fast:
.LFB2012:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	test	rdx, rdx
	je	.L9
	movaps	xmm5, XMMWORD PTR .LC0[rip]
	movaps	xmm4, XMMWORD PTR .LC1[rip]
	sal	rdx, 4
	xor	eax, eax
	.p2align 4,,10
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
.LFE2012:
	.size	cg_normalize3_fast, .-cg_normalize3_fast
	.p2align 4
	.globl	cg_normalize4
	.type	cg_normalize4, @function
cg_normalize4:
.LFB2013:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	test	rdx, rdx
	je	.L16
	sal	rdx, 4
	xor	eax, eax
	.p2align 4,,10
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
.LFE2013:
	.size	cg_normalize4, .-cg_normalize4
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	1056964608
	.long	1056964608
	.long	1056964608
	.long	1056964608
	.align 16
.LC1:
	.long	1069547520
	.long	1069547520
	.long	1069547520
	.long	1069547520
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0"
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
