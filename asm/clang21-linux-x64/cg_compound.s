# Ubuntu clang version 21.1.8 (6ubuntu1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_compound.cpp
	.intel_syntax noprefix
	.file	"cg_compound.cpp"
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          # -- Begin function cg_compound_et
.LCPI0_0:
	.long	0x40400000                      # float 3
	.long	0x40400000                      # float 3
	.long	0x40400000                      # float 3
	.long	0x40400000                      # float 3
	.text
	.globl	cg_compound_et
	.p2align	4
	.type	cg_compound_et,@function
cg_compound_et:                         # @cg_compound_et
	.cfi_startproc
# %bb.0:
	test	r8, r8
	je	.LBB0_3
# %bb.1:
	xor	eax, eax
	movaps	xmm0, xmmword ptr [rip + .LCPI0_0] # xmm0 = [3.0E+0,3.0E+0,3.0E+0,3.0E+0]
	.p2align	4
.LBB0_2:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm2, xmmword ptr [rsi + rax]
	movaps	xmm1, xmmword ptr [rdx + rax]
	movaps	xmm3, xmm2
	addps	xmm3, xmm2
	addps	xmm3, xmmword ptr [rdi + rax]
	movaps	xmm4, xmm3
	mulps	xmm4, xmm3
	movshdup	xmm5, xmm4                      # xmm5 = xmm4[1,1,3,3]
	addss	xmm5, xmm4
	movhlps	xmm4, xmm4                      # xmm4 = xmm4[1,1]
	addss	xmm4, xmm5
	sqrtss	xmm4, xmm4
	shufps	xmm4, xmm4, 0                   # xmm4 = xmm4[0,0,0,0]
	movaps	xmm5, xmm3
	divps	xmm5, xmm4
	blendps	xmm5, xmm3, 8                   # xmm5 = xmm5[0,1,2],xmm3[3]
	mulps	xmm2, xmm1
	movshdup	xmm3, xmm2                      # xmm3 = xmm2[1,1,3,3]
	addss	xmm3, xmm2
	shufps	xmm2, xmm2, 170                 # xmm2 = xmm2[2,2,2,2]
	shufps	xmm3, xmm3, 0                   # xmm3 = xmm3[0,0,0,0]
	addps	xmm3, xmm2
	mulps	xmm3, xmm5
	mulps	xmm1, xmm0
	addps	xmm1, xmm3
	movaps	xmmword ptr [rcx + rax], xmm1
	add	rax, 16
	dec	r8
	jne	.LBB0_2
.LBB0_3:
	ret
.Lfunc_end0:
	.size	cg_compound_et, .Lfunc_end0-cg_compound_et
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          # -- Begin function cg_compound_value
.LCPI1_0:
	.long	0x40400000                      # float 3
	.long	0x40400000                      # float 3
	.long	0x40400000                      # float 3
	.long	0x40400000                      # float 3
	.text
	.globl	cg_compound_value
	.p2align	4
	.type	cg_compound_value,@function
cg_compound_value:                      # @cg_compound_value
	.cfi_startproc
# %bb.0:
	movaps	xmm1, xmmword ptr [rsi]
	movaps	xmm2, xmm1
	addps	xmm2, xmm1
	addps	xmm2, xmmword ptr [rdi]
	movaps	xmm0, xmmword ptr [rdx]
	movaps	xmm3, xmm2
	mulps	xmm3, xmm2
	movshdup	xmm4, xmm3                      # xmm4 = xmm3[1,1,3,3]
	addss	xmm4, xmm3
	movhlps	xmm3, xmm3                      # xmm3 = xmm3[1,1]
	addss	xmm3, xmm4
	sqrtss	xmm3, xmm3
	shufps	xmm3, xmm3, 0                   # xmm3 = xmm3[0,0,0,0]
	movaps	xmm4, xmm2
	divps	xmm4, xmm3
	blendps	xmm4, xmm2, 8                   # xmm4 = xmm4[0,1,2],xmm2[3]
	mulps	xmm1, xmm0
	movshdup	xmm2, xmm1                      # xmm2 = xmm1[1,1,3,3]
	addss	xmm2, xmm1
	shufps	xmm1, xmm1, 170                 # xmm1 = xmm1[2,2,2,2]
	shufps	xmm2, xmm2, 0                   # xmm2 = xmm2[0,0,0,0]
	addps	xmm2, xmm1
	mulps	xmm2, xmm4
	mulps	xmm0, xmmword ptr [rip + .LCPI1_0]
	addps	xmm0, xmm2
	ret
.Lfunc_end1:
	.size	cg_compound_value, .Lfunc_end1-cg_compound_value
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          # -- Begin function cg_compound_manual
.LCPI2_0:
	.long	0x40400000                      # float 3
	.long	0x40400000                      # float 3
	.long	0x40400000                      # float 3
	.long	0x40400000                      # float 3
	.text
	.globl	cg_compound_manual
	.p2align	4
	.type	cg_compound_manual,@function
cg_compound_manual:                     # @cg_compound_manual
	.cfi_startproc
# %bb.0:
	test	r8, r8
	je	.LBB2_3
# %bb.1:
	xor	eax, eax
	movaps	xmm0, xmmword ptr [rip + .LCPI2_0] # xmm0 = [3.0E+0,3.0E+0,3.0E+0,3.0E+0]
	.p2align	4
.LBB2_2:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm2, xmmword ptr [rsi + rax]
	movaps	xmm1, xmmword ptr [rdx + rax]
	movaps	xmm3, xmm2
	addps	xmm3, xmm2
	addps	xmm3, xmmword ptr [rdi + rax]
	movaps	xmm4, xmm3
	mulps	xmm4, xmm3
	movshdup	xmm5, xmm4                      # xmm5 = xmm4[1,1,3,3]
	addss	xmm5, xmm4
	movhlps	xmm4, xmm4                      # xmm4 = xmm4[1,1]
	addss	xmm4, xmm5
	sqrtss	xmm4, xmm4
	shufps	xmm4, xmm4, 0                   # xmm4 = xmm4[0,0,0,0]
	movaps	xmm5, xmm3
	divps	xmm5, xmm4
	blendps	xmm5, xmm3, 8                   # xmm5 = xmm5[0,1,2],xmm3[3]
	mulps	xmm2, xmm1
	movshdup	xmm3, xmm2                      # xmm3 = xmm2[1,1,3,3]
	addss	xmm3, xmm2
	shufps	xmm2, xmm2, 170                 # xmm2 = xmm2[2,2,2,2]
	shufps	xmm3, xmm3, 0                   # xmm3 = xmm3[0,0,0,0]
	addps	xmm3, xmm2
	mulps	xmm3, xmm5
	mulps	xmm1, xmm0
	addps	xmm1, xmm3
	movaps	xmmword ptr [rcx + rax], xmm1
	add	rax, 16
	dec	r8
	jne	.LBB2_2
.LBB2_3:
	ret
.Lfunc_end2:
	.size	cg_compound_manual, .Lfunc_end2-cg_compound_manual
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          # -- Begin function cg_compound_intrin
.LCPI3_0:
	.long	0x40400000                      # float 3
	.long	0x40400000                      # float 3
	.long	0x40400000                      # float 3
	.long	0x40400000                      # float 3
	.text
	.globl	cg_compound_intrin
	.p2align	4
	.type	cg_compound_intrin,@function
cg_compound_intrin:                     # @cg_compound_intrin
	.cfi_startproc
# %bb.0:
	test	r8, r8
	je	.LBB3_3
# %bb.1:
	xor	eax, eax
	movaps	xmm0, xmmword ptr [rip + .LCPI3_0] # xmm0 = [3.0E+0,3.0E+0,3.0E+0,3.0E+0]
	.p2align	4
.LBB3_2:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm1, xmmword ptr [rsi + rax]
	movaps	xmm2, xmm1
	addps	xmm2, xmm1
	addps	xmm2, xmmword ptr [rdi + rax]
	movaps	xmm3, xmm2
	dpps	xmm3, xmm2, 127
	movaps	xmm4, xmmword ptr [rdx + rax]
	sqrtps	xmm3, xmm3
	movaps	xmm5, xmm2
	dpps	xmm1, xmm4, 127
	divps	xmm5, xmm3
	blendps	xmm5, xmm2, 8                   # xmm5 = xmm5[0,1,2],xmm2[3]
	mulps	xmm1, xmm5
	mulps	xmm4, xmm0
	addps	xmm4, xmm1
	movaps	xmmword ptr [rcx + rax], xmm4
	add	rax, 16
	dec	r8
	jne	.LBB3_2
.LBB3_3:
	ret
.Lfunc_end3:
	.size	cg_compound_intrin, .Lfunc_end3-cg_compound_intrin
	.cfi_endproc
                                        # -- End function
	.ident	"Ubuntu clang version 21.1.8 (6ubuntu1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_compound_et
	.addrsig_sym cg_compound_value
	.addrsig_sym cg_compound_manual
	.addrsig_sym cg_compound_intrin
	.addrsig_sym __gxx_personality_v0
