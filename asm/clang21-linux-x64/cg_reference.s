# Ubuntu clang version 21.1.8 (6ubuntu1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex -msse4.1 -masm=intel cg_reference.cpp
	.intel_syntax noprefix
	.file	"cg_reference.cpp"
	.text
	.globl	cg_clean                        # -- Begin function cg_clean
	.p2align	4
	.type	cg_clean,@function
cg_clean:                               # @cg_clean
	.cfi_startproc
# %bb.0:
	mulps	xmm0, xmm1
	addps	xmm0, xmm1
	mulps	xmm0, xmm2
	addps	xmm0, xmm2
	ret
.Lfunc_end0:
	.size	cg_clean, .Lfunc_end0-cg_clean
	.cfi_endproc
                                        # -- End function
	.globl	cg_spilled                      # -- Begin function cg_spilled
	.p2align	4
	.type	cg_spilled,@function
cg_spilled:                             # @cg_spilled
	.cfi_startproc
# %bb.0:
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	movaps	xmmword ptr [rsp], xmm2         # 16-byte Spill
	call	cg_opaque_kernel@PLT
	movaps	xmm1, xmmword ptr [rsp]         # 16-byte Reload
	add	rsp, 24
	.cfi_def_cfa_offset 8
	jmp	cg_opaque_kernel@PLT            # TAILCALL
.Lfunc_end1:
	.size	cg_spilled, .Lfunc_end1-cg_spilled
	.cfi_endproc
                                        # -- End function
	.ident	"Ubuntu clang version 21.1.8 (6ubuntu1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_clean
	.addrsig_sym cg_spilled
	.addrsig_sym __gxx_personality_v0
