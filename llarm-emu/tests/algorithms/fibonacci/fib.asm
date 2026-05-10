
fib.bin:     file format binary


Disassembly of section .data:

00000000 <.data>:
   0:	e92d00f0 	push	{r4, r5, r6, r7}
   4:	e24dd028 	sub	sp, sp, #40	@ 0x28
   8:	e3a0200a 	mov	r2, #10
   c:	e3a03000 	mov	r3, #0
  10:	e58d2008 	str	r2, [sp, #8]
  14:	e58d300c 	str	r3, [sp, #12]
  18:	e3a02000 	mov	r2, #0
  1c:	e3a03000 	mov	r3, #0
  20:	e58d2020 	str	r2, [sp, #32]
  24:	e58d3024 	str	r3, [sp, #36]	@ 0x24
  28:	e3a02001 	mov	r2, #1
  2c:	e3a03000 	mov	r3, #0
  30:	e58d2018 	str	r2, [sp, #24]
  34:	e58d301c 	str	r3, [sp, #28]
  38:	e3a03002 	mov	r3, #2
  3c:	e58d3014 	str	r3, [sp, #20]
  40:	ea000010 	b	0x88
  44:	e28d1020 	add	r1, sp, #32
  48:	e8910003 	ldm	r1, {r0, r1}
  4c:	e28d3018 	add	r3, sp, #24
  50:	e893000c 	ldm	r3, {r2, r3}
  54:	e0906002 	adds	r6, r0, r2
  58:	e0a17003 	adc	r7, r1, r3
  5c:	e88d00c0 	stm	sp, {r6, r7}
  60:	e28d3018 	add	r3, sp, #24
  64:	e893000c 	ldm	r3, {r2, r3}
  68:	e58d2020 	str	r2, [sp, #32]
  6c:	e58d3024 	str	r3, [sp, #36]	@ 0x24
  70:	e89d000c 	ldm	sp, {r2, r3}
  74:	e58d2018 	str	r2, [sp, #24]
  78:	e58d301c 	str	r3, [sp, #28]
  7c:	e59d3014 	ldr	r3, [sp, #20]
  80:	e2833001 	add	r3, r3, #1
  84:	e58d3014 	str	r3, [sp, #20]
  88:	e59d3014 	ldr	r3, [sp, #20]
  8c:	e1a02fc3 	asr	r2, r3, #31
  90:	e1a04003 	mov	r4, r3
  94:	e1a05002 	mov	r5, r2
  98:	e28d3008 	add	r3, sp, #8
  9c:	e893000c 	ldm	r3, {r2, r3}
  a0:	e1520004 	cmp	r2, r4
  a4:	e0d33005 	sbcs	r3, r3, r5
  a8:	aaffffe5 	bge	0x44
  ac:	e59d3018 	ldr	r3, [sp, #24]
  b0:	e1a00003 	mov	r0, r3
  b4:	e28dd028 	add	sp, sp, #40	@ 0x28
  b8:	e8bd00f0 	pop	{r4, r5, r6, r7}
  bc:	e12fff1e 	bx	lr