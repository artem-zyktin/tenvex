# g++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_quat.cpp
	.file	"cg_quat.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	cg_hamilton
	.type	cg_hamilton, @function
cg_hamilton:
.LFB2080:
	.cfi_startproc
	endbr64
	test	rcx, rcx
	je	.L1
	movaps	xmm6, XMMWORD PTR .LC0[rip]
	movaps	xmm5, XMMWORD PTR .LC1[rip]
	sal	rcx, 4
	xor	eax, eax
	movaps	xmm4, XMMWORD PTR .LC2[rip]
	.p2align 4
	.p2align 3
.L3:
	movaps	xmm0, XMMWORD PTR [rdi+rax]
	movaps	xmm2, XMMWORD PTR [rsi+rax]
	movaps	xmm7, xmm0
	movaps	xmm1, xmm2
	movaps	xmm3, xmm2
	palignr	xmm3, xmm3, 8
	shufps	xmm7, xmm0, 0
	shufps	xmm1, xmm2, 27
	movaps	xmm8, xmm2
	mulps	xmm7, xmm1
	movaps	xmm1, xmm0
	shufps	xmm8, xmm2, 177
	shufps	xmm1, xmm0, 85
	mulps	xmm1, xmm3
	movaps	xmm3, xmm0
	shufps	xmm3, xmm0, 170
	mulps	xmm3, xmm8
	shufps	xmm0, xmm0, 255
	mulps	xmm0, xmm2
	xorps	xmm7, xmm6
	xorps	xmm1, xmm5
	xorps	xmm3, xmm4
	addps	xmm0, xmm7
	addps	xmm1, xmm3
	addps	xmm0, xmm1
	movaps	XMMWORD PTR [rdx+rax], xmm0
	add	rax, 16
	cmp	rcx, rax
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE2080:
	.size	cg_hamilton, .-cg_hamilton
	.p2align 4
	.globl	cg_rotate
	.type	cg_rotate, @function
cg_rotate:
.LFB2081:
	.cfi_startproc
	endbr64
	test	rcx, rcx
	je	.L9
	sal	rcx, 4
	xor	eax, eax
	.p2align 4
	.p2align 3
.L11:
	movaps	xmm0, XMMWORD PTR [rsi+rax]
	movaps	xmm3, XMMWORD PTR [rdi+rax]
	movaps	xmm1, xmm0
	movaps	xmm2, xmm3
	movaps	xmm4, xmm0
	shufps	xmm1, xmm0, 201
	shufps	xmm2, xmm3, 201
	mulps	xmm1, xmm3
	mulps	xmm2, xmm0
	subps	xmm2, xmm1
	mulps	xmm4, xmm2
	movaps	xmm1, xmm2
	shufps	xmm1, xmm2, 210
	mulps	xmm1, xmm0
	shufps	xmm0, xmm0, 255
	addps	xmm0, xmm0
	shufps	xmm2, xmm2, 201
	mulps	xmm0, xmm2
	shufps	xmm4, xmm4, 201
	subps	xmm1, xmm4
	shufps	xmm1, xmm1, 201
	addps	xmm1, xmm1
	addps	xmm0, xmm1
	addps	xmm0, xmm3
	movaps	XMMWORD PTR [rdx+rax], xmm0
	add	rax, 16
	cmp	rcx, rax
	jne	.L11
.L9:
	ret
	.cfi_endproc
.LFE2081:
	.size	cg_rotate, .-cg_rotate
	.p2align 4
	.globl	cg_conj_scale
	.type	cg_conj_scale, @function
cg_conj_scale:
.LFB2082:
	.cfi_startproc
	endbr64
	test	rdx, rdx
	je	.L16
	movaps	xmm1, XMMWORD PTR .LC3[rip]
	sal	rdx, 4
	xor	eax, eax
	.p2align 5
	.p2align 4
	.p2align 3
.L18:
	movaps	xmm0, XMMWORD PTR [rdi+rax]
	xorps	xmm0, xmm1
	addps	xmm0, xmm0
	movaps	XMMWORD PTR [rsi+rax], xmm0
	add	rax, 16
	cmp	rdx, rax
	jne	.L18
.L16:
	ret
	.cfi_endproc
.LFE2082:
	.size	cg_conj_scale, .-cg_conj_scale
	.p2align 4
	.globl	cg_quat_inverse
	.type	cg_quat_inverse, @function
cg_quat_inverse:
.LFB2083:
	.cfi_startproc
	endbr64
	test	rdx, rdx
	je	.L23
	movaps	xmm2, XMMWORD PTR .LC3[rip]
	sal	rdx, 4
	xor	eax, eax
	.p2align 6
	.p2align 4
	.p2align 3
.L25:
	movaps	xmm1, XMMWORD PTR [rdi+rax]
	movaps	xmm0, xmm1
	mulps	xmm0, xmm1
	xorps	xmm1, xmm2
	haddps	xmm0, xmm0
	haddps	xmm0, xmm0
	divps	xmm1, xmm0
	movaps	XMMWORD PTR [rsi+rax], xmm1
	add	rax, 16
	cmp	rdx, rax
	jne	.L25
.L23:
	ret
	.cfi_endproc
.LFE2083:
	.size	cg_quat_inverse, .-cg_quat_inverse
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	0
	.long	-2147483648
	.long	0
	.long	-2147483648
	.align 16
.LC1:
	.long	0
	.long	0
	.long	-2147483648
	.long	-2147483648
	.align 16
.LC2:
	.long	-2147483648
	.long	0
	.long	0
	.long	-2147483648
	.align 16
.LC3:
	.long	-2147483648
	.long	-2147483648
	.long	-2147483648
	.long	0
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
