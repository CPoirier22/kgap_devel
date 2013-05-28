	.file	"cstart.c"

	.section	.cstart,"ax",@progbits
	.align	4
	.globl	_start
	.type	_start, @function
_start:
	movd    $3405691582, (r1,r0)
	di
	movd	$_cstack+1020@l, (sp)
	lprd	(sp), usp
	movd	$_istack+252@l, (r1, r0)
	lprd    (r1, r0), isp
	movd    $_IntTable, (r1, r0)
    lpr     r0, intbasel
    lpr     r1, intbaseh
	spr     cfg, r0
    orw     $256, r0
    nop
    lpr     r0, cfg
	bal     (ra), _main@c
	jump	(ra)
	.size	_start, .-_start

	.section	.text
	.align	4
	.globl	___disable_interrupt
	.type	___disable_interrupt, @function
___disable_interrupt:
	di
	jump	(ra)
	.size	___disable_interrupt, .-___disable_interrupt

	.align	4
	.globl	___enable_interrupt
	.type	___enable_interrupt, @function
___enable_interrupt:
	ei
	jump	(ra)
	.size	___enable_interrupt, .-___enable_interrupt

	.align	4
	.globl	_Get_isp
	.type	_Get_isp, @function
_Get_isp:
    sprd     isp, (r1,r0)
	jump	(ra)
	.size	_Get_isp, .-_Get_isp

	.align	4
	.globl	_Get_sp
	.type	_Get_sp, @function
_Get_sp:
    movd    (sp),(r1,r0)
	jump	(ra)
	.size	_Get_sp, .-_Get_sp

	.align	4
	.globl	___set_PSR_I_bit
	.type	___set_PSR_I_bit, @function
___set_PSR_I_bit:
	push    $1, r0
	spr     psr, r0
    orw     $0x800, r0
    lpr     r0, psr
	pop     $1, r0
	jump	(ra)
	.size	___set_PSR_I_bit, .-___set_PSR_I_bit

		.align	4
	.globl	___enable_icache
	.type	___enable_icache, @function
___enable_icache:
	push    $1, r0
	spr     cfg, r0
    orw     $0x10, r0
    lpr     r0, cfg
	pop     $1, r0
	jump	(ra)
	.size	___enable_icache, .-___enable_icache


	.ident	"GCC: (GNU) 4.1.2"
