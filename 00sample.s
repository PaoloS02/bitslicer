	.text
	.file	"sample.c"
	.globl	offset
	.p2align	4, 0x90
	.type	offset,@function
offset:                                 # @offset
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Lcfi0:
	.cfi_def_cfa_offset 16
.Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Lcfi2:
	.cfi_def_cfa_register %rbp
	movl	$6, %eax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	offset, .Lfunc_end0-offset
	.cfi_endproc

	.globl	address
	.p2align	4, 0x90
	.type	address,@function
address:                                # @address
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Lcfi3:
	.cfi_def_cfa_offset 16
.Lcfi4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Lcfi5:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	retq
.Lfunc_end1:
	.size	address, .Lfunc_end1-address
	.cfi_endproc

	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Lcfi6:
	.cfi_def_cfa_offset 16
.Lcfi7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Lcfi8:
	.cfi_def_cfa_register %rbp
	subq	$320, %rsp              # imm = 0x140
	movl	$0, -4(%rbp)
	movb	$0, -309(%rbp)
	movl	$0, -308(%rbp)
.LBB2_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$10, -308(%rbp)
	jge	.LBB2_4
# BB#2:                                 # %for.body
                                        #   in Loop: Header=BB2_1 Depth=1
	movslq	-308(%rbp), %rax
	movb	$85, -23(%rbp,%rax)
# BB#3:                                 # %for.inc
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	-308(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -308(%rbp)
	jmp	.LBB2_1
.LBB2_4:                                # %for.end
	movl	$0, -308(%rbp)
.LBB2_5:                                # %for.cond1
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$4, -308(%rbp)
	jge	.LBB2_8
# BB#6:                                 # %for.body3
                                        #   in Loop: Header=BB2_5 Depth=1
	movslq	-308(%rbp), %rax
	movb	$-86, -13(%rbp,%rax)
	movl	-308(%rbp), %ecx
	addl	$4, %ecx
	movslq	%ecx, %rax
	movb	$85, -13(%rbp,%rax)
# BB#7:                                 # %for.inc8
                                        #   in Loop: Header=BB2_5 Depth=1
	movl	-308(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -308(%rbp)
	jmp	.LBB2_5
.LBB2_8:                                # %for.end10
	movl	$0, -308(%rbp)
.LBB2_9:                                # %for.cond11
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$8, -308(%rbp)
	jge	.LBB2_12
# BB#10:                                # %for.body13
                                        #   in Loop: Header=BB2_9 Depth=1
	movslq	-308(%rbp), %rax
	movzbl	-13(%rbp,%rax), %ecx
	movl	-308(%rbp), %edx
	addl	$2, %edx
	movslq	%edx, %rax
	movzbl	-23(%rbp,%rax), %edx
	xorl	%edx, %ecx
	movb	%cl, %sil
	movslq	-308(%rbp), %rax
	movb	%sil, -13(%rbp,%rax)
# BB#11:                                # %for.inc23
                                        #   in Loop: Header=BB2_9 Depth=1
	movl	-308(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -308(%rbp)
	jmp	.LBB2_9
.LBB2_12:                               # %for.end25
	movl	$6, -308(%rbp)
	callq	offset
	leaq	-309(%rbp), %rdi
	movslq	%eax, %rcx
	movb	$-86, -13(%rbp,%rcx)
	callq	address
	movb	$9, (%rax)
	movl	$0, -308(%rbp)
.LBB2_13:                               # %for.cond27
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$8, -308(%rbp)
	jge	.LBB2_16
# BB#14:                                # %for.body30
                                        #   in Loop: Header=BB2_13 Depth=1
	movabsq	$.L.str, %rdi
	movl	-308(%rbp), %esi
	movslq	-308(%rbp), %rax
	movzbl	-13(%rbp,%rax), %edx
	movb	$0, %al
	callq	printf
	movl	%eax, -316(%rbp)        # 4-byte Spill
# BB#15:                                # %for.inc35
                                        #   in Loop: Header=BB2_13 Depth=1
	movl	-308(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -308(%rbp)
	jmp	.LBB2_13
.LBB2_16:                               # %for.end37
	xorl	%eax, %eax
	addq	$320, %rsp              # imm = 0x140
	popq	%rbp
	retq
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc

	.type	val,@object             # @val
	.data
	.globl	val
	.p2align	3
val:
	.long	2                       # 0x2
	.size	val, 4

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"P[%d]: %d\n"
	.size	.L.str, 11


	.ident	"clang version 5.0.0 (trunk 301269) (llvm/trunk 301268)"
	.section	".note.GNU-stack","",@progbits
