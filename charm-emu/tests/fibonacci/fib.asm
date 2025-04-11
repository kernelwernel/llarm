
fib.bin:     file format binary


Disassembly of section .data:

00000000 <.data>:
   0:	b5b0      	push	{r4, r5, r7, lr}
   2:	b08a      	sub	sp, #40	@ 0x28
   4:	af00      	add	r7, sp, #0
   6:	200a      	movs	r0, #10
   8:	2100      	movs	r1, #0
   a:	60b8      	str	r0, [r7, #8]
   c:	60f9      	str	r1, [r7, #12]
   e:	2000      	movs	r0, #0
  10:	2100      	movs	r1, #0
  12:	6238      	str	r0, [r7, #32]
  14:	6279      	str	r1, [r7, #36]	@ 0x24
  16:	2001      	movs	r0, #1
  18:	2100      	movs	r1, #0
  1a:	61b8      	str	r0, [r7, #24]
  1c:	61f9      	str	r1, [r7, #28]
  1e:	2102      	movs	r1, #2
  20:	6179      	str	r1, [r7, #20]
  22:	e012      	b.n	0x4a
  24:	6a3c      	ldr	r4, [r7, #32]
  26:	6a7d      	ldr	r5, [r7, #36]	@ 0x24
  28:	69b8      	ldr	r0, [r7, #24]
  2a:	69f9      	ldr	r1, [r7, #28]
  2c:	1900      	adds	r0, r0, r4
  2e:	4169      	adcs	r1, r5
  30:	6038      	str	r0, [r7, #0]
  32:	6079      	str	r1, [r7, #4]
  34:	69b8      	ldr	r0, [r7, #24]
  36:	69f9      	ldr	r1, [r7, #28]
  38:	6238      	str	r0, [r7, #32]
  3a:	6279      	str	r1, [r7, #36]	@ 0x24
  3c:	6838      	ldr	r0, [r7, #0]
  3e:	6879      	ldr	r1, [r7, #4]
  40:	61b8      	str	r0, [r7, #24]
  42:	61f9      	str	r1, [r7, #28]
  44:	6979      	ldr	r1, [r7, #20]
  46:	3101      	adds	r1, #1
  48:	6179      	str	r1, [r7, #20]
  4a:	6979      	ldr	r1, [r7, #20]
  4c:	000a      	movs	r2, r1
  4e:	17c9      	asrs	r1, r1, #31
  50:	000b      	movs	r3, r1
  52:	68f9      	ldr	r1, [r7, #12]
  54:	4299      	cmp	r1, r3
  56:	db05      	blt.n	0x64
  58:	68f9      	ldr	r1, [r7, #12]
  5a:	4299      	cmp	r1, r3
  5c:	d1e2      	bne.n	0x24
  5e:	68b9      	ldr	r1, [r7, #8]
  60:	4291      	cmp	r1, r2
  62:	d2df      	bcs.n	0x24
  64:	69bb      	ldr	r3, [r7, #24]
  66:	0018      	movs	r0, r3
  68:	46bd      	mov	sp, r7
  6a:	b00a      	add	sp, #40	@ 0x28
  6c:	bcb0      	pop	{r4, r5, r7}
  6e:	bc02      	pop	{r1}
  70:	4708      	bx	r1
