# Ubuntu clang version 21.1.8 (6ubuntu1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_reductions.cpp
	.intel_syntax noprefix
	.file	"cg_reductions.cpp"
	.text
	.globl	cg_dot3                         # -- Begin function cg_dot3
	.p2align	4
	.type	cg_dot3,@function
cg_dot3:                                # @cg_dot3
	.cfi_startproc
# %bb.0:
	test	rcx, rcx
	je	.LBB0_5
# %bb.1:
	cmp	rcx, 1
	jne	.LBB0_6
# %bb.2:
	xor	eax, eax
	jmp	.LBB0_3
.LBB0_6:
	mov	r8, rcx
	and	r8, -2
	mov	r9d, 4
	xor	eax, eax
	.p2align	4
.LBB0_7:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [rdi + 4*r9 - 16]
	mulps	xmm0, xmmword ptr [rsi + 4*r9 - 16]
	movshdup	xmm1, xmm0                      # xmm1 = xmm0[1,1,3,3]
	addss	xmm1, xmm0
	movhlps	xmm0, xmm0                      # xmm0 = xmm0[1,1]
	addss	xmm0, xmm1
	movss	dword ptr [rdx + r9 - 4], xmm0
	movaps	xmm0, xmmword ptr [rdi + 4*r9]
	mulps	xmm0, xmmword ptr [rsi + 4*r9]
	movshdup	xmm1, xmm0                      # xmm1 = xmm0[1,1,3,3]
	addss	xmm1, xmm0
	movhlps	xmm0, xmm0                      # xmm0 = xmm0[1,1]
	addss	xmm0, xmm1
	movss	dword ptr [rdx + r9], xmm0
	add	rax, 2
	add	r9, 8
	cmp	r8, rax
	jne	.LBB0_7
.LBB0_3:
	test	cl, 1
	je	.LBB0_5
# %bb.4:
	mov	rcx, rax
	shl	rcx, 4
	movaps	xmm0, xmmword ptr [rdi + rcx]
	mulps	xmm0, xmmword ptr [rsi + rcx]
	movshdup	xmm1, xmm0                      # xmm1 = xmm0[1,1,3,3]
	addss	xmm1, xmm0
	movhlps	xmm0, xmm0                      # xmm0 = xmm0[1,1]
	addss	xmm0, xmm1
	movss	dword ptr [rdx + 4*rax], xmm0
.LBB0_5:
	ret
.Lfunc_end0:
	.size	cg_dot3, .Lfunc_end0-cg_dot3
	.cfi_endproc
                                        # -- End function
	.globl	cg_dot4                         # -- Begin function cg_dot4
	.p2align	4
	.type	cg_dot4,@function
cg_dot4:                                # @cg_dot4
	.cfi_startproc
# %bb.0:
	test	rcx, rcx
	je	.LBB1_5
# %bb.1:
	cmp	rcx, 1
	jne	.LBB1_6
# %bb.2:
	xor	eax, eax
	jmp	.LBB1_3
.LBB1_6:
	mov	r8, rcx
	and	r8, -2
	mov	r9d, 4
	xor	eax, eax
	.p2align	4
.LBB1_7:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [rdi + 4*r9 - 16]
	mulps	xmm0, xmmword ptr [rsi + 4*r9 - 16]
	haddps	xmm0, xmm0
	haddps	xmm0, xmm0
	movss	dword ptr [rdx + r9 - 4], xmm0
	movaps	xmm0, xmmword ptr [rdi + 4*r9]
	mulps	xmm0, xmmword ptr [rsi + 4*r9]
	haddps	xmm0, xmm0
	haddps	xmm0, xmm0
	movss	dword ptr [rdx + r9], xmm0
	add	rax, 2
	add	r9, 8
	cmp	r8, rax
	jne	.LBB1_7
.LBB1_3:
	test	cl, 1
	je	.LBB1_5
# %bb.4:
	mov	rcx, rax
	shl	rcx, 4
	movaps	xmm0, xmmword ptr [rdi + rcx]
	mulps	xmm0, xmmword ptr [rsi + rcx]
	haddps	xmm0, xmm0
	haddps	xmm0, xmm0
	movss	dword ptr [rdx + 4*rax], xmm0
.LBB1_5:
	ret
.Lfunc_end1:
	.size	cg_dot4, .Lfunc_end1-cg_dot4
	.cfi_endproc
                                        # -- End function
	.globl	cg_magnitude3                   # -- Begin function cg_magnitude3
	.p2align	4
	.type	cg_magnitude3,@function
cg_magnitude3:                          # @cg_magnitude3
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
	lea	r8, [rdi + 16]
	xor	eax, eax
	.p2align	4
.LBB2_7:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [r8 - 16]
	mulps	xmm0, xmm0
	movshdup	xmm1, xmm0                      # xmm1 = xmm0[1,1,3,3]
	addss	xmm1, xmm0
	movhlps	xmm0, xmm0                      # xmm0 = xmm0[1,1]
	addss	xmm0, xmm1
	sqrtss	xmm0, xmm0
	movss	dword ptr [rsi + 4*rax], xmm0
	movaps	xmm0, xmmword ptr [r8]
	mulps	xmm0, xmm0
	movshdup	xmm1, xmm0                      # xmm1 = xmm0[1,1,3,3]
	addss	xmm1, xmm0
	movhlps	xmm0, xmm0                      # xmm0 = xmm0[1,1]
	addss	xmm0, xmm1
	sqrtss	xmm0, xmm0
	movss	dword ptr [rsi + 4*rax + 4], xmm0
	add	rax, 2
	add	r8, 32
	cmp	rcx, rax
	jne	.LBB2_7
.LBB2_3:
	test	dl, 1
	je	.LBB2_5
# %bb.4:
	mov	rcx, rax
	shl	rcx, 4
	movaps	xmm0, xmmword ptr [rdi + rcx]
	mulps	xmm0, xmm0
	movshdup	xmm1, xmm0                      # xmm1 = xmm0[1,1,3,3]
	addss	xmm1, xmm0
	movhlps	xmm0, xmm0                      # xmm0 = xmm0[1,1]
	addss	xmm0, xmm1
	sqrtss	xmm0, xmm0
	movss	dword ptr [rsi + 4*rax], xmm0
.LBB2_5:
	ret
.Lfunc_end2:
	.size	cg_magnitude3, .Lfunc_end2-cg_magnitude3
	.cfi_endproc
                                        # -- End function
	.globl	cg_magnitude3_sq                # -- Begin function cg_magnitude3_sq
	.p2align	4
	.type	cg_magnitude3_sq,@function
cg_magnitude3_sq:                       # @cg_magnitude3_sq
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
	lea	r8, [rdi + 16]
	xor	eax, eax
	.p2align	4
.LBB3_7:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [r8 - 16]
	mulps	xmm0, xmm0
	movshdup	xmm1, xmm0                      # xmm1 = xmm0[1,1,3,3]
	addss	xmm1, xmm0
	movhlps	xmm0, xmm0                      # xmm0 = xmm0[1,1]
	addss	xmm0, xmm1
	movss	dword ptr [rsi + 4*rax], xmm0
	movaps	xmm0, xmmword ptr [r8]
	mulps	xmm0, xmm0
	movshdup	xmm1, xmm0                      # xmm1 = xmm0[1,1,3,3]
	addss	xmm1, xmm0
	movhlps	xmm0, xmm0                      # xmm0 = xmm0[1,1]
	addss	xmm0, xmm1
	movss	dword ptr [rsi + 4*rax + 4], xmm0
	add	rax, 2
	add	r8, 32
	cmp	rcx, rax
	jne	.LBB3_7
.LBB3_3:
	test	dl, 1
	je	.LBB3_5
# %bb.4:
	mov	rcx, rax
	shl	rcx, 4
	movaps	xmm0, xmmword ptr [rdi + rcx]
	mulps	xmm0, xmm0
	movshdup	xmm1, xmm0                      # xmm1 = xmm0[1,1,3,3]
	addss	xmm1, xmm0
	movhlps	xmm0, xmm0                      # xmm0 = xmm0[1,1]
	addss	xmm0, xmm1
	movss	dword ptr [rsi + 4*rax], xmm0
.LBB3_5:
	ret
.Lfunc_end3:
	.size	cg_magnitude3_sq, .Lfunc_end3-cg_magnitude3_sq
	.cfi_endproc
                                        # -- End function
	.globl	cg_mag3_lt_mag3                 # -- Begin function cg_mag3_lt_mag3
	.p2align	4
	.type	cg_mag3_lt_mag3,@function
cg_mag3_lt_mag3:                        # @cg_mag3_lt_mag3
	.cfi_startproc
# %bb.0:
	test	rcx, rcx
	je	.LBB4_3
# %bb.1:
	xor	eax, eax
	xor	r8d, r8d
	.p2align	4
.LBB4_2:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm0, xmmword ptr [rdi + rax]
	movaps	xmm1, xmmword ptr [rsi + rax]
	mulps	xmm0, xmm0
	mulps	xmm1, xmm1
	movaps	xmm2, xmm0
	haddps	xmm2, xmm1
	shufps	xmm2, xmm2, 232                 # xmm2 = xmm2[0,2,2,3]
	movhlps	xmm0, xmm0                      # xmm0 = xmm0[1,1]
	insertps	xmm0, xmm1, 156                 # xmm0 = xmm0[0],xmm1[2],zero,zero
	addps	xmm0, xmm2
	movshdup	xmm1, xmm0                      # xmm1 = xmm0[1,1,3,3]
	ucomiss	xmm1, xmm0
	seta	byte ptr [rdx + r8]
	inc	r8
	add	rax, 16
	cmp	rcx, r8
	jne	.LBB4_2
.LBB4_3:
	ret
.Lfunc_end4:
	.size	cg_mag3_lt_mag3, .Lfunc_end4-cg_mag3_lt_mag3
	.cfi_endproc
                                        # -- End function
	.globl	cg_mag3_lt_scalar               # -- Begin function cg_mag3_lt_scalar
	.p2align	4
	.type	cg_mag3_lt_scalar,@function
cg_mag3_lt_scalar:                      # @cg_mag3_lt_scalar
	.cfi_startproc
# %bb.0:
	test	rdx, rdx
	je	.LBB5_6
# %bb.1:
	xorps	xmm1, xmm1
	ucomiss	xmm1, xmm0
	jbe	.LBB5_2
# %bb.9:
	mov	rdi, rsi
	xor	esi, esi
	jmp	memset@PLT                      # TAILCALL
.LBB5_2:
	mulss	xmm0, xmm0
	cmp	rdx, 1
	jne	.LBB5_7
# %bb.3:
	xor	eax, eax
	jmp	.LBB5_4
.LBB5_7:
	mov	rcx, rdx
	and	rcx, -2
	lea	r8, [rdi + 16]
	xor	eax, eax
	.p2align	4
.LBB5_8:                                # =>This Inner Loop Header: Depth=1
	movaps	xmm1, xmmword ptr [r8 - 16]
	mulps	xmm1, xmm1
	movshdup	xmm2, xmm1                      # xmm2 = xmm1[1,1,3,3]
	addss	xmm2, xmm1
	movhlps	xmm1, xmm1                      # xmm1 = xmm1[1,1]
	addss	xmm1, xmm2
	ucomiss	xmm0, xmm1
	seta	byte ptr [rsi + rax]
	movaps	xmm1, xmmword ptr [r8]
	mulps	xmm1, xmm1
	movshdup	xmm2, xmm1                      # xmm2 = xmm1[1,1,3,3]
	addss	xmm2, xmm1
	movhlps	xmm1, xmm1                      # xmm1 = xmm1[1,1]
	addss	xmm1, xmm2
	ucomiss	xmm0, xmm1
	seta	byte ptr [rsi + rax + 1]
	add	rax, 2
	add	r8, 32
	cmp	rcx, rax
	jne	.LBB5_8
.LBB5_4:
	test	dl, 1
	je	.LBB5_6
# %bb.5:
	mov	rcx, rax
	shl	rcx, 4
	movaps	xmm1, xmmword ptr [rdi + rcx]
	mulps	xmm1, xmm1
	movshdup	xmm2, xmm1                      # xmm2 = xmm1[1,1,3,3]
	addss	xmm2, xmm1
	movhlps	xmm1, xmm1                      # xmm1 = xmm1[1,1]
	addss	xmm1, xmm2
	ucomiss	xmm0, xmm1
	seta	byte ptr [rsi + rax]
.LBB5_6:
	ret
.Lfunc_end5:
	.size	cg_mag3_lt_scalar, .Lfunc_end5-cg_mag3_lt_scalar
	.cfi_endproc
                                        # -- End function
	.ident	"Ubuntu clang version 21.1.8 (6ubuntu1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_dot3
	.addrsig_sym cg_dot4
	.addrsig_sym cg_magnitude3
	.addrsig_sym cg_magnitude3_sq
	.addrsig_sym cg_mag3_lt_mag3
	.addrsig_sym cg_mag3_lt_scalar
	.addrsig_sym __gxx_personality_v0
