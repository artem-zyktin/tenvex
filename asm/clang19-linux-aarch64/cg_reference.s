# Debian clang version 19.1.7 (3+b1)
# clang++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_reference.cpp
	.text
	.file	"cg_reference.cpp"
	.globl	cg_clean                        // -- Begin function cg_clean
	.p2align	2
	.type	cg_clean,@function
cg_clean:                               // @cg_clean
	.cfi_startproc
// %bb.0:
	fmul	v0.4s, v0.4s, v1.4s
	fadd	v0.4s, v0.4s, v1.4s
	fmul	v0.4s, v0.4s, v2.4s
	fadd	v0.4s, v0.4s, v2.4s
	ret
.Lfunc_end0:
	.size	cg_clean, .Lfunc_end0-cg_clean
	.cfi_endproc
                                        // -- End function
	.globl	cg_spilled                      // -- Begin function cg_spilled
	.p2align	2
	.type	cg_spilled,@function
cg_spilled:                             // @cg_spilled
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             // 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	q2, [sp]                        // 16-byte Folded Spill
	bl	cg_opaque_kernel
	ldr	q1, [sp]                        // 16-byte Folded Reload
	.cfi_def_cfa wsp, 32
	ldp	x29, x30, [sp, #16]             // 16-byte Folded Reload
	add	sp, sp, #32
	.cfi_def_cfa_offset 0
	.cfi_restore w30
	.cfi_restore w29
	b	cg_opaque_kernel
.Lfunc_end1:
	.size	cg_spilled, .Lfunc_end1-cg_spilled
	.cfi_endproc
                                        // -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"Debian clang version 19.1.7 (3+b1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym cg_clean
	.addrsig_sym cg_spilled
	.addrsig_sym __gxx_personality_v0
