# Ubuntu clang version 21.1.8 (6ubuntu1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_quat.cpp
	.intel_syntax noprefix
	.file	"cg_quat.cpp"
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          # -- Begin function cg_hamilton
.LCPI0_0:
	.long	0                               # 0x0
	.long	2147483648                      # 0x80000000
	.long	0                               # 0x0
	.long	2147483648                      # 0x80000000
.LCPI0_1:
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	2147483648                      # 0x80000000
	.long	2147483648                      # 0x80000000
.LCPI0_2:
	.long	2147483648                      # 0x80000000
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	2147483648                      # 0x80000000
	.text
	.globl	cg_hamilton
	.p2align	4
	.type	cg_hamilton,@function
cg_hamilton:                            # @cg_hamilton
	.cfi_startproc
# %bb.0:
	test	rcx, rcx
	je	.LBB0_3
# %bb.1:
	xor	eax, eax
	movaps	xmm0, xmmword ptr [rip + .LCPI0_0] # xmm0 = [0,2147483648,0,2147483648]
	movaps	xmm1, xmmword ptr [rip + .LCPI0_1] # xmm1 = [0,0,2147483648,2147483648]
	movaps	xmm2, xmmword ptr [rip + .LCPI0_2] # xmm2 = [2147483648,0,0,2147483648]
	.p2align	4
.LBB0_2:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm5, xmmword ptr [rdi + rax]
	movaps	xmm4, xmmword ptr [rsi + rax]
	movaps	xmm3, xmm5
	shufps	xmm3, xmm5, 255                 # xmm3 = xmm3[3,3],xmm5[3,3]
	movaps	xmm6, xmm5
	shufps	xmm6, xmm5, 0                   # xmm6 = xmm6[0,0],xmm5[0,0]
	movaps	xmm7, xmm5
	shufps	xmm7, xmm5, 85                  # xmm7 = xmm7[1,1],xmm5[1,1]
	shufps	xmm5, xmm5, 170                 # xmm5 = xmm5[2,2,2,2]
	movaps	xmm8, xmm4
	shufps	xmm8, xmm4, 27                  # xmm8 = xmm8[3,2],xmm4[1,0]
	mulps	xmm8, xmm6
	xorps	xmm8, xmm0
	movaps	xmm6, xmm4
	shufps	xmm6, xmm4, 78                  # xmm6 = xmm6[2,3],xmm4[0,1]
	mulps	xmm6, xmm7
	xorps	xmm6, xmm1
	mulps	xmm3, xmm4
	shufps	xmm4, xmm4, 177                 # xmm4 = xmm4[1,0,3,2]
	mulps	xmm4, xmm5
	xorps	xmm4, xmm2
	addps	xmm4, xmm6
	addps	xmm3, xmm8
	addps	xmm3, xmm4
	movaps	xmmword ptr [rdx + rax], xmm3
	add	rax, 16
	dec	rcx
	jne	.LBB0_2
.LBB0_3:
	ret
.Lfunc_end0:
	.size	cg_hamilton, .Lfunc_end0-cg_hamilton
	.cfi_endproc
                                        # -- End function
	.globl	cg_rotate                       # -- Begin function cg_rotate
	.p2align	4
	.type	cg_rotate,@function
cg_rotate:                              # @cg_rotate
	.cfi_startproc
# %bb.0:
	test	rcx, rcx
	je	.LBB1_3
# %bb.1:
	xor	eax, eax
	.p2align	4
.LBB1_2:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [rdi + rax]
	movaps	xmm1, xmmword ptr [rsi + rax]
	movaps	xmm2, xmm1
	shufps	xmm2, xmm1, 201                 # xmm2 = xmm2[1,2],xmm1[0,3]
	movaps	xmm3, xmm0
	shufps	xmm3, xmm0, 201                 # xmm3 = xmm3[1,2],xmm0[0,3]
	mulps	xmm3, xmm1
	movaps	xmm4, xmm0
	mulps	xmm4, xmm2
	subps	xmm3, xmm4
	movaps	xmm4, xmm3
	shufps	xmm4, xmm3, 201                 # xmm4 = xmm4[1,2],xmm3[0,3]
	shufps	xmm3, xmm3, 210                 # xmm3 = xmm3[2,0,1,3]
	mulps	xmm3, xmm1
	mulps	xmm2, xmm4
	subps	xmm3, xmm2
	addps	xmm1, xmm1
	shufps	xmm1, xmm1, 255                 # xmm1 = xmm1[3,3,3,3]
	mulps	xmm1, xmm4
	addps	xmm3, xmm3
	shufps	xmm3, xmm3, 201                 # xmm3 = xmm3[1,2,0,3]
	addps	xmm3, xmm1
	addps	xmm3, xmm0
	movaps	xmmword ptr [rdx + rax], xmm3
	add	rax, 16
	dec	rcx
	jne	.LBB1_2
.LBB1_3:
	ret
.Lfunc_end1:
	.size	cg_rotate, .Lfunc_end1-cg_rotate
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          # -- Begin function cg_conj_scale
.LCPI2_0:
	.long	2147483648                      # 0x80000000
	.long	2147483648                      # 0x80000000
	.long	2147483648                      # 0x80000000
	.long	0                               # 0x0
	.text
	.globl	cg_conj_scale
	.p2align	4
	.type	cg_conj_scale,@function
cg_conj_scale:                          # @cg_conj_scale
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
	movaps	xmm0, xmmword ptr [rip + .LCPI2_0] # xmm0 = [2147483648,2147483648,2147483648,0]
	.p2align	4
.LBB2_7:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm1, xmmword ptr [rdi + r8 - 16]
	xorps	xmm1, xmm0
	addps	xmm1, xmm1
	movaps	xmmword ptr [rsi + r8 - 16], xmm1
	movaps	xmm1, xmmword ptr [rdi + r8]
	xorps	xmm1, xmm0
	addps	xmm1, xmm1
	movaps	xmmword ptr [rsi + r8], xmm1
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
	xorps	xmm0, xmmword ptr [rip + .LCPI2_0]
	addps	xmm0, xmm0
	movaps	xmmword ptr [rsi + rax], xmm0
.LBB2_5:
	ret
.Lfunc_end2:
	.size	cg_conj_scale, .Lfunc_end2-cg_conj_scale
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          # -- Begin function cg_quat_inverse
.LCPI3_0:
	.long	2147483648                      # 0x80000000
	.long	2147483648                      # 0x80000000
	.long	2147483648                      # 0x80000000
	.long	0                               # 0x0
	.text
	.globl	cg_quat_inverse
	.p2align	4
	.type	cg_quat_inverse,@function
cg_quat_inverse:                        # @cg_quat_inverse
	.cfi_startproc
# %bb.0:
	test	rdx, rdx
	je	.LBB3_5
# %bb.1:
	cmp	rdx, 1
	jne	.LBB3_6
# %bb.2:
	xor	eax, eax
	jmp	.LBB3_3
.LBB3_6:
	mov	rcx, rdx
	and	rcx, -2
	mov	r8d, 16
	xor	eax, eax
	movaps	xmm0, xmmword ptr [rip + .LCPI3_0] # xmm0 = [2147483648,2147483648,2147483648,0]
	.p2align	4
.LBB3_7:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm1, xmmword ptr [rdi + r8 - 16]
	movaps	xmm2, xmm1
	xorps	xmm2, xmm0
	mulps	xmm1, xmm1
	haddps	xmm1, xmm1
	haddps	xmm1, xmm1
	divps	xmm2, xmm1
	movaps	xmmword ptr [rsi + r8 - 16], xmm2
	movaps	xmm1, xmmword ptr [rdi + r8]
	movaps	xmm2, xmm1
	xorps	xmm2, xmm0
	mulps	xmm1, xmm1
	haddps	xmm1, xmm1
	haddps	xmm1, xmm1
	divps	xmm2, xmm1
	movaps	xmmword ptr [rsi + r8], xmm2
	add	rax, 2
	add	r8, 32
	cmp	rcx, rax
	jne	.LBB3_7
.LBB3_3:
	test	dl, 1
	je	.LBB3_5
# %bb.4:
	shl	rax, 4
	movaps	xmm0, xmmword ptr [rdi + rax]
	movaps	xmm1, xmmword ptr [rip + .LCPI3_0] # xmm1 = [2147483648,2147483648,2147483648,0]
	xorps	xmm1, xmm0
	mulps	xmm0, xmm0
	haddps	xmm0, xmm0
	haddps	xmm0, xmm0
	divps	xmm1, xmm0
	movaps	xmmword ptr [rsi + rax], xmm1
.LBB3_5:
	ret
.Lfunc_end3:
	.size	cg_quat_inverse, .Lfunc_end3-cg_quat_inverse
	.cfi_endproc
                                        # -- End function
	.ident	"Ubuntu clang version 21.1.8 (6ubuntu1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_hamilton
	.addrsig_sym cg_rotate
	.addrsig_sym cg_conj_scale
	.addrsig_sym cg_quat_inverse
	.addrsig_sym __gxx_personality_v0
