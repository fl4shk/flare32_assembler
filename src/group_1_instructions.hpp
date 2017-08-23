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

#define LIST_OF_INSTR_G1_RA_RB_IMM__COLLECTION_0(ARGS, VARNAME, VALUE) \
/* rA = rB + (zero-extended imm) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_IMM(addi) \
\
/* rA = rB + (zero-extended imm) + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_IMM(adci) \
\
/* rA = rB - (zero-extended imm) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_IMM(subi) \
\
/* rA = rB + (~(zero-extended imm)) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_IMM(sbci) \
\
\
\
/* rA = (zero-extended imm) - rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_IMM(rsbi) \
\
/* rA = rB * (zero-extended imm) */ \
INSTR_RA_RB_IMM(muli) \
\
/* rA = rB & (zero-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_IMM(andi) \
\
/* rA = rB | (zero-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_IMM(ori) \
\
\
\
/* rA = rB ^ (zero-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_IMM(xori) \
\
/* Logical shift left */ \
/* rA = rB << (zero-extended imm) */ \
INSTR_RA_RB_IMM(lsli) \
\
/* Logical shift right */ \
INSTR_RA_RB_IMM(lsri) \
\
/* Arithmetic shift right */ \
INSTR_RA_RB_IMM(asri) \
\
\
\
/* Rotate  left by (zero-extended imm) bits, then store result in rA. */ \
INSTR_RA_RB_IMM(roli) \
\
/* Rotate  right by (zero-extended imm) bits, then store result in rA. */ \
INSTR_RA_RB_IMM(rori) \


#define LIST_OF_INSTR_G1_IMM__COLLECTION_0(ARGS, VARNAME, VALUE) \
/* Branch always,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bra) \
\
/* Branch never (effectively a NOP), */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bnv) \
\
\
\
/* Branch when Z == 0,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bne) \
\
/* Branch when Z == 1,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(beq) \
\
/* Branch when C == 0 [unsigned less than],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bcc) \
\
/* Branch when C == 1 [unsigned greater than or equal],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bcs) \
\
\
\
/* Branch when (C == 0 or Z == 1) [unsigned less than or equal],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bls) \
\
/* Branch when (C == 1 and Z == 0) [unsigned greater than],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bhi) \
\
/* Branch when N == 0,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bpl) \
\
/* Branch when N == 1,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bmi) \
\
\
\
/* Branch when V == 0,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bvc) \
\
/* Branch when V == 1,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bvs) \
\
/* Branch when N == V [signed greater than or equal],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bge) \
\
/* Branch when N != V [signed less than],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(blt) \
\
\
\
/* Branch when (N == V and Z == 0) [signed greater than],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(bgt) \
\
/* Branch when (N != V or Z == 1) [signed less than or equal],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
INSTR_IMM(ble) \


#define LIST_OF_INSTR_G1_RA_RB_SIMM__COLLECTION_1(ARGS, VARNAME, VALUE) \
/* rA = rB ^ (sign-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_IMM(xorsi)

/* Reserved for future expansion. */


#endif		// group_1_instructions_hpp
