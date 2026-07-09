# g++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_reference.cpp
	.file	"cg_reference.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	cg_clean
	.type	cg_clean, @function
cg_clean:
.LFB2081:
	.cfi_startproc
	endbr64
	mulps	xmm0, xmm1
	addps	xmm0, xmm1
	mulps	xmm0, xmm2
	addps	xmm0, xmm2
	ret
	.cfi_endproc
.LFE2081:
	.size	cg_clean, .-cg_clean
	.p2align 4
	.globl	cg_spilled
	.type	cg_spilled, @function
cg_spilled:
.LFB2082:
	.cfi_startproc
	endbr64
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	movaps	XMMWORD PTR [rsp], xmm2
	call	cg_opaque_kernel@PLT
	movaps	xmm1, XMMWORD PTR [rsp]
	add	rsp, 24
	.cfi_def_cfa_offset 8
	jmp	cg_opaque_kernel@PLT
	.cfi_endproc
.LFE2082:
	.size	cg_spilled, .-cg_spilled
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
