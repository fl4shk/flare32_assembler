#ifndef group_0_instructions_hpp
#define group_0_instructions_hpp


// Group 0 Instructions
// 00fo oooo aaaa bbbb

	// f:  1 if can affect flags (and instruction type supports it), 0 if
	// flags unchanged.

	// o:  opcode
	// a: rA (destination register usually)
	// b: rB

#define LIST_OF_INSTR_G0_LDST_RA_RB__COLLECTION_0(ENC_GROUP, ARGS, \
	VARNAME, VALUE) \
/* Load 32-bit value from address rB into rA. */ \
ENC_GROUP(0) ARGS(ldst_ra_rb) VARNAME(Ldr) VALUE("ldr") \
\
/* Load zero-extended 16-bit value from address rB into rA. */ \
/* This zero-extends the value. */ \
ENC_GROUP(0) ARGS(ldst_ra_rb) VARNAME(Ldh) VALUE("ldh") \
\
/* Load sign-extended 16-bit value from address rB into rA. */ \
/* This sign-extends the value. */ \
ENC_GROUP(0) ARGS(ldst_ra_rb) VARNAME(Ldsh) VALUE("ldsh") \
\
/* Load zero-extended 8-bit value from address rB into rA. */ \
/* This zero-extends the value. */ \
ENC_GROUP(0) ARGS(ldst_ra_rb) VARNAME(Ldb) VALUE("ldb") \
\
\
\
/* Load sign-extended 8-bit value from address rB into rA. */ \
/* This sign-extends the value. */ \
ENC_GROUP(0) ARGS(ldst_ra_rb) VARNAME(Ldsb) VALUE("ldsb") \
\
/* Store 32-bit value in rA to address rB. */ \
ENC_GROUP(0) ARGS(ldst_ra_rb) VARNAME(Str) VALUE("str") \
\
/* Store low 16 bits of rA to address rB. */ \
ENC_GROUP(0) ARGS(ldst_ra_rb) VARNAME(Sth) VALUE("sth") \
\
/* Store low 8 bits of rA to address rB. */ \
ENC_GROUP(0) ARGS(ldst_ra_rb) VARNAME(Stb) VALUE("stb")



#define LIST_OF_INSTR_G0_RA_RB__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
/* rA = rA + rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Add) VALUE("add") \
\
/* rA = rA + rB + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Adc) VALUE("adc") \
\
/* rA = rA - rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Sub) VALUE("sub") \
\
/* rA = rA + (~rB) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Sbc) VALUE("sbc") \
\
\
\
/* rA = rB - rA */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Rsb) VALUE("rsb") \
\
/* rA = rA * rB */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Mul) VALUE("mul") \
\
/* rA = rA & rB */ \
/* This instruction can affect the N and Z flags. */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(And) VALUE("and") \
\
/* rA = rA | rB */ \
/* This instruction can affect the N and Z flags. */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Or) VALUE("or") \
\
\
\
/* rA = rA ^ rB */ \
/* This instruction can affect the N and Z flags. */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Xor) VALUE("xor") \
\
/* Logical shift left */ \
/* rA = rA << rB */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Lsl) VALUE("lsl") \
\
/* Logical shift right */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Lsr) VALUE("lsr") \
\
/* Arithmetic shift right */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Asr) VALUE("asr") \
\
\
\
/* Rotate rA left by rB bits, then store result in rA. */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Rol) VALUE("rol") \
\
/* Rotate rA right by rB bits, then store result in rA. */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Ror) VALUE("ror") \
\
/* Rotate rB left (THROUGH carry) by 1 bit, then store result in rA. */ \
/* This instruction can only affect the C flag. */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Rlc) VALUE("rlc") \
\
/* Rotate rB right (THROUGH carry) by 1 bit, then store result in rA. */ \
/* This instruction can only affect the C flag. */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Rrc) VALUE("rrc")



#define LIST_OF_INSTR_G0_IRA_RA__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
/* Copy rA to the Interrupt Return Address */ \
ENC_GROUP(0) ARGS(ira_ra) VARNAME(Cpy) VALUE("cpy")

#define LIST_OF_INSTR_G0_RA_IRA__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE)\
/* Copy the Interrupt Return Address to rA */ \
ENC_GROUP(0) ARGS(ra_ira) VARNAME(Cpy) VALUE("cpy")

#define LIST_OF_INSTR_G0_RA_RB__COLLECTION_1(ENC_GROUP, ARGS, VARNAME, \
	VALUE)\
/* Subroutine call using (rA + rB) as destination address.  */ \
/* The return address is stored in the link register (lr). */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Callx) VALUE("callx") \
\
/* Set pc to destination address in (rA + rB). */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Jumpx) VALUE("jumpx")



#define LIST_OF_INSTR_G0_RA_PC__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
/* Copy pc to rA (this can be used for pc-relative loads */ \
/* and stores) */ \
ENC_GROUP(0) ARGS(ra_pc) VARNAME(Cpy) VALUE("cpy")



#define LIST_OF_INSTR_G0_RA_RB__COLLECTION_2(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
/* Copy */ \
/* rA = rB */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Cpy) VALUE("cpy") \
\
/* rA = Sign extend of low 16 bits in rB */ \
/* Note that the high 16 bits of rB are ignored */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Seh) VALUE("seh") \
\
/* rA = Sign extend of low 8 bits in rB */ \
ENC_GROUP(0) ARGS(ra_rb) VARNAME(Seb) VALUE("seb")



//// Pseudo instruction:
//// Subroutine call using rB as destination address. 
//// Encoded like this:  callx r0, rB
//PSEUDO_INSTR_RB(call)
//
//// Pseudo instruction:
//// Set pc to destination address in rB.
//// Encoded like this:  jumpx r0, rB
//PSEUDO_INSTR_RB(jump)
//
//// Pseudo instruction:
//// Set pc to destination address in rB.
//// Encoded like this:  jumpx r0, rB
//PSEUDO_INSTR_PC_RB(cpy)



#define LIST_OF_GROUP_0_INSTRUCTIONS(ENC_GROUP, ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_LDST_RA_RB__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
LIST_OF_INSTR_G0_RA_RB__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_IRA_RA__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_RA_IRA__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_RA_RB__COLLECTION_1(ENC_GROUP, ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_RA_PC__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_RA_RB__COLLECTION_2(ENC_GROUP, ARGS, VARNAME, VALUE) \


#endif		// group_0_instructions_hpp
