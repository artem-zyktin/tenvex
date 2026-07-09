# g++ (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_reductions.cpp
	.file	"cg_reductions.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	cg_dot3
	.type	cg_dot3, @function
cg_dot3:
.LFB2011:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	test	rcx, rcx
	je	.L1
	sal	rcx, 4
	xor	eax, eax
	.p2align 4,,10
	.p2align 3
.L3:
	movaps	xmm0, XMMWORD PTR [rdi+rax]
	mulps	xmm0, XMMWORD PTR [rsi+rax]
	add	rax, 16
	add	rdx, 4
	movaps	xmm2, xmm0
	movaps	xmm1, xmm0
	shufps	xmm2, xmm0, 85
	addss	xmm1, xmm2
	movhlps	xmm0, xmm0
	addss	xmm1, xmm0
	movss	DWORD PTR -4[rdx], xmm1
	cmp	rcx, rax
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE2011:
	.size	cg_dot3, .-cg_dot3
	.p2align 4
	.globl	cg_dot4
	.type	cg_dot4, @function
cg_dot4:
.LFB2012:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	test	rcx, rcx
	je	.L9
	sal	rcx, 4
	xor	eax, eax
	.p2align 4,,10
	.p2align 3
.L11:
	movaps	xmm0, XMMWORD PTR [rdi+rax]
	mulps	xmm0, XMMWORD PTR [rsi+rax]
	add	rax, 16
	add	rdx, 4
	haddps	xmm0, xmm0
	haddps	xmm0, xmm0
	movss	DWORD PTR -4[rdx], xmm0
	cmp	rcx, rax
	jne	.L11
.L9:
	ret
	.cfi_endproc
.LFE2012:
	.size	cg_dot4, .-cg_dot4
	.p2align 4
	.globl	cg_magnitude3
	.type	cg_magnitude3, @function
cg_magnitude3:
.LFB2013:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	test	rdx, rdx
	je	.L16
	sal	rdx, 4
	lea	rax, [rdi+rdx]
	.p2align 4,,10
	.p2align 3
.L18:
	movaps	xmm0, XMMWORD PTR [rdi]
	add	rdi, 16
	add	rsi, 4
	mulps	xmm0, xmm0
	movaps	xmm2, xmm0
	movaps	xmm1, xmm0
	shufps	xmm2, xmm0, 85
	addss	xmm1, xmm2
	movhlps	xmm0, xmm0
	addss	xmm1, xmm0
	shufps	xmm1, xmm1, 0
	sqrtps	xmm1, xmm1
	movss	DWORD PTR -4[rsi], xmm1
	cmp	rdi, rax
	jne	.L18
.L16:
	ret
	.cfi_endproc
.LFE2013:
	.size	cg_magnitude3, .-cg_magnitude3
	.p2align 4
	.globl	cg_magnitude3_sq
	.type	cg_magnitude3_sq, @function
cg_magnitude3_sq:
.LFB2014:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	test	rdx, rdx
	je	.L23
	sal	rdx, 4
	lea	rax, [rdi+rdx]
	.p2align 4,,10
	.p2align 3
.L25:
	movaps	xmm0, XMMWORD PTR [rdi]
	add	rdi, 16
	add	rsi, 4
	mulps	xmm0, xmm0
	movaps	xmm2, xmm0
	movaps	xmm1, xmm0
	shufps	xmm2, xmm0, 85
	addss	xmm1, xmm2
	movhlps	xmm0, xmm0
	addss	xmm1, xmm0
	movss	DWORD PTR -4[rsi], xmm1
	cmp	rdi, rax
	jne	.L25
.L23:
	ret
	.cfi_endproc
.LFE2014:
	.size	cg_magnitude3_sq, .-cg_magnitude3_sq
	.p2align 4
	.globl	cg_mag3_lt_mag3
	.type	cg_mag3_lt_mag3, @function
cg_mag3_lt_mag3:
.LFB2015:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	test	rcx, rcx
	je	.L30
	sal	rcx, 4
	xor	eax, eax
	.p2align 4,,10
	.p2align 3
.L32:
	movaps	xmm0, XMMWORD PTR [rdi+rax]
	mulps	xmm0, xmm0
	movaps	xmm2, xmm0
	movaps	xmm1, xmm0
	shufps	xmm2, xmm0, 85
	addss	xmm1, xmm2
	movhlps	xmm0, xmm0
	addss	xmm1, xmm0
	movaps	xmm0, XMMWORD PTR [rsi+rax]
	mulps	xmm0, xmm0
	movaps	xmm3, xmm0
	movaps	xmm2, xmm0
	shufps	xmm3, xmm0, 85
	addss	xmm2, xmm3
	movhlps	xmm0, xmm0
	addss	xmm2, xmm0
	comiss	xmm2, xmm1
	seta	BYTE PTR [rdx]
	add	rax, 16
	add	rdx, 1
	cmp	rcx, rax
	jne	.L32
.L30:
	ret
	.cfi_endproc
.LFE2015:
	.size	cg_mag3_lt_mag3, .-cg_mag3_lt_mag3
	.p2align 4
	.globl	cg_mag3_lt_scalar
	.type	cg_mag3_lt_scalar, @function
cg_mag3_lt_scalar:
.LFB2016:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	endbr64
	mov	r8, rsi
	test	rdx, rdx
	je	.L37
	pxor	xmm1, xmm1
	comiss	xmm1, xmm0
	ja	.L39
	mulss	xmm0, xmm0
	mov	rax, rdi
	sal	rdx, 4
	mov	rdi, rsi
	add	rdx, rax
	.p2align 4,,10
	.p2align 3
.L40:
	movaps	xmm1, XMMWORD PTR [rax]
	mulps	xmm1, xmm1
	movaps	xmm3, xmm1
	movaps	xmm2, xmm1
	shufps	xmm3, xmm1, 85
	addss	xmm2, xmm3
	movhlps	xmm1, xmm1
	addss	xmm2, xmm1
	comiss	xmm0, xmm2
	seta	BYTE PTR [rdi]
	add	rax, 16
	add	rdi, 1
	cmp	rdx, rax
	jne	.L40
	ret
	.p2align 4,,10
	.p2align 3
.L37:
	ret
	.p2align 4,,10
	.p2align 3
.L39:
	xor	esi, esi
	mov	rdi, r8
	jmp	memset@PLT
	.cfi_endproc
.LFE2016:
	.size	cg_mag3_lt_scalar, .-cg_mag3_lt_scalar
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
