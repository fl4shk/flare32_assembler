#ifndef group_2_instructions_hpp
#define group_2_instructions_hpp

// Group 2 Instructions
// Non Block Moves Version:  
	// 10fo oooo aaaa bbbb  cccc iiii iiii iiii

	// f:  1 if can affect flags (and instruction type supports it), 0 if
	// flags unchanged.

	// o:  opcode
	// a: rA
	// b: rB
	// c: rC
	// i:  12-bit immediate value

// Block Moves Version (stmdb, ldmia, stmia, push, pop):  
	// 10fo oooo aaaa bbbb  cccc dddd xxxx 00ii

	// f:  1 if can affect flags (and instruction type supports it), 0 if
	// flags unchanged.

	// o:  opcode
	// a: rA
	// b: rB
	// c: rC
	// d: rD
	// x: rX
	// i:  2-bit immediate value


#define LIST_OF_INSTR_G2_LDST_RA_RB_RC_SIMM12__COLLECTION_0(ENC_GROUP, \
	ARGS, VARNAME, VALUE) \
/* Load 32-bit value from address (rB + rC + (sign-extended imm)) into 
rA. */ \
ENC_GROUP(2) ARGS(ldst_ra_rb_rc_simm12) VARNAME(Ldr) VALUE("ldr") \
\
/* Load zero-extended 16-bit value from address (rB + rC + (sign-extended
imm)) into rA. */ \
/* This zero-extends the value. */ \
ENC_GROUP(2) ARGS(ldst_ra_rb_rc_simm12) VARNAME(Ldh) VALUE("ldh") \
\
/* Load sign-extended 16-bit value from address (rB + rC + (sign-extended
imm)) into rA. */ \
/* This sign-extends the value. */ \
ENC_GROUP(2) ARGS(ldst_ra_rb_rc_simm12) VARNAME(Ldsh) VALUE("ldsh") \
\
/* Load zero-extended 8-bit value from address (rB + rC + (sign-extended
 imm)) into rA. */ \
/* This zero-extends the value. */ \
ENC_GROUP(2) ARGS(ldst_ra_rb_rc_simm12) VARNAME(Ldb) VALUE("ldb") \
\
\
\
/* Load sign-extended 8-bit value from address (rB + rC + (sign-extended
imm)) into rA. */ \
/* This sign-extends the value. */ \
ENC_GROUP(2) ARGS(ldst_ra_rb_rc_simm12) VARNAME(Ldsb) VALUE("ldsb") \
\
/* Store 32-bit value in rA to address (rB + rC + (sign-extended 
imm)). */ \
ENC_GROUP(2) ARGS(ldst_ra_rb_rc_simm12) VARNAME(Str) VALUE("str") \
\
/* Store low 16 bits of rA to address (rB + rC + (sign-extended imm)). */ \
ENC_GROUP(2) ARGS(ldst_ra_rb_rc_simm12) VARNAME(Sth) VALUE("sth") \
\
/* Store low 8 bits of rA to address (rB + rC + (sign-extended imm)). */ \
ENC_GROUP(2) ARGS(ldst_ra_rb_rc_simm12) VARNAME(Stb) VALUE("stb")


#define LIST_OF_INSTR_G2_RA_RB_RC__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
/* rA = rB + rC */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Add) VALUE("add") \
\
/* rA = rB + rC + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Adc) VALUE("adc") \
\
/* rA = rB - rC */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Sub) VALUE("sub") \
\
/* rA = rB + (~rC) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Sbc) VALUE("sbc") \
\
\
\
/* rA = rC - rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Rsb) VALUE("rsb") \
\
/* rA = rB * rC */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Mul) VALUE("mul") \
\
/* rA = rB & rC */ \
/* This instruction can affect the N and Z flags. */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(And) VALUE("and") \
\
/* rA = rB | rC */ \
/* This instruction can affect the N and Z flags. */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Or) VALUE("or") \
\
\
\
/* rA = rB ^ rC */ \
/* This instruction can affect the N and Z flags. */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Xor) VALUE("xor") \
\
/* Logical shift left */ \
/* rA = rB << rC */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Lsl) VALUE("lsl") \
\
/* Logical shift right */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Lsr) VALUE("lsr") \
\
/* Arithmetic shift right */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Asr) VALUE("asr") \
\
\
\
/* Rotate rC left by rC bits, then store result in rA. */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Rol) VALUE("rol") \
\
/* Rotate rC right by rC bits, then store result in rA. */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Ror) VALUE("ror") \
\
/* Fused multiply-add */ \
/* rA = rA + (rB * rC) */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Fma) VALUE("fma") \
\
/* Copy rC to rA and to rB */ \
/* If rA is the same register as rB, then the  */ \
/* register will only be written once. */ \
ENC_GROUP(2) ARGS(ra_rb_rc) VARNAME(Cpyp) VALUE("cpyp")


#define LIST_OF_INSTR_G2_LDST_BLOCK_1_TO_4__COLLECTION_0(ENC_GROUP, ARGS, \
	VARNAME, VALUE) \
/* STore Multiple, Decrement Before */ \
/* Note that this instruction takes multiple forms */ \
ENC_GROUP(2) ARGS(ldst_block_1_to_4) VARNAME(Stmdb) VALUE("stmdb") \
\
\
/* LoaD Multiple, Increment After */ \
/* Note that this instruction takes multiple forms */ \
ENC_GROUP(2) ARGS(ldst_block_1_to_4) VARNAME(Ldmia) VALUE("ldmia") \
\
\
/* STore Multiple, Increment After */ \
/* Note that this instruction takes multiple forms */ \
ENC_GROUP(2) ARGS(ldst_block_1_to_4) VARNAME(Stmia) VALUE("stmia")



#define LIST_OF_INSTR_G2_NO_ARGS__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
/* ENable Interrupts */ \
ENC_GROUP(2) ARGS(no_args) VARNAME(Eni) VALUE("eni") \
\
\
\
/* DIsable Interrupts */ \
ENC_GROUP(2) ARGS(no_args) VARNAME(Dii) VALUE("dii") \
\
/* Set the PC to interrupt RETurn address and enable Interrupts */ \
ENC_GROUP(2) ARGS(no_args) VARNAME(Reti) VALUE("reti")


#define LIST_OF_INSTR_G2_IRA__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
/* Set the PC to the Interrupt Return Address, but DON'T enable */ \
/* interrupts */ \
ENC_GROUP(2) ARGS(ira) VARNAME(Jump) VALUE("jump")

/* Reserved for future expansion. */ \





// Pseudo instruction:
//// Load 32-bit value from address (rB + rC) into rA.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldr,rB,rC,0)
//INSTR_LDST_RA_RB_RC(ldrx)

// Pseudo instruction:
//// Load zero-extended 16-bit value from address (rB + rC) into rA.
//// This zero-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldh,rB,rC,0)
//INSTR_LDST_RA_RB_RC(ldhx)

// Pseudo instruction:
//// Load sign-extended 16-bit value from address (rB + rC) into rA.
//// This sign-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldsh,rB,rC,0)
//INSTR_LDST_RA_RB_RC(ldshx)

// Pseudo instruction:
//// Load zero-extended 8-bit value from address (rB + rC) into rA.
//// This zero-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldb,rB,rC,0)
//INSTR_LDST_RA_RB_RC(ldbx)



// Pseudo instruction:
//// Load sign-extended 8-bit value from address (rB + rC) into rA.
//// This sign-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldsb,rB,rC,0)
//INSTR_LDST_RA_RB_RC(ldsbx)

// Pseudo instruction:
//// Store 32-bit value in rA to address (rB + rC).
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(str,rB,rC,0)
//INSTR_LDST_RA_RB_RC(strx)

// Pseudo instruction:
//// Store low 16 bits of rA to address (rB + rC).
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(sth,rB,rC,0)
//INSTR_LDST_RA_RB_RC(sthx)

// Pseudo instruction:
//// Store low 8 bits of rA to address (rB + rC).
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(stb,rB,rC,0)
//INSTR_LDST_RA_RB_RC(stbx)



// Pseudo instruction:
//// Load 32-bit value from address (rB + (sign-extended imm)) into rA.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldr,rB,r0)
//INSTR_LDST_RA_RB_IMM(ldrxi)

// Pseudo instruction:
//// Load zero-extended 16-bit value from address (rB + (sign-extended imm)) into rA.
//// This zero-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldh,rB,r0)
//INSTR_LDST_RA_RB_IMM(ldhxi)

// Pseudo instruction:
//// Load sign-extended 16-bit value from address (rB + (sign-extended imm)) into rA.
//// This sign-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldsh,rB,r0)
//INSTR_LDST_RA_RB_IMM(ldshxi)

// Pseudo instruction:
//// Load zero-extended 8-bit value from address (rB + (sign-extended imm)) into rA.
//// This zero-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldb,rB,r0)
//INSTR_LDST_RA_RB_IMM(ldbxi)



// Pseudo instruction:
//// Load sign-extended 8-bit value from address (rB + (sign-extended imm)) into rA.
//// This sign-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldsb,rB,r0)
//INSTR_LDST_RA_RB_IMM(ldsbxi)

// Pseudo instruction:
//// Store 32-bit value in rA to address (rB + (sign-extended imm)).
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(str,rB,r0)
//INSTR_LDST_RA_RB_IMM(strxi)

// Pseudo instruction:
//// Store low 16 bits of rA to address (rB + (sign-extended imm)).
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(sth,rB,r0)
//INSTR_LDST_RA_RB_IMM(sthxi)

// Pseudo instruction:
//// Store low 8 bits of rA to address (rB + (sign-extended imm)).
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(stb,rB,r0)
//INSTR_LDST_RA_RB_IMM(stbxi)



// Pseudo instruction:
//// temp = rB - rC
//// This instruction can affect N, V, Z, and C flags.
//// Encoded like this:  sub.f r0, rB, rC
//PSEUDO_INSTR_RB_RC(cmp)

// Pseudo instruction:
//// temp = rB - (-rC)
//// This instruction can affect N, V, Z, and C flags.
//// Encoded like this:  add.f r0, rB, rC
//PSEUDO_INSTR_RB_RC(cmn)

// Pseudo instruction:
//// temp = rC - rB
//// This instruction can affect N, V, Z, and C flags.
//// Encoded like this:  rsb.f r0, rB, rC
//PSEUDO_INSTR_RB_RC(cmr)

// Pseudo instruction:
//// temp = rB & rC
//// Encoded like this:  and.f r0, rB, rC
//// This instruction can affect the N and Z flags.
//PSEUDO_INSTR_RB_RC(tst)




// Pseudo instruction:
// Pop
// Note that this instruction takes multiple forms
	// Syntax:  pop rA

// Pseudo instruction:
// Push
// Note that this instruction takes multiple forms
	// Syntax:  push rA

#define LIST_OF_GROUP_2_INSTRUCTIONS(ENC_GROUP, ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G2_LDST_RA_RB_RC_SIMM12__COLLECTION_0(ENC_GROUP, ARGS, \
	VARNAME, VALUE) \
LIST_OF_INSTR_G2_RA_RB_RC__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G2_LDST_BLOCK_1_TO_4__COLLECTION_0(ENC_GROUP, ARGS, \
	VARNAME, VALUE) \
LIST_OF_INSTR_G2_NO_ARGS__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G2_IRA__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, VALUE)

#endif		// group_2_instructions_hpp
