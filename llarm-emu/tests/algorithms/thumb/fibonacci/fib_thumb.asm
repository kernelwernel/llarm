
fib.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <main>:
   0:	e92d 03b0 	stmdb	sp!, {r4, r5, r7, r8, r9}
   4:	b08b      	sub	sp, #44	@ 0x2c
   6:	af00      	add	r7, sp, #0
   8:	f04f 020a 	mov.w	r2, #10
   c:	f04f 0300 	mov.w	r3, #0
  10:	e9c7 2302 	strd	r2, r3, [r7, #8]
  14:	f04f 0200 	mov.w	r2, #0
  18:	f04f 0300 	mov.w	r3, #0
  1c:	e9c7 2308 	strd	r2, r3, [r7, #32]
  20:	f04f 0201 	mov.w	r2, #1
  24:	f04f 0300 	mov.w	r3, #0
  28:	e9c7 2306 	strd	r2, r3, [r7, #24]
  2c:	2302      	movs	r3, #2
  2e:	617b      	str	r3, [r7, #20]
  30:	e014      	b.n	5c <main+0x5c>
  32:	e9d7 0108 	ldrd	r0, r1, [r7, #32]
  36:	e9d7 2306 	ldrd	r2, r3, [r7, #24]
  3a:	eb10 0802 	adds.w	r8, r0, r2
  3e:	eb41 0903 	adc.w	r9, r1, r3
  42:	e9c7 8900 	strd	r8, r9, [r7]
  46:	e9d7 2306 	ldrd	r2, r3, [r7, #24]
  4a:	e9c7 2308 	strd	r2, r3, [r7, #32]
  4e:	e9d7 2300 	ldrd	r2, r3, [r7]
  52:	e9c7 2306 	strd	r2, r3, [r7, #24]
  56:	697b      	ldr	r3, [r7, #20]
  58:	3301      	adds	r3, #1
  5a:	617b      	str	r3, [r7, #20]
  5c:	697b      	ldr	r3, [r7, #20]
  5e:	17da      	asrs	r2, r3, #31
  60:	461c      	mov	r4, r3
  62:	4615      	mov	r5, r2
  64:	e9d7 2302 	ldrd	r2, r3, [r7, #8]
  68:	42a2      	cmp	r2, r4
  6a:	41ab      	sbcs	r3, r5
  6c:	dae1      	bge.n	32 <main+0x32>
  6e:	69bb      	ldr	r3, [r7, #24]
  70:	4618      	mov	r0, r3
  72:	372c      	adds	r7, #44	@ 0x2c
  74:	46bd      	mov	sp, r7
  76:	e8bd 03b0 	ldmia.w	sp!, {r4, r5, r7, r8, r9}
  7a:	4770      	bx	lr
