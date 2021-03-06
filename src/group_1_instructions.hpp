#ifndef group_1_instructions_hpp
#define group_1_instructions_hpp


// Group 1 Instructions
// 01oo oooo aaaa bbbb  iiii iiii iiii iiii

	// o:  opcode
	// a: rA
	// b: rB
	// i:  16-bit immediate value



#define LIST_OF_INSTR_G1_RA_RB_UIMM16__COLLECTION_0(INSTR_STUFF) \
\
/* rA = rB + (zero-extended imm) */ \
/* This instruction can affect N, V, Z, and C Flags. */ \
INSTR_STUFF(1, RaRbUImm16, Addi, "addi") \
\
/* rA = rB + (zero-extended imm) + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C Flags. */ \
INSTR_STUFF(1, RaRbUImm16, Adci, "adci") \
\
/* rA = rB - (zero-extended imm) */ \
/* This instruction can affect N, V, Z, and C Flags. */ \
INSTR_STUFF(1, RaRbUImm16, Subi, "subi") \
\
/* rA = rB + (~(zero-extended imm)) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C Flags. */ \
INSTR_STUFF(1, RaRbUImm16, Sbci, "sbci") \
\
\
\
/* rA = (zero-extended imm) - rB */ \
/* This instruction can affect N, V, Z, and C Flags. */ \
INSTR_STUFF(1, RaRbUImm16, Rsbi, "rsbi") \
\
/* rA = rB * (zero-extended imm) */ \
INSTR_STUFF(1, RaRbUImm16, Muli, "muli") \
\
/* rA = rB & (zero-extended imm) */ \
/* This instruction can affect the N and Z Flags. */ \
INSTR_STUFF(1, RaRbUImm16, Andi, "andi") \
\
/* rA = rB | (zero-extended imm) */ \
/* This instruction can affect the N and Z Flags. */ \
INSTR_STUFF(1, RaRbUImm16, Ori, "ori") \
\
\
\
/* rA = rB ^ (zero-extended imm) */ \
/* This instruction can affect the N and Z Flags. */ \
INSTR_STUFF(1, RaRbUImm16, Xori, "xori") \
\
/* Logical shift left */ \
/* rA = rB << (zero-extended imm) */ \
INSTR_STUFF(1, RaRbUImm16, Lsli, "lsli") \
\
/* Logical shift right */ \
INSTR_STUFF(1, RaRbUImm16, Lsri, "lsri") \
\
/* Arithmetic shift right */ \
INSTR_STUFF(1, RaRbUImm16, Asri, "asri") \
\
\
\
/* Rotate  left by (zero-extended imm) bits, then store result in rA. */ \
INSTR_STUFF(1, RaRbUImm16, Roli, "roli") \
\
/* Rotate  right by (zero-extended imm) bits, then store result in rA. */ \
INSTR_STUFF(1, RaRbUImm16, Rori, "rori") \
\
\
/* rA = rB + (zero-extended imm) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(1, RaRbUImm16, AddiDotF, "addi.f") \
\
/* rA = rB + (zero-extended imm) + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(1, RaRbUImm16, AdciDotF, "adci.f") \
\
\
\
/* rA = rB - (zero-extended imm) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(1, RaRbUImm16, SubiDotF, "subi.f") \
\
/* rA = rA + (~rB) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(1, RaRbUImm16, SbciDotF, "sbci.f") \
\
/* rA = rB - rA */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(1, RaRbUImm16, RsbiDotF, "rsbi.f") \
\
/* rA = rB * (zero-extended imm) */ \
INSTR_STUFF(1, RaRbUImm16, MuliDotF, "muli.f") \
\
\
\
/* rA = rB & (zero-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_STUFF(1, RaRbUImm16, AndiDotF, "andi.f") \
\
/* rA = rB | (zero-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_STUFF(1, RaRbUImm16, OriDotF, "ori.f") \
\
/* rA = rB ^ (zero-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_STUFF(1, RaRbUImm16, XoriDotF, "xori.f") \
\
/* Logical shift left */ \
/* rA = rB << (zero-extended imm) */ \
INSTR_STUFF(1, RaRbUImm16, LsliDotF, "lsli.f") \
\
\
\
/* Logical shift right */ \
INSTR_STUFF(1, RaRbUImm16, LsriDotF, "lsri.f") \
\
/* Arithmetic shift right */ \
INSTR_STUFF(1, RaRbUImm16, AsriDotF, "asri.f") \
\
/* Rotate rB left by (zero-extended imm) bits, then store result in */ \
/* rA. */ \
INSTR_STUFF(1, RaRbUImm16, RoliDotF, "roli.f") \
\
/* Rotate rB right by (zero-extended imm) bits, then store result in */ \
/* rA. */ \
INSTR_STUFF(1, RaRbUImm16, RoriDotF, "rori.f") \




#define LIST_OF_INSTR_G1_SIMM16__COLLECTION_0(INSTR_STUFF) \
/* Branch always,  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Bra, "bra") \
\
/* Branch never (effectively a NOP), */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Bnv, "bnv") \
\
/* Branch when Z == 0,  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Bne, "bne") \
\
/* Branch when Z == 1,  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Beq, "beq") \
\
\
\
/* Branch when C == 0 [unsigned less than],  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Bcc, "bcc") \
\
/* Branch when C == 1 [unsigned greater than or equal],  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Bcs, "bcs") \
\
/* Branch when (C == 0 or Z == 1) [unsigned less than or equal],  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Bls, "bls") \
\
/* Branch when (C == 1 and Z == 0) [unsigned greater than],  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Bhi, "bhi") \
\
\
\
/* Branch when N == 0,  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Bpl, "bpl") \
\
/* Branch when N == 1,  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Bmi, "bmi") \
\
/* Branch when V == 0,  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Bvc, "bvc") \
\
/* Branch when V == 1,  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Bvs, "bvs") \
\
\
\
/* Branch when N == V [signed greater than or equal],  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Bge, "bge") \
\
/* Branch when N != V [signed less than],  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Blt, "blt") \
\
/* Branch when (N == V and Z == 0) [signed greater than],  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Bgt, "bgt") \
\
/* Branch when (N != V or Z == 1) [signed less than or equal],  */ \
/* to ((pc when instruction starts + 4) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_STUFF(1, Branch, Ble, "ble")




#define LIST_OF_INSTR_G1_RA_RB_SIMM16__COLLECTION_0(INSTR_STUFF) \
/* rA = rB ^ (sign-extended imm) */ \
/* This instruction can affect the N and Z Flags. */ \
INSTR_STUFF(1, RaRbSImm16, Xorsi, "xorsi")

#define LIST_OF_INSTR_G1_RA_UIMM16__COLLECTION_0(INSTR_STUFF) \
/* rA bits {31, 30, 29, ..., 18, 17, 16} = 16-bit unsigned immediate */ \
/* value */ \
INSTR_STUFF(1, RaUImm16, Lui, "lui")

/* Reserved for future expansion. */
/* Reserved for future expansion. */



/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */

/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */

/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */

/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */


// Pseudo instruction:
//// Compare rB to (zero-extended imm)
//// temp = rB - (zero-extended imm)
//// Encoded like this:  subi.f r0, rB, imm
//// This instruction can affect N, V, Z, and C Flags.
//PSEUDO_INSTR_RB_IMM(cmpi)

// Pseudo instruction:
//// Compare rB to negated (zero-extended imm)
//// temp = rB - (-(zero-extended imm))
//// Encoded like this:  addi.f r0, rB, imm
//// This instruction can affect N, V, Z, and C Flags.
//PSEUDO_INSTR_RB_IMM(cmni)

// Pseudo instruction:
//// Compare reversed with immediate value
//// temp = (zero-extended imm) - rB
//// Encoded like this:  rsbi.f r0, rB, imm
//// This instruction can affect N, V, Z, and C Flags.
//PSEUDO_INSTR_RB_IMM(cmri)

// Pseudo instruction:
//// Copy Negated
//// rA = -rB
//// Encoded like this:  rsbi rA, rB, 0
//INSTR_RA_RB(cpn)

// Pseudo instruction:
//// Copy Complemented
//// rA = ~rB
//// Encoded like this:  xorsi rA, rB, -1
//INSTR_RA_RB(cpc)




// Pseudo instruction:
//// temp = rB & (zero-extended imm)
//// Encoded like this:  andi r0, rB, imm
//// This instruction can affect the N and Z Flags.
//PSEUDO_INSTR_RB_IMM(tsti,imm)

#define LIST_OF_GROUP_1_INSTRUCTIONS(INSTR_STUFF) \
LIST_OF_INSTR_G1_RA_RB_UIMM16__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G1_SIMM16__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G1_RA_RB_SIMM16__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G1_RA_UIMM16__COLLECTION_0(INSTR_STUFF) \

#endif		// group_1_instructions_hpp
