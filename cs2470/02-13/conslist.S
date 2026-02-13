	.file	"conslist.c"
	.text
	.p2align 4
	.globl	cons
	.type	cons, @function
cons:
.LFB39:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	%edi, %ebp
	movl	$16, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rsi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	malloc@PLT
	movl	%ebp, (%rax)
	movq	%rbx, 8(%rax)
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE39:
	.size	cons, .-cons
	.p2align 4
	.globl	sum_acc
	.type	sum_acc, @function
sum_acc:
.LFB40:
	.cfi_startproc
	endbr64
	movl	%esi, %eax
	testq	%rdi, %rdi
	je	.L8
	.p2align 4,,10
	.p2align 3
.L5:
	addl	(%rdi), %eax
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
	jne	.L5
.L8:
	ret
	.cfi_endproc
.LFE40:
	.size	sum_acc, .-sum_acc
	.p2align 4
	.globl	sum
	.type	sum, @function
sum:
.LFB41:
	.cfi_startproc
	endbr64
	xorl	%eax, %eax
	testq	%rdi, %rdi
	je	.L12
	.p2align 4,,10
	.p2align 3
.L13:
	addl	(%rdi), %eax
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
	jne	.L13
.L12:
	ret
	.cfi_endproc
.LFE41:
	.size	sum, .-sum
	.p2align 4
	.globl	sum2
	.type	sum2, @function
sum2:
.LFB42:
	.cfi_startproc
	endbr64
	xorl	%eax, %eax
	testq	%rdi, %rdi
	je	.L23
	.p2align 4,,10
	.p2align 3
.L22:
	addl	(%rdi), %eax
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
	jne	.L22
	ret
	.p2align 4,,10
	.p2align 3
.L23:
	ret
	.cfi_endproc
.LFE42:
	.size	sum2, .-sum2
	.p2align 4
	.globl	sum1
	.type	sum1, @function
sum1:
.LFB43:
	.cfi_startproc
	endbr64
	xorl	%eax, %eax
	testq	%rdi, %rdi
	je	.L25
	.p2align 4,,10
	.p2align 3
.L26:
	movl	(%rdi), %edx
	movq	8(%rdi), %rdi
	addl	%edx, %eax
	testq	%rdi, %rdi
	jne	.L26
.L25:
	ret
	.cfi_endproc
.LFE43:
	.size	sum1, .-sum1
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"sum = %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB44:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	$16, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	malloc@PLT
	movl	$16, %edi
	movl	$4, (%rax)
	movq	%rax, %rbx
	movq	$0, 8(%rax)
	call	malloc@PLT
	movl	$16, %edi
	movq	%rbx, 8(%rax)
	movq	%rax, %rbp
	movl	$3, (%rax)
	call	malloc@PLT
	movl	$16, %edi
	movl	$2, (%rax)
	movq	%rax, %rbx
	movq	%rbp, 8(%rax)
	call	malloc@PLT
	xorl	%edx, %edx
	testq	%rax, %rax
	je	.L35
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L34:
	movl	(%rbx), %eax
	movq	8(%rbx), %rbx
	addl	%eax, %edx
	testq	%rbx, %rbx
	jne	.L34
.L35:
	leaq	.LC0(%rip), %rsi
	movl	$2, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE44:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
