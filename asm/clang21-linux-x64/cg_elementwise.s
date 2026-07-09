# Ubuntu clang version 21.1.8 (6ubuntu1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_elementwise.cpp
	.intel_syntax noprefix
	.file	"cg_elementwise.cpp"
	.text
	.globl	cg_aabb                         # -- Begin function cg_aabb
	.p2align	4
	.type	cg_aabb,@function
cg_aabb:                                # @cg_aabb
	.cfi_startproc
# %bb.0:
	movaps	xmm0, xmmword ptr [rdi]
	cmp	rsi, 2
	jb	.LBB0_1
# %bb.2:
	lea	r8, [rsi - 1]
	add	rsi, -2
	mov	eax, r8d
	and	eax, 3
	cmp	rsi, 3
	jae	.LBB0_8
# %bb.3:
	mov	esi, 1
	movaps	xmm1, xmm0
	jmp	.LBB0_4
.LBB0_1:
	movaps	xmm1, xmm0
	movaps	xmmword ptr [rdx], xmm0
	movaps	xmmword ptr [rcx], xmm1
	ret
.LBB0_8:
	lea	r9, [rdi + 64]
	and	r8, -4
	neg	r8
	mov	esi, 1
	movaps	xmm1, xmm0
	.p2align	4
.LBB0_9:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm2, xmmword ptr [r9 - 48]
	movaps	xmm3, xmmword ptr [r9 - 32]
	movaps	xmm4, xmmword ptr [r9 - 16]
	movaps	xmm5, xmmword ptr [r9]
	minps	xmm0, xmm2
	maxps	xmm1, xmm2
	minps	xmm0, xmm3
	maxps	xmm1, xmm3
	minps	xmm0, xmm4
	maxps	xmm1, xmm4
	minps	xmm0, xmm5
	maxps	xmm1, xmm5
	add	r9, 64
	lea	r10, [r8 + rsi]
	add	r10, 4
	add	rsi, 4
	cmp	r10, 1
	jne	.LBB0_9
.LBB0_4:
	test	rax, rax
	je	.LBB0_7
# %bb.5:
	shl	rsi, 4
	add	rdi, rsi
	shl	eax, 4
	xor	esi, esi
	.p2align	4
.LBB0_6:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm2, xmmword ptr [rdi + rsi]
	minps	xmm0, xmm2
	maxps	xmm1, xmm2
	add	rsi, 16
	cmp	rax, rsi
	jne	.LBB0_6
.LBB0_7:
	movaps	xmmword ptr [rdx], xmm0
	movaps	xmmword ptr [rcx], xmm1
	ret
.Lfunc_end0:
	.size	cg_aabb, .Lfunc_end0-cg_aabb
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          # -- Begin function cg_saturate
.LCPI1_0:
	.long	0x3f800000                      # float 1
	.long	0x3f800000                      # float 1
	.long	0x3f800000                      # float 1
	.long	0x3f800000                      # float 1
	.text
	.globl	cg_saturate
	.p2align	4
	.type	cg_saturate,@function
cg_saturate:                            # @cg_saturate
	.cfi_startproc
# %bb.0:
	test	rdx, rdx
	je	.LBB1_5
# %bb.1:
	cmp	rdx, 1
	jne	.LBB1_6
# %bb.2:
	xor	eax, eax
	jmp	.LBB1_3
.LBB1_6:
	mov	rcx, rdx
	and	rcx, -2
	mov	r8d, 16
	xor	eax, eax
	xorps	xmm0, xmm0
	movaps	xmm1, xmmword ptr [rip + .LCPI1_0] # xmm1 = [1.0E+0,1.0E+0,1.0E+0,1.0E+0]
	.p2align	4
.LBB1_7:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm2, xmmword ptr [rdi + r8 - 16]
	maxps	xmm2, xmm0
	minps	xmm2, xmm1
	movaps	xmmword ptr [rsi + r8 - 16], xmm2
	movaps	xmm2, xmmword ptr [rdi + r8]
	maxps	xmm2, xmm0
	minps	xmm2, xmm1
	movaps	xmmword ptr [rsi + r8], xmm2
	add	rax, 2
	add	r8, 32
	cmp	rcx, rax
	jne	.LBB1_7
.LBB1_3:
	test	dl, 1
	je	.LBB1_5
# %bb.4:
	shl	rax, 4
	movaps	xmm0, xmmword ptr [rdi + rax]
	xorps	xmm1, xmm1
	maxps	xmm0, xmm1
	minps	xmm0, xmmword ptr [rip + .LCPI1_0]
	movaps	xmmword ptr [rsi + rax], xmm0
.LBB1_5:
	ret
.Lfunc_end1:
	.size	cg_saturate, .Lfunc_end1-cg_saturate
	.cfi_endproc
                                        # -- End function
	.globl	cg_with_w_expr                  # -- Begin function cg_with_w_expr
	.p2align	4
	.type	cg_with_w_expr,@function
cg_with_w_expr:                         # @cg_with_w_expr
	.cfi_startproc
# %bb.0:
	test	rcx, rcx
	je	.LBB2_5
# %bb.1:
	cmp	rcx, 1
	jne	.LBB2_6
# %bb.2:
	xor	eax, eax
	jmp	.LBB2_3
.LBB2_6:
	mov	r8, rcx
	and	r8, -2
	mov	r9d, 16
	xor	eax, eax
	.p2align	4
.LBB2_7:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [rdi + r9 - 16]
	movaps	xmm1, xmmword ptr [rsi + r9 - 16]
	addps	xmm1, xmm0
	blendps	xmm1, xmm0, 8                   # xmm1 = xmm1[0,1,2],xmm0[3]
	movaps	xmmword ptr [rdx + r9 - 16], xmm1
	movaps	xmm0, xmmword ptr [rdi + r9]
	movaps	xmm1, xmmword ptr [rsi + r9]
	addps	xmm1, xmm0
	blendps	xmm1, xmm0, 8                   # xmm1 = xmm1[0,1,2],xmm0[3]
	movaps	xmmword ptr [rdx + r9], xmm1
	add	rax, 2
	add	r9, 32
	cmp	r8, rax
	jne	.LBB2_7
.LBB2_3:
	test	cl, 1
	je	.LBB2_5
# %bb.4:
	shl	rax, 4
	movaps	xmm0, xmmword ptr [rdi + rax]
	movaps	xmm1, xmmword ptr [rsi + rax]
	addps	xmm1, xmm0
	blendps	xmm1, xmm0, 8                   # xmm1 = xmm1[0,1,2],xmm0[3]
	movaps	xmmword ptr [rdx + rax], xmm1
.LBB2_5:
	ret
.Lfunc_end2:
	.size	cg_with_w_expr, .Lfunc_end2-cg_with_w_expr
	.cfi_endproc
                                        # -- End function
	.globl	cg_cross3                       # -- Begin function cg_cross3
	.p2align	4
	.type	cg_cross3,@function
cg_cross3:                              # @cg_cross3
	.cfi_startproc
# %bb.0:
	test	rcx, rcx
	je	.LBB3_3
# %bb.1:
	xor	eax, eax
	.p2align	4
.LBB3_2:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [rdi + rax]
	movaps	xmm1, xmmword ptr [rsi + rax]
	movaps	xmm2, xmm0
	shufps	xmm2, xmm0, 201                 # xmm2 = xmm2[1,2],xmm0[0,3]
	mulps	xmm2, xmm1
	shufps	xmm1, xmm1, 201                 # xmm1 = xmm1[1,2,0,3]
	mulps	xmm1, xmm0
	subps	xmm1, xmm2
	shufps	xmm1, xmm1, 201                 # xmm1 = xmm1[1,2,0,3]
	movaps	xmmword ptr [rdx + rax], xmm1
	add	rax, 16
	dec	rcx
	jne	.LBB3_2
.LBB3_3:
	ret
.Lfunc_end3:
	.size	cg_cross3, .Lfunc_end3-cg_cross3
	.cfi_endproc
                                        # -- End function
	.globl	cg_cross3_value                 # -- Begin function cg_cross3_value
	.p2align	4
	.type	cg_cross3_value,@function
cg_cross3_value:                        # @cg_cross3_value
	.cfi_startproc
# %bb.0:
	movaps	xmm1, xmmword ptr [rdi]
	movaps	xmm0, xmmword ptr [rsi]
	movaps	xmm2, xmm1
	shufps	xmm2, xmm1, 201                 # xmm2 = xmm2[1,2],xmm1[0,3]
	mulps	xmm2, xmm0
	shufps	xmm0, xmm0, 201                 # xmm0 = xmm0[1,2,0,3]
	mulps	xmm0, xmm1
	subps	xmm0, xmm2
	shufps	xmm0, xmm0, 201                 # xmm0 = xmm0[1,2,0,3]
	ret
.Lfunc_end4:
	.size	cg_cross3_value, .Lfunc_end4-cg_cross3_value
	.cfi_endproc
                                        # -- End function
	.ident	"Ubuntu clang version 21.1.8 (6ubuntu1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_aabb
	.addrsig_sym cg_saturate
	.addrsig_sym cg_with_w_expr
	.addrsig_sym cg_cross3
	.addrsig_sym cg_cross3_value
	.addrsig_sym __gxx_personality_v0
