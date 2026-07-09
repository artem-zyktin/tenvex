# g++ (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_reference.cpp
	.file	"cg_reference.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	cg_clean
	.type	cg_clean, @function
cg_clean:
.LFB2012:
	.cfi_startproc
	endbr64
	mulps	xmm0, xmm1
	addps	xmm0, xmm1
	mulps	xmm0, xmm2
	addps	xmm0, xmm2
	ret
	.cfi_endproc
.LFE2012:
	.size	cg_clean, .-cg_clean
	.p2align 4
	.globl	cg_spilled
	.type	cg_spilled, @function
cg_spilled:
.LFB2013:
	.cfi_startproc
	endbr64
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	movaps	XMMWORD PTR [rsp], xmm2
	call	cg_opaque_kernel@PLT
	movaps	xmm2, XMMWORD PTR [rsp]
	add	rsp, 24
	.cfi_def_cfa_offset 8
	movaps	xmm1, xmm2
	jmp	cg_opaque_kernel@PLT
	.cfi_endproc
.LFE2013:
	.size	cg_spilled, .-cg_spilled
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
