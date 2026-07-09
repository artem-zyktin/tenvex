# Ubuntu clang version 21.1.8 (6ubuntu1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_composed.cpp
	.intel_syntax noprefix
	.file	"cg_composed.cpp"
	.text
	.globl	cg_lerp                         # -- Begin function cg_lerp
	.p2align	4
	.type	cg_lerp,@function
cg_lerp:                                # @cg_lerp
	.cfi_startproc
# %bb.0:
	test	rcx, rcx
	je	.LBB0_5
# %bb.1:
	shufps	xmm0, xmm0, 0                   # xmm0 = xmm0[0,0,0,0]
	cmp	rcx, 1
	jne	.LBB0_6
# %bb.2:
	xor	eax, eax
	jmp	.LBB0_3
.LBB0_6:
	mov	r8, rcx
	and	r8, -2
	mov	r9d, 16
	xor	eax, eax
	.p2align	4
.LBB0_7:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm1, xmmword ptr [rsi + r9 - 16]
	movaps	xmm2, xmmword ptr [rdi + r9 - 16]
	subps	xmm1, xmm2
	mulps	xmm1, xmm0
	addps	xmm1, xmm2
	movaps	xmmword ptr [rdx + r9 - 16], xmm1
	movaps	xmm1, xmmword ptr [rsi + r9]
	movaps	xmm2, xmmword ptr [rdi + r9]
	subps	xmm1, xmm2
	mulps	xmm1, xmm0
	addps	xmm1, xmm2
	movaps	xmmword ptr [rdx + r9], xmm1
	add	rax, 2
	add	r9, 32
	cmp	r8, rax
	jne	.LBB0_7
.LBB0_3:
	test	cl, 1
	je	.LBB0_5
# %bb.4:
	shl	rax, 4
	movaps	xmm1, xmmword ptr [rsi + rax]
	movaps	xmm2, xmmword ptr [rdi + rax]
	subps	xmm1, xmm2
	mulps	xmm0, xmm1
	addps	xmm0, xmm2
	movaps	xmmword ptr [rdx + rax], xmm0
.LBB0_5:
	ret
.Lfunc_end0:
	.size	cg_lerp, .Lfunc_end0-cg_lerp
	.cfi_endproc
                                        # -- End function
	.globl	cg_clamp                        # -- Begin function cg_clamp
	.p2align	4
	.type	cg_clamp,@function
cg_clamp:                               # @cg_clamp
	.cfi_startproc
# %bb.0:
	test	r8, r8
	je	.LBB1_5
# %bb.1:
	cmp	r8, 1
	jne	.LBB1_6
# %bb.2:
	xor	eax, eax
	jmp	.LBB1_3
.LBB1_6:
	mov	r9, r8
	and	r9, -2
	mov	r10d, 16
	xor	eax, eax
	.p2align	4
.LBB1_7:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [rdi + r10 - 16]
	maxps	xmm0, xmmword ptr [rsi + r10 - 16]
	minps	xmm0, xmmword ptr [rdx + r10 - 16]
	movaps	xmmword ptr [rcx + r10 - 16], xmm0
	movaps	xmm0, xmmword ptr [rdi + r10]
	maxps	xmm0, xmmword ptr [rsi + r10]
	minps	xmm0, xmmword ptr [rdx + r10]
	movaps	xmmword ptr [rcx + r10], xmm0
	add	rax, 2
	add	r10, 32
	cmp	r9, rax
	jne	.LBB1_7
.LBB1_3:
	test	r8b, 1
	je	.LBB1_5
# %bb.4:
	shl	rax, 4
	movaps	xmm0, xmmword ptr [rdi + rax]
	maxps	xmm0, xmmword ptr [rsi + rax]
	minps	xmm0, xmmword ptr [rdx + rax]
	movaps	xmmword ptr [rcx + rax], xmm0
.LBB1_5:
	ret
.Lfunc_end1:
	.size	cg_clamp, .Lfunc_end1-cg_clamp
	.cfi_endproc
                                        # -- End function
	.globl	cg_reflect                      # -- Begin function cg_reflect
	.p2align	4
	.type	cg_reflect,@function
cg_reflect:                             # @cg_reflect
	.cfi_startproc
# %bb.0:
	test	rcx, rcx
	je	.LBB2_3
# %bb.1:
	xor	eax, eax
	.p2align	4
.LBB2_2:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [rdi + rax]
	movaps	xmm1, xmmword ptr [rsi + rax]
	movaps	xmm2, xmm0
	mulps	xmm2, xmm1
	movshdup	xmm3, xmm2                      # xmm3 = xmm2[1,1,3,3]
	addss	xmm3, xmm2
	movhlps	xmm2, xmm2                      # xmm2 = xmm2[1,1]
	addss	xmm2, xmm3
	addss	xmm2, xmm2
	shufps	xmm2, xmm2, 0                   # xmm2 = xmm2[0,0,0,0]
	mulps	xmm2, xmm1
	subps	xmm0, xmm2
	movaps	xmmword ptr [rdx + rax], xmm0
	add	rax, 16
	dec	rcx
	jne	.LBB2_2
.LBB2_3:
	ret
.Lfunc_end2:
	.size	cg_reflect, .Lfunc_end2-cg_reflect
	.cfi_endproc
                                        # -- End function
	.globl	cg_distance3_sq                 # -- Begin function cg_distance3_sq
	.p2align	4
	.type	cg_distance3_sq,@function
cg_distance3_sq:                        # @cg_distance3_sq
	.cfi_startproc
# %bb.0:
	test	rcx, rcx
	je	.LBB3_5
# %bb.1:
	cmp	rcx, 1
	jne	.LBB3_6
# %bb.2:
	xor	eax, eax
	jmp	.LBB3_3
.LBB3_6:
	mov	r8, rcx
	and	r8, -2
	mov	r9d, 4
	xor	eax, eax
	.p2align	4
.LBB3_7:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [rdi + 4*r9 - 16]
	subps	xmm0, xmmword ptr [rsi + 4*r9 - 16]
	mulps	xmm0, xmm0
	movshdup	xmm1, xmm0                      # xmm1 = xmm0[1,1,3,3]
	addss	xmm1, xmm0
	movhlps	xmm0, xmm0                      # xmm0 = xmm0[1,1]
	addss	xmm0, xmm1
	movss	dword ptr [rdx + r9 - 4], xmm0
	movaps	xmm0, xmmword ptr [rdi + 4*r9]
	subps	xmm0, xmmword ptr [rsi + 4*r9]
	mulps	xmm0, xmm0
	movshdup	xmm1, xmm0                      # xmm1 = xmm0[1,1,3,3]
	addss	xmm1, xmm0
	movhlps	xmm0, xmm0                      # xmm0 = xmm0[1,1]
	addss	xmm0, xmm1
	movss	dword ptr [rdx + r9], xmm0
	add	rax, 2
	add	r9, 8
	cmp	r8, rax
	jne	.LBB3_7
.LBB3_3:
	test	cl, 1
	je	.LBB3_5
# %bb.4:
	mov	rcx, rax
	shl	rcx, 4
	movaps	xmm0, xmmword ptr [rdi + rcx]
	subps	xmm0, xmmword ptr [rsi + rcx]
	mulps	xmm0, xmm0
	movshdup	xmm1, xmm0                      # xmm1 = xmm0[1,1,3,3]
	addss	xmm1, xmm0
	movhlps	xmm0, xmm0                      # xmm0 = xmm0[1,1]
	addss	xmm0, xmm1
	movss	dword ptr [rdx + 4*rax], xmm0
.LBB3_5:
	ret
.Lfunc_end3:
	.size	cg_distance3_sq, .Lfunc_end3-cg_distance3_sq
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0                          # -- Begin function cg_orthogonal
.LCPI4_0:
	.long	0x7fffffff                      # float NaN
	.long	0x7fffffff                      # float NaN
	.long	0x7fffffff                      # float NaN
	.long	0x7fffffff                      # float NaN
.LCPI4_1:
	.long	2147483648                      # 0x80000000
	.long	2147483648                      # 0x80000000
	.long	2147483648                      # 0x80000000
	.long	2147483648                      # 0x80000000
	.text
	.globl	cg_orthogonal
	.p2align	4
	.type	cg_orthogonal,@function
cg_orthogonal:                          # @cg_orthogonal
	.cfi_startproc
# %bb.0:
	test	rdx, rdx
	je	.LBB4_6
# %bb.1:
	xor	eax, eax
	movaps	xmm0, xmmword ptr [rip + .LCPI4_0] # xmm0 = [NaN,NaN,NaN,NaN]
	movaps	xmm1, xmmword ptr [rip + .LCPI4_1] # xmm1 = [2147483648,2147483648,2147483648,2147483648]
	jmp	.LBB4_2
	.p2align	4
.LBB4_3:                                #   in Loop: Header=BB4_2 Depth=1
	movshdup	xmm3, xmm2                      # xmm3 = xmm2[1,1,3,3]
	xorps	xmm3, xmm1
	insertps	xmm3, xmm2, 28                  # xmm3 = xmm3[0],xmm2[0],zero,zero
	movaps	xmmword ptr [rsi + rax], xmm3
	add	rax, 16
	dec	rdx
	je	.LBB4_6
.LBB4_2:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm2, xmmword ptr [rdi + rax]
	movss	xmm3, dword ptr [rdi + rax + 8] # xmm3 = mem[0],zero,zero,zero
	movaps	xmm4, xmm2
	andps	xmm4, xmm0
	movaps	xmm5, xmm3
	andps	xmm5, xmm0
	ucomiss	xmm4, xmm5
	ja	.LBB4_3
# %bb.4:                                #   in Loop: Header=BB4_2 Depth=1
	movsldup	xmm3, xmm3                      # xmm3 = xmm3[0,0,2,2]
	xorps	xmm3, xmm1
	insertps	xmm3, xmm2, 105                 # xmm3 = zero,xmm3[1],xmm2[1],zero
	movaps	xmmword ptr [rsi + rax], xmm3
	add	rax, 16
	dec	rdx
	jne	.LBB4_2
.LBB4_6:
	ret
.Lfunc_end4:
	.size	cg_orthogonal, .Lfunc_end4-cg_orthogonal
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2, 0x0                          # -- Begin function cg_nlerp
.LCPI5_0:
	.long	0x3f800000                      # float 1
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4, 0x0
.LCPI5_1:
	.long	0x80000000                      # float -0
	.long	0x80000000                      # float -0
	.long	0x80000000                      # float -0
	.long	0x80000000                      # float -0
	.text
	.globl	cg_nlerp
	.p2align	4
	.type	cg_nlerp,@function
cg_nlerp:                               # @cg_nlerp
	.cfi_startproc
# %bb.0:
	test	rcx, rcx
	je	.LBB5_3
# %bb.1:
	movaps	xmm1, xmm0
	movss	xmm2, dword ptr [rip + .LCPI5_0] # xmm2 = [1.0E+0,0.0E+0,0.0E+0,0.0E+0]
	subss	xmm2, xmm0
	shufps	xmm2, xmm2, 0                   # xmm2 = xmm2[0,0,0,0]
	movaps	xmm3, xmmword ptr [rip + .LCPI5_1] # xmm3 = [-0.0E+0,-0.0E+0,-0.0E+0,-0.0E+0]
	xorps	xmm3, xmm0
	xor	eax, eax
	xorps	xmm4, xmm4
	.p2align	4
.LBB5_2:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [rdi + rax]
	movaps	xmm5, xmmword ptr [rsi + rax]
	movaps	xmm6, xmm2
	mulps	xmm6, xmm0
	mulps	xmm0, xmm5
	haddps	xmm0, xmm0
	haddps	xmm0, xmm0
	cmpltss	xmm0, xmm4
	movaps	xmm7, xmm1
	blendvps	xmm7, xmm3, xmm0
	shufps	xmm7, xmm7, 0                   # xmm7 = xmm7[0,0,0,0]
	mulps	xmm7, xmm5
	addps	xmm7, xmm6
	movaps	xmm0, xmm7
	mulps	xmm0, xmm7
	haddps	xmm0, xmm0
	haddps	xmm0, xmm0
	sqrtps	xmm0, xmm0
	divps	xmm7, xmm0
	movaps	xmmword ptr [rdx + rax], xmm7
	add	rax, 16
	dec	rcx
	jne	.LBB5_2
.LBB5_3:
	ret
.Lfunc_end5:
	.size	cg_nlerp, .Lfunc_end5-cg_nlerp
	.cfi_endproc
                                        # -- End function
	.ident	"Ubuntu clang version 21.1.8 (6ubuntu1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_lerp
	.addrsig_sym cg_clamp
	.addrsig_sym cg_reflect
	.addrsig_sym cg_distance3_sq
	.addrsig_sym cg_orthogonal
	.addrsig_sym cg_nlerp
	.addrsig_sym __gxx_personality_v0
