# g++ (Debian 14.2.0-19) 14.2.0
# g++ -S -O3 -std=c++20 -Wall -Isrc/tenvex  cg_reference.cpp
	.arch armv8-a
	.file	"cg_reference.cpp"
	.text
	.align	2
	.p2align 5,,15
	.global	cg_clean
	.type	cg_clean, %function
cg_clean:
.LFB5349:
	.cfi_startproc
	fmla	v1.4s, v0.4s, v1.4s
	fmla	v2.4s, v2.4s, v1.4s
	mov	v0.16b, v2.16b
	ret
	.cfi_endproc
.LFE5349:
	.size	cg_clean, .-cg_clean
	.align	2
	.p2align 5,,15
	.global	cg_spilled
	.type	cg_spilled, %function
cg_spilled:
.LFB5350:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	str	q2, [sp, 16]
	bl	cg_opaque_kernel
	ldr	q1, [sp, 16]
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	b	cg_opaque_kernel
	.cfi_endproc
.LFE5350:
	.size	cg_spilled, .-cg_spilled
	.ident	"GCC: (Debian 14.2.0-19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
