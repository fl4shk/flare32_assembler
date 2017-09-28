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
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Addi) VALUE("addi") \
\
/* rA = rB + (zero-extended imm) + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Adci) VALUE("adci") \
\
/* rA = rB - (zero-extended imm) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Subi) VALUE("subi") \
\
/* rA = rB + (~(zero-extended imm)) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Sbci) VALUE("sbci") \
\
\
\
/* rA = (zero-extended imm) - rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Rsbi) VALUE("rsbi") \
\
/* rA = rB * (zero-extended imm) */ \
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Muli) VALUE("muli") \
\
/* rA = rB & (zero-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Andi) VALUE("andi") \
\
/* rA = rB | (zero-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Ori) VALUE("ori") \
\
\
\
/* rA = rB ^ (zero-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Xori) VALUE("xori") \
\
/* Logical shift left */ \
/* rA = rB << (zero-extended imm) */ \
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Lsli) VALUE("lsli") \
\
/* Logical shift right */ \
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Lsri) VALUE("lsri") \
\
/* Arithmetic shift right */ \
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Asri) VALUE("asri") \
\
\
\
/* Rotate  left by (zero-extended imm) bits, then store result in rA. */ \
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Roli) VALUE("roli") \
\
/* Rotate  right by (zero-extended imm) bits, then store result in rA. */ \
ENC_GROUP(1) ARGS(ra_rb_uimm16) VARNAME(Rori) VALUE("rori")

#define LIST_OF_INSTR_G1_SIMM16__COLLECTION_0(ENC_GROUP, ARGS, \
	VARNAME, VALUE) \
/* Branch always,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Bra) VALUE("bra") \
\
/* Branch never (effectively a NOP), */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Bnv) VALUE("bnv") \
\
\
\
/* Branch when Z == 0,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Bne) VALUE("bne") \
\
/* Branch when Z == 1,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Beq) VALUE("beq") \
\
/* Branch when C == 0 [unsigned less than],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Bcc) VALUE("bcc") \
\
/* Branch when C == 1 [unsigned greater than or equal],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Bcs) VALUE("bcs") \
\
\
\
/* Branch when (C == 0 or Z == 1) [unsigned less than or equal],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Bls) VALUE("bls") \
\
/* Branch when (C == 1 and Z == 0) [unsigned greater than],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Bhi) VALUE("bhi") \
\
/* Branch when N == 0,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Bpl) VALUE("bpl") \
\
/* Branch when N == 1,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Bmi) VALUE("bmi") \
\
\
\
/* Branch when V == 0,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Bvc) VALUE("bvc") \
\
/* Branch when V == 1,  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Bvs) VALUE("bvs") \
\
/* Branch when N == V [signed greater than or equal],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Bge) VALUE("bge") \
\
/* Branch when N != V [signed less than],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Blt) VALUE("blt") \
\
\
\
/* Branch when (N == V and Z == 0) [signed greater than],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Bgt) VALUE("bgt") \
\
/* Branch when (N != V or Z == 1) [signed less than or equal],  */ \
/* to ((pc when instruction starts) */ \
/* + (sign-extended 16-bit immediate value)) */ \
ENC_GROUP(1) ARGS(simm16) VARNAME(Ble) VALUE("ble")


#define LIST_OF_INSTR_G1_RA_RB_SIMM16__COLLECTION_0(ENC_GROUP, ARGS, \
	VARNAME, VALUE) \
/* rA = rB ^ (sign-extended imm) */ \
/* This instruction can affect the N and Z flags. */ \
ENC_GROUP(1) ARGS(ra_rb_simm16) VARNAME(Xorsi) VALUE("xorsi")

#define LIST_OF_INSTR_G1_RA_UIMM16__COLLECTION_0(ENC_GROUP, ARGS, \
	VARNAME, VALUE) \
/* rA bits {31, 30, 29, ..., 18, 17, 16} = 16-bit unsigned immediate  \
value */ \
ENC_GROUP(1) ARGS(ra_uimm16) VARNAME(Lui) VALUE("lui")



// Pseudo instruction:
//// Compare rB to (zero-extended imm)
//// temp = rB - (zero-extended imm)
//// Encoded like this:  subi.f r0, rB, imm
//// This instruction can affect N, V, Z, and C flags.
//PSEUDO_INSTR_RB_IMM(cmpi)

// Pseudo instruction:
//// Compare rB to negated (zero-extended imm)
//// temp = rB - (-(zero-extended imm))
//// Encoded like this:  addi.f r0, rB, imm
//// This instruction can affect N, V, Z, and C flags.
//PSEUDO_INSTR_RB_IMM(cmni)

// Pseudo instruction:
//// Compare reversed with immediate value
//// temp = (zero-extended imm) - rB
//// Encoded like this:  rsbi.f r0, rB, imm
//// This instruction can affect N, V, Z, and C flags.
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
//// This instruction can affect the N and Z flags.
//PSEUDO_INSTR_RB_IMM(tsti,imm)

#define LIST_OF_GROUP_1_INSTRUCTIONS(ENC_GROUP, ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G1_RA_RB_UIMM16__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
LIST_OF_INSTR_G1_SIMM16__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G1_RA_RB_SIMM16__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
LIST_OF_INSTR_G1_RA_UIMM16__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, VALUE) \

#endif		// group_1_instructions_hpp
