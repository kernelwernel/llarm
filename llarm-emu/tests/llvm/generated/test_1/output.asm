
bin.elf:	file format elf32-littlearm

Disassembly of section .text:

00000000 <autogen_SD3264627838>:
       0: e1a01000     	mov	r1, r0
       4: e3a00000     	mov	r0, #0
       8: e5810004     	str	r0, [r1, #0x4]
       c: e59f200c     	ldr	r2, [pc, #0xc]          @ 0x20 <autogen_SD3264627838+0x20>
      10: e5812000     	str	r2, [r1]
      14: e5810000     	str	r0, [r1]
      18: eaffffff     	b	0x1c <autogen_SD3264627838+0x1c> @ imm = #-0x4
      1c: eafffffe     	b	0x1c <autogen_SD3264627838+0x1c> @ imm = #-0x8
      20: eb 0a 01 00  	.word	0x00010aeb

Disassembly of section .ARM.exidx:

00010024 <.ARM.exidx>:
   10024: 7ffeffdc     	svcvc	#0xfeffdc
   10028: 00000001     	andeq	r0, r0, r1
   1002c: 7ffefff8     	svcvc	#0xfefff8
   10030: 00000001     	andeq	r0, r0, r1

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
       0: 00003941     	andeq	r3, r0, r1, asr #18
       4: 61656100     	<unknown>
       8: 01006962     	<unknown>
       c: 0000002f     	andeq	r0, r0, pc, lsr #32
      10: 302e3243     	eorlo	r3, lr, r3, asr #4
      14: 61050039     	<unknown>
      18: 74376d72     	ldrtvc	r6, [r7], #-3442
      1c: 00696d64     	rsbeq	r6, r9, r4, ror #26
      20: 01080206     	<unknown>
      24: 000e0109     	andeq	r0, lr, r9, lsl #2
      28: 01140111     	tsteq	r4, r1, lsl r1
      2c: 03170015     	tsteq	r7, #21
      30: 01190118     	tsteq	r9, r8, lsl r1
      34: 0022051e     	eoreq	r0, r2, lr, lsl r5
      38: 26 01        	<unknown>

Disassembly of section .comment:

00000000 <.comment>:
       0: 6b6e694c     	blvs	0x1b9a538 <.ARM.exidx+0x1b8a514> @ imm = #0x1b9a530
       4: 203a7265     	eorshs	r7, r10, r5, ror #4
       8: 20444c4c     	subhs	r4, r4, r12, asr #24
       c: 312e3931     	<unknown>
      10: 2e 37 00     	<unknown>

Disassembly of section .symtab:

00000000 <.symtab>:
		...
      10: 00000001     	andeq	r0, r0, r1
		...
      1c: fff10004     	<unknown>
      20: 0000000c     	andeq	r0, r0, r12
		...
      2c: 00010000     	andeq	r0, r1, r0
      30: 0000000f     	andeq	r0, r0, pc
      34: 00000020     	andeq	r0, r0, r0, lsr #32
      38: 00000000     	andeq	r0, r0, r0
      3c: 00010000     	andeq	r0, r1, r0
      40: 00000012     	andeq	r0, r0, r2, lsl r0
      44: 00000000     	andeq	r0, r0, r0
      48: 00000024     	andeq	r0, r0, r4, lsr #32
      4c: 00010012     	andeq	r0, r1, r2, lsl r0

Disassembly of section .shstrtab:

00000000 <.shstrtab>:
       0: 65742e00     	ldrbvs	r2, [r4, #-0xe00]!
       4: 2e007478     	mcrhs	p4, #0x0, r7, c0, c8, #0x3
       8: 2e4d5241     	cdphs	p2, #0x4, c5, c13, c1, #0x2
       c: 64697865     	strbtvs	r7, [r9], #-2149
      10: 412e0078     	<unknown>
      14: 612e4d52     	qsubvs	r4, r2, lr
      18: 69727474     	ldmdbvs	r2!, {r2, r4, r5, r6, r10, r12, sp, lr} ^
      1c: 65747562     	ldrbvs	r7, [r4, #-0x562]!
      20: 632e0073     	<unknown>
      24: 656d6d6f     	strbvs	r6, [sp, #-0xd6f]!
      28: 2e00746e     	cdphs	p4, #0x0, c7, c0, c14, #0x3
      2c: 746d7973     	strbtvc	r7, [sp], #-2419
      30: 2e006261     	cdphs	p2, #0x0, c6, c0, c1, #0x3
      34: 74736873     	ldrbtvc	r6, [r3], #-2163
      38: 62617472     	rsbvs	r7, r1, #1912602624
      3c: 74732e00     	ldrbtvc	r2, [r3], #-3584
      40: 62617472     	rsbvs	r7, r1, #1912602624
      44: 00           	<unknown>

Disassembly of section .strtab:

00000000 <.strtab>:
       0: 74756100     	ldrbtvc	r6, [r5], #-256
       4: 6e65676f     	cdpvs	p7, #0x6, c6, c5, c15, #0x3
       8: 0063622e     	rsbeq	r6, r3, lr, lsr #4
       c: 24006124     	strhs	r6, [r0], #-292
      10: 75610064     	strbvc	r0, [r1, #-0x64]!
      14: 65676f74     	strbvs	r6, [r7, #-0xf74]!
      18: 44535f6e     	ldrbmi	r5, [r3], #-3950
      1c: 34363233     	ldrtlo	r3, [r6], #-563
      20: 38373236     	ldmdalo	r7!, {r1, r2, r4, r5, r9, r12, sp}
      24: 33 38 00     	<unknown>
