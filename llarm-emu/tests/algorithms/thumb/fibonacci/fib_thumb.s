	.cpu cortex-m3
	.arch armv7-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"fib_thumb.c"
	.text
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r4, r5, r7, r8, r9}
	sub	sp, sp, #44
	add	r7, sp, #0
	mov	r2, #10
	mov	r3, #0
	strd	r2, [r7, #8]
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r7, #32]
	mov	r2, #1
	mov	r3, #0
	strd	r2, [r7, #24]
	movs	r3, #2
	str	r3, [r7, #20]
	b	.L2
.L3:
	ldrd	r0, [r7, #32]
	ldrd	r2, [r7, #24]
	adds	r8, r0, r2
	adc	r9, r1, r3
	strd	r8, [r7]
	ldrd	r2, [r7, #24]
	strd	r2, [r7, #32]
	ldrd	r2, [r7]
	strd	r2, [r7, #24]
	ldr	r3, [r7, #20]
	adds	r3, r3, #1
	str	r3, [r7, #20]
.L2:
	ldr	r3, [r7, #20]
	asrs	r2, r3, #31
	mov	r4, r3
	mov	r5, r2
	ldrd	r2, [r7, #8]
	cmp	r2, r4
	sbcs	r3, r3, r5
	bge	.L3
	ldr	r3, [r7, #24]
	mov	r0, r3
	adds	r7, r7, #44
	mov	sp, r7
	@ sp needed
	pop	{r4, r5, r7, r8, r9}
	bx	lr
	.size	main, .-main
	.ident	"GCC: (Arch Repository) 14.2.0"
