#ifndef group_1_instructions_hpp
#define group_1_instructions_hpp


// Group 1 Instructions
// 01fo oooo aaaa bbbb  iiii iiii iiii iiii

	// f:  1 if can affect flags (and instruction type supports it), 0 if
	// flags unchanged.

	// o:  opcode
	// a: rA
	// b: rB
	// i:  16-bit immediate value



#define LIST_OF_INSTR_G1_RA_RB_UIMM16__COLLECTION_0(ENC_GROUP, ARGS, \
	VARNAME, VALUE) \
\
/* rA = rB + (zero-extended imm) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_IMM(addi,imm) \
\
/* rA = rB + (zero-extended imm) + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_IMM(adci,imm) \
\
/* rA = rB - (zero-extended imm) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_IMM(subi,imm) \
\
/* rA = rB + (~(zero-extended imm)) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_IMM(sbci,imm) \
\
\
\
/* rA = (zero-extended imm) - rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_IMM(rsbi,imm) \
\
/* rA = rB * (zero-extended imm) */ \
INSTR_RA_RB_IMM(muli,imm) \
\
/* rA = rB & (zero-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_IMM(andi,imm) \
\
/* rA = rB | (zero-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_IMM(ori,imm) \
\
\
\
/* rA = rB ^ (zero-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_IMM(xori,imm) \
\
/* Logical shift left */ \
/* rA = rB << (zero-extended imm) */ \
INSTR_RA_RB_IMM(lsli,imm) \
\
/* Logical shift right */ \
INSTR_RA_RB_IMM(lsri,imm) \
\
/* Arithmetic shift right */ \
INSTR_RA_RB_IMM(asri,imm) \
\
\
\
/* Rotate  left by (zero-extended imm) bits, then store result in rA. */ \
INSTR_RA_RB_IMM(roli,imm) \
\
/* Rotate  right by (zero-extended imm) bits, then store result in rA. */ \
INSTR_RA_RB_IMM(rori,imm)

#define LIST_OF_INSTR_G1_SIMM16__COLLECTION_0(ENC_GROUP, ARGS, \
	VARNAME, VALUE) \
/* Branch always,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bra,imm) \
\
/* Branch never (effectively a NOP), */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bnv,imm) \
\
\
\
/* Branch when Z == 0,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bne,imm) \
\
/* Branch when Z == 1,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(beq,imm) \
\
/* Branch when C == 0 [unsigned less than],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bcc,imm) \
\
/* Branch when C == 1 [unsigned greater than or equal],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bcs,imm) \
\
\
\
/* Branch when (C == 0 or Z == 1) [unsigned less than or equal],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bls,imm) \
\
/* Branch when (C == 1 and Z == 0) [unsigned greater than],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bhi,imm) \
\
/* Branch when N == 0,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bpl,imm) \
\
/* Branch when N == 1,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bmi,imm) \
\
\
\
/* Branch when V == 0,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bvc,imm) \
\
/* Branch when V == 1,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bvs,imm) \
\
/* Branch when N == V [signed greater than or equal],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bge,imm) \
\
/* Branch when N != V [signed less than],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(blt,imm) \
\
\
\
/* Branch when (N == V and Z == 0) [signed greater than],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bgt,imm) \
\
/* Branch when (N != V or Z == 1) [signed less than or equal],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(ble,imm)


#define LIST_OF_INSTR_G1_RA_RB_SIMM16__COLLECTION_0(ENC_GROUP, ARGS, \
	VARNAME, VALUE) \
/* rA = rB ^ (sign-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_IMM(xorsi,imm)

#define LIST_OF_INSTR_G1_RA_UIMM16__COLLECTION_0(ENC_GROUP, ARGS, \
	VARNAME, VALUE) \
/* rA bits {31, 30, 29, ..., 18, 17, 16} = 16-bit unsigned immediate  \
value */ \
INSTR_RA_IMM(lui,imm)



// Pseudo instruction:
//// Compare rB to (zero-extended imm)
//// temp = rB - (zero-extended imm)
//// Encoded like this:  subi.f r0, rB, imm
//// This instruction can affect N, V, Z, and C flags.
//PSEUDO_INSTR_RB_IMM(cmpi,imm)

// Pseudo instruction:
//// Compare rB to negated (zero-extended imm)
//// temp = rB - (-(zero-extended imm))
//// Encoded like this:  addi.f r0, rB, imm
//// This instruction can affect N, V, Z, and C flags.
//PSEUDO_INSTR_RB_IMM(cmni,imm)

// Pseudo instruction:
//// Compare reversed with immediate value
//// temp = (zero-extended imm) - rB
//// Encoded like this:  rsbi.f r0, rB, imm
//// This instruction can affect N, V, Z, and C flags.
//PSEUDO_INSTR_RB_IMM(cmri,imm)

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
//// This instruction can affect the N and Z flags.
//PSEUDO_INSTR_RB_IMM(tsti,imm)

#endif		// group_1_instructions_hpp
