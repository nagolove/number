	.file	"sret.c"
	.intel_syntax noprefix
	.text
	.globl	foo
	.type	foo, @function
foo:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 296
	.cfi_offset 3, -24
	mov	QWORD PTR -296[rbp], rdi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -24[rbp], rax
	xor	eax, eax
	mov	QWORD PTR -288[rbp], 0
	mov	QWORD PTR -280[rbp], 0
	mov	QWORD PTR -272[rbp], 0
	mov	QWORD PTR -264[rbp], 0
	mov	QWORD PTR -256[rbp], 0
	mov	QWORD PTR -248[rbp], 0
	mov	QWORD PTR -240[rbp], 0
	mov	QWORD PTR -232[rbp], 0
	mov	QWORD PTR -224[rbp], 0
	mov	QWORD PTR -216[rbp], 0
	mov	QWORD PTR -208[rbp], 0
	mov	QWORD PTR -200[rbp], 0
	mov	QWORD PTR -192[rbp], 0
	mov	QWORD PTR -184[rbp], 0
	mov	QWORD PTR -176[rbp], 0
	mov	QWORD PTR -168[rbp], 0
	mov	QWORD PTR -160[rbp], 0
	mov	QWORD PTR -152[rbp], 0
	mov	QWORD PTR -144[rbp], 0
	mov	QWORD PTR -136[rbp], 0
	mov	QWORD PTR -128[rbp], 0
	mov	QWORD PTR -120[rbp], 0
	mov	QWORD PTR -112[rbp], 0
	mov	QWORD PTR -104[rbp], 0
	mov	QWORD PTR -96[rbp], 0
	mov	QWORD PTR -88[rbp], 0
	mov	QWORD PTR -80[rbp], 0
	mov	QWORD PTR -72[rbp], 0
	mov	QWORD PTR -64[rbp], 0
	mov	QWORD PTR -56[rbp], 0
	mov	QWORD PTR -48[rbp], 0
	mov	QWORD PTR -40[rbp], 0
	mov	BYTE PTR -288[rbp], 42
	mov	rax, QWORD PTR -296[rbp]
	mov	rcx, QWORD PTR -288[rbp]
	mov	rbx, QWORD PTR -280[rbp]
	mov	QWORD PTR [rax], rcx
	mov	QWORD PTR 8[rax], rbx
	mov	rcx, QWORD PTR -272[rbp]
	mov	rbx, QWORD PTR -264[rbp]
	mov	QWORD PTR 16[rax], rcx
	mov	QWORD PTR 24[rax], rbx
	mov	rcx, QWORD PTR -256[rbp]
	mov	rbx, QWORD PTR -248[rbp]
	mov	QWORD PTR 32[rax], rcx
	mov	QWORD PTR 40[rax], rbx
	mov	rcx, QWORD PTR -240[rbp]
	mov	rbx, QWORD PTR -232[rbp]
	mov	QWORD PTR 48[rax], rcx
	mov	QWORD PTR 56[rax], rbx
	mov	rcx, QWORD PTR -224[rbp]
	mov	rbx, QWORD PTR -216[rbp]
	mov	QWORD PTR 64[rax], rcx
	mov	QWORD PTR 72[rax], rbx
	mov	rcx, QWORD PTR -208[rbp]
	mov	rbx, QWORD PTR -200[rbp]
	mov	QWORD PTR 80[rax], rcx
	mov	QWORD PTR 88[rax], rbx
	mov	rcx, QWORD PTR -192[rbp]
	mov	rbx, QWORD PTR -184[rbp]
	mov	QWORD PTR 96[rax], rcx
	mov	QWORD PTR 104[rax], rbx
	mov	rcx, QWORD PTR -176[rbp]
	mov	rbx, QWORD PTR -168[rbp]
	mov	QWORD PTR 112[rax], rcx
	mov	QWORD PTR 120[rax], rbx
	mov	rcx, QWORD PTR -160[rbp]
	mov	rbx, QWORD PTR -152[rbp]
	mov	QWORD PTR 128[rax], rcx
	mov	QWORD PTR 136[rax], rbx
	mov	rcx, QWORD PTR -144[rbp]
	mov	rbx, QWORD PTR -136[rbp]
	mov	QWORD PTR 144[rax], rcx
	mov	QWORD PTR 152[rax], rbx
	mov	rcx, QWORD PTR -128[rbp]
	mov	rbx, QWORD PTR -120[rbp]
	mov	QWORD PTR 160[rax], rcx
	mov	QWORD PTR 168[rax], rbx
	mov	rcx, QWORD PTR -112[rbp]
	mov	rbx, QWORD PTR -104[rbp]
	mov	QWORD PTR 176[rax], rcx
	mov	QWORD PTR 184[rax], rbx
	mov	rcx, QWORD PTR -96[rbp]
	mov	rbx, QWORD PTR -88[rbp]
	mov	QWORD PTR 192[rax], rcx
	mov	QWORD PTR 200[rax], rbx
	mov	rcx, QWORD PTR -80[rbp]
	mov	rbx, QWORD PTR -72[rbp]
	mov	QWORD PTR 208[rax], rcx
	mov	QWORD PTR 216[rax], rbx
	mov	rcx, QWORD PTR -64[rbp]
	mov	rbx, QWORD PTR -56[rbp]
	mov	QWORD PTR 224[rax], rcx
	mov	QWORD PTR 232[rax], rbx
	mov	rcx, QWORD PTR -48[rbp]
	mov	rbx, QWORD PTR -40[rbp]
	mov	QWORD PTR 240[rax], rcx
	mov	QWORD PTR 248[rax], rbx
	mov	rax, QWORD PTR -24[rbp]
	sub	rax, QWORD PTR fs:40
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	mov	rax, QWORD PTR -296[rbp]
	mov	rbx, QWORD PTR -8[rbp]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 272
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	lea	rax, -272[rbp]
	mov	rdi, rax
	mov	eax, 0
	call	foo
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L6
	call	__stack_chk_fail@PLT
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 14.2.1 20250207"
	.section	.note.GNU-stack,"",@progbits
