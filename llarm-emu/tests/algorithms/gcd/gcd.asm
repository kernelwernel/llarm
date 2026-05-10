
gcd.bin:     file format binary


Disassembly of section .data:

00000000 <.data>:
   0:	e24dd008 	sub	sp, sp, #8
   4:	e3a0301e 	mov	r3, #30
   8:	e58d3004 	str	r3, [sp, #4]
   c:	e3a03014 	mov	r3, #20
  10:	e58d3000 	str	r3, [sp]
  14:	ea00000c 	b	0x4c
  18:	e59d2004 	ldr	r2, [sp, #4]
  1c:	e59d3000 	ldr	r3, [sp]
  20:	e1520003 	cmp	r2, r3
  24:	da000004 	ble	0x3c
  28:	e59d2004 	ldr	r2, [sp, #4]
  2c:	e59d3000 	ldr	r3, [sp]
  30:	e0423003 	sub	r3, r2, r3
  34:	e58d3004 	str	r3, [sp, #4]
  38:	ea000003 	b	0x4c
  3c:	e59d2000 	ldr	r2, [sp]
  40:	e59d3004 	ldr	r3, [sp, #4]
  44:	e0423003 	sub	r3, r2, r3
  48:	e58d3000 	str	r3, [sp]
  4c:	e59d2004 	ldr	r2, [sp, #4]
  50:	e59d3000 	ldr	r3, [sp]
  54:	e1520003 	cmp	r2, r3
  58:	1affffee 	bne	0x18
  5c:	e59d3004 	ldr	r3, [sp, #4]
  60:	e1a00003 	mov	r0, r3
  64:	e28dd008 	add	sp, sp, #8
  68:	e12fff1e 	bx	lr
