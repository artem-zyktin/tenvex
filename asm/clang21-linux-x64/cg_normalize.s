# Ubuntu clang version 21.1.8 (6ubuntu1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_normalize.cpp
	.intel_syntax noprefix
	.file	"cg_normalize.cpp"
	.text
	.globl	cg_normalize3                   # -- Begin function cg_normalize3
	.p2align	4
	.type	cg_normalize3,@function
cg_normalize3:                          # @cg_normalize3
	.cfi_startproc
# %bb.0:
	test	rdx, rdx
	je	.LBB0_3
# %bb.1:
	xor	eax, eax
	.p2align	4
.LBB0_2:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [rdi + rax]
	movaps	xmm1, xmm0
	mulps	xmm1, xmm0
	movshdup	xmm2, xmm1                      # xmm2 = xmm1[1,1,3,3]
	addss	xmm2, xmm1
	movhlps	xmm1, xmm1                      # xmm1 = xmm1[1,1]
	addss	xmm1, xmm2
	sqrtss	xmm1, xmm1
	shufps	xmm1, xmm1, 0                   # xmm1 = xmm1[0,0,0,0]
	movaps	xmm2, xmm0
	divps	xmm2, xmm1
	blendps	xmm2, xmm0, 8                   # xmm2 = xmm2[0,1,2],xmm0[3]
	movaps	xmmword ptr [rsi + rax], xmm2
	add	rax, 16
	dec	rdx
	jne	.LBB0_2
.LBB0_3:
	ret
.Lfunc_end0:
	.size	cg_normalize3, .Lfunc_end0-cg_normalize3
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          # -- Begin function cg_normalize3_fast
.LCPI1_0:
	.long	0xbf000000                      # float -0.5
	.long	0xbf000000                      # float -0.5
	.long	0xbf000000                      # float -0.5
	.zero	4
.LCPI1_1:
	.long	0x3fc00000                      # float 1.5
	.long	0x3fc00000                      # float 1.5
	.long	0x3fc00000                      # float 1.5
	.zero	4
	.text
	.globl	cg_normalize3_fast
	.p2align	4
	.type	cg_normalize3_fast,@function
cg_normalize3_fast:                     # @cg_normalize3_fast
	.cfi_startproc
# %bb.0:
	test	rdx, rdx
	je	.LBB1_3
# %bb.1:
	xor	eax, eax
	movaps	xmm0, xmmword ptr [rip + .LCPI1_0] # xmm0 = [-5.0E-1,-5.0E-1,-5.0E-1,u]
	movaps	xmm1, xmmword ptr [rip + .LCPI1_1] # xmm1 = [1.5E+0,1.5E+0,1.5E+0,u]
	.p2align	4
.LBB1_2:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm2, xmmword ptr [rdi + rax]
	movaps	xmm3, xmm2
	mulps	xmm3, xmm2
	movshdup	xmm4, xmm3                      # xmm4 = xmm3[1,1,3,3]
	addss	xmm4, xmm3
	shufps	xmm3, xmm3, 170                 # xmm3 = xmm3[2,2,2,2]
	shufps	xmm4, xmm4, 0                   # xmm4 = xmm4[0,0,0,0]
	addps	xmm4, xmm3
	rsqrtps	xmm3, xmm4
	movaps	xmm5, xmm3
	mulps	xmm5, xmm3
	mulps	xmm4, xmm0
	mulps	xmm4, xmm5
	addps	xmm4, xmm1
	mulps	xmm4, xmm3
	mulps	xmm4, xmm2
	blendps	xmm4, xmm2, 8                   # xmm4 = xmm4[0,1,2],xmm2[3]
	movaps	xmmword ptr [rsi + rax], xmm4
	add	rax, 16
	dec	rdx
	jne	.LBB1_2
.LBB1_3:
	ret
.Lfunc_end1:
	.size	cg_normalize3_fast, .Lfunc_end1-cg_normalize3_fast
	.cfi_endproc
                                        # -- End function
	.globl	cg_normalize4                   # -- Begin function cg_normalize4
	.p2align	4
	.type	cg_normalize4,@function
cg_normalize4:                          # @cg_normalize4
	.cfi_startproc
# %bb.0:
	test	rdx, rdx
	je	.LBB2_5
# %bb.1:
	cmp	rdx, 1
	jne	.LBB2_6
# %bb.2:
	xor	eax, eax
	jmp	.LBB2_3
.LBB2_6:
	mov	rcx, rdx
	and	rcx, -2
	mov	r8d, 16
	xor	eax, eax
	.p2align	4
.LBB2_7:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [rdi + r8 - 16]
	movaps	xmm1, xmm0
	mulps	xmm1, xmm0
	haddps	xmm1, xmm1
	haddps	xmm1, xmm1
	sqrtps	xmm1, xmm1
	divps	xmm0, xmm1
	movaps	xmmword ptr [rsi + r8 - 16], xmm0
	movaps	xmm0, xmmword ptr [rdi + r8]
	movaps	xmm1, xmm0
	mulps	xmm1, xmm0
	haddps	xmm1, xmm1
	haddps	xmm1, xmm1
	sqrtps	xmm1, xmm1
	divps	xmm0, xmm1
	movaps	xmmword ptr [rsi + r8], xmm0
	add	rax, 2
	add	r8, 32
	cmp	rcx, rax
	jne	.LBB2_7
.LBB2_3:
	test	dl, 1
	je	.LBB2_5
# %bb.4:
	shl	rax, 4
	movaps	xmm0, xmmword ptr [rdi + rax]
	movaps	xmm1, xmm0
	mulps	xmm1, xmm0
	haddps	xmm1, xmm1
	haddps	xmm1, xmm1
	sqrtps	xmm1, xmm1
	divps	xmm0, xmm1
	movaps	xmmword ptr [rsi + rax], xmm0
.LBB2_5:
	ret
.Lfunc_end2:
	.size	cg_normalize4, .Lfunc_end2-cg_normalize4
	.cfi_endproc
                                        # -- End function
	.ident	"Ubuntu clang version 21.1.8 (6ubuntu1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_normalize3
	.addrsig_sym cg_normalize3_fast
	.addrsig_sym cg_normalize4
	.addrsig_sym __gxx_personality_v0
