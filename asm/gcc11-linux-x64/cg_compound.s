# g++ (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_compound.cpp
	.file	"cg_compound.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	cg_compound_et
	.type	cg_compound_et, @function
cg_compound_et:
.LFB2011:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	test	r8, r8
	je	.L1
	movaps	xmm4, XMMWORD PTR .LC0[rip]
	sal	r8, 4
	xor	eax, eax
	.p2align 4,,10
	.p2align 3
.L3:
	movaps	xmm0, XMMWORD PTR [rsi+rax]
	movaps	xmm2, XMMWORD PTR [rdx+rax]
	mulps	xmm2, xmm0
	addps	xmm0, xmm0
	addps	xmm0, XMMWORD PTR [rdi+rax]
	movaps	xmm3, xmm2
	movaps	xmm1, xmm2
	shufps	xmm3, xmm2, 85
	addss	xmm1, xmm3
	movaps	xmm3, xmm0
	movhlps	xmm2, xmm2
	mulps	xmm3, xmm0
	addss	xmm1, xmm2
	movaps	xmm5, xmm3
	movaps	xmm2, xmm3
	shufps	xmm1, xmm1, 0
	shufps	xmm5, xmm3, 85
	addss	xmm2, xmm5
	movhlps	xmm3, xmm3
	addss	xmm2, xmm3
	movaps	xmm3, xmm0
	shufps	xmm2, xmm2, 0
	sqrtps	xmm2, xmm2
	divps	xmm3, xmm2
	blendps	xmm3, xmm0, 8
	movaps	xmm0, XMMWORD PTR [rdx+rax]
	mulps	xmm1, xmm3
	mulps	xmm0, xmm4
	addps	xmm0, xmm1
	movaps	XMMWORD PTR [rcx+rax], xmm0
	add	rax, 16
	cmp	r8, rax
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE2011:
	.size	cg_compound_et, .-cg_compound_et
	.p2align 4
	.globl	cg_compound_value
	.type	cg_compound_value, @function
cg_compound_value:
.LFB2017:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	movaps	xmm1, XMMWORD PTR [rsi]
	movaps	xmm0, XMMWORD PTR [rdx]
	movaps	xmm3, xmm1
	addps	xmm1, xmm1
	addps	xmm1, XMMWORD PTR [rdi]
	mulps	xmm3, xmm0
	mulps	xmm0, XMMWORD PTR .LC0[rip]
	movaps	xmm4, xmm3
	movaps	xmm2, xmm3
	shufps	xmm4, xmm3, 85
	addss	xmm2, xmm4
	movaps	xmm4, xmm1
	movhlps	xmm3, xmm3
	mulps	xmm4, xmm1
	addss	xmm2, xmm3
	movaps	xmm5, xmm4
	movaps	xmm3, xmm4
	shufps	xmm2, xmm2, 0
	shufps	xmm5, xmm4, 85
	addss	xmm3, xmm5
	movhlps	xmm4, xmm4
	addss	xmm3, xmm4
	movaps	xmm4, xmm1
	shufps	xmm3, xmm3, 0
	sqrtps	xmm3, xmm3
	divps	xmm4, xmm3
	blendps	xmm4, xmm1, 8
	mulps	xmm2, xmm4
	addps	xmm0, xmm2
	ret
	.cfi_endproc
.LFE2017:
	.size	cg_compound_value, .-cg_compound_value
	.p2align 4
	.globl	cg_compound_manual
	.type	cg_compound_manual, @function
cg_compound_manual:
.LFB2018:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	test	r8, r8
	je	.L10
	movaps	xmm3, XMMWORD PTR .LC0[rip]
	sal	r8, 4
	xor	eax, eax
	.p2align 4,,10
	.p2align 3
.L12:
	movaps	xmm0, XMMWORD PTR [rsi+rax]
	movaps	xmm4, xmm0
	addps	xmm4, xmm0
	addps	xmm4, XMMWORD PTR [rdi+rax]
	mulps	xmm0, XMMWORD PTR [rdx+rax]
	movaps	xmm2, xmm4
	mulps	xmm2, xmm4
	movaps	xmm5, xmm2
	movaps	xmm1, xmm2
	shufps	xmm5, xmm2, 85
	addss	xmm1, xmm5
	movhlps	xmm2, xmm2
	addss	xmm1, xmm2
	movaps	xmm2, xmm4
	shufps	xmm1, xmm1, 0
	sqrtps	xmm1, xmm1
	divps	xmm2, xmm1
	movaps	xmm1, xmm0
	blendps	xmm2, xmm4, 8
	movaps	xmm4, xmm0
	shufps	xmm4, xmm0, 85
	addss	xmm1, xmm4
	movhlps	xmm0, xmm0
	addss	xmm1, xmm0
	movaps	xmm0, XMMWORD PTR [rdx+rax]
	mulps	xmm0, xmm3
	shufps	xmm1, xmm1, 0
	mulps	xmm1, xmm2
	addps	xmm0, xmm1
	movaps	XMMWORD PTR [rcx+rax], xmm0
	add	rax, 16
	cmp	r8, rax
	jne	.L12
.L10:
	ret
	.cfi_endproc
.LFE2018:
	.size	cg_compound_manual, .-cg_compound_manual
	.p2align 4
	.globl	cg_compound_intrin
	.type	cg_compound_intrin, @function
cg_compound_intrin:
.LFB2021:
	.cfi_startproc
	endbr64
	test	r8, r8
	je	.L17
	movaps	xmm4, XMMWORD PTR .LC0[rip]
	xor	eax, eax
	xor	r9d, r9d
	.p2align 4,,10
	.p2align 3
.L19:
	movaps	xmm2, XMMWORD PTR [rsi+rax]
	add	r9, 1
	movaps	xmm0, xmm2
	addps	xmm0, xmm2
	addps	xmm0, XMMWORD PTR [rdi+rax]
	dpps	xmm2, XMMWORD PTR [rdx+rax], 127
	movaps	xmm3, xmm0
	movaps	xmm1, xmm0
	dpps	xmm3, xmm0, 127
	sqrtps	xmm3, xmm3
	divps	xmm1, xmm3
	blendps	xmm1, xmm0, 8
	movaps	xmm0, XMMWORD PTR [rdx+rax]
	mulps	xmm1, xmm2
	mulps	xmm0, xmm4
	addps	xmm0, xmm1
	movaps	XMMWORD PTR [rcx+rax], xmm0
	add	rax, 16
	cmp	r8, r9
	jne	.L19
.L17:
	ret
	.cfi_endproc
.LFE2021:
	.size	cg_compound_intrin, .-cg_compound_intrin
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	1077936128
	.long	1077936128
	.long	1077936128
	.long	1077936128
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
