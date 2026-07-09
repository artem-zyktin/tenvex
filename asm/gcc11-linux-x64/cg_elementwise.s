# g++ (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_elementwise.cpp
	.file	"cg_elementwise.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	cg_aabb
	.type	cg_aabb, @function
cg_aabb:
.LFB2011:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	movaps	xmm0, XMMWORD PTR [rdi]
	cmp	rsi, 1
	jbe	.L4
	sal	rsi, 4
	lea	rax, 16[rdi]
	movaps	xmm1, xmm0
	add	rdi, rsi
	.p2align 4,,10
	.p2align 3
.L3:
	minps	xmm0, XMMWORD PTR [rax]
	maxps	xmm1, XMMWORD PTR [rax]
	add	rax, 16
	cmp	rax, rdi
	jne	.L3
	movaps	XMMWORD PTR [rdx], xmm0
	movaps	XMMWORD PTR [rcx], xmm1
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	movaps	xmm1, xmm0
	movaps	XMMWORD PTR [rdx], xmm0
	movaps	XMMWORD PTR [rcx], xmm1
	ret
	.cfi_endproc
.LFE2011:
	.size	cg_aabb, .-cg_aabb
	.p2align 4
	.globl	cg_saturate
	.type	cg_saturate, @function
cg_saturate:
.LFB2012:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	test	rdx, rdx
	je	.L7
	movaps	xmm2, XMMWORD PTR .LC0[rip]
	sal	rdx, 4
	xor	eax, eax
	pxor	xmm1, xmm1
	.p2align 4,,10
	.p2align 3
.L9:
	movaps	xmm0, XMMWORD PTR [rdi+rax]
	maxps	xmm0, xmm1
	minps	xmm0, xmm2
	movaps	XMMWORD PTR [rsi+rax], xmm0
	add	rax, 16
	cmp	rdx, rax
	jne	.L9
.L7:
	ret
	.cfi_endproc
.LFE2012:
	.size	cg_saturate, .-cg_saturate
	.p2align 4
	.globl	cg_with_w_expr
	.type	cg_with_w_expr, @function
cg_with_w_expr:
.LFB2013:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	test	rcx, rcx
	je	.L14
	sal	rcx, 4
	xor	eax, eax
	.p2align 4,,10
	.p2align 3
.L16:
	movaps	xmm0, XMMWORD PTR [rdi+rax]
	addps	xmm0, XMMWORD PTR [rsi+rax]
	blendps	xmm0, XMMWORD PTR [rdi+rax], 8
	movaps	XMMWORD PTR [rdx+rax], xmm0
	add	rax, 16
	cmp	rcx, rax
	jne	.L16
.L14:
	ret
	.cfi_endproc
.LFE2013:
	.size	cg_with_w_expr, .-cg_with_w_expr
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	1065353216
	.long	1065353216
	.long	1065353216
	.long	1065353216
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
