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
INSTR_LDST_RA_RB(ldr) \
\
/* Load zero-extended 16-bit value from address rB into rA. */ \
/* This zero-extends the value. */ \
INSTR_LDST_RA_RB(ldh) \
\
/* Load sign-extended 16-bit value from address rB into rA. */ \
/* This sign-extends the value. */ \
INSTR_LDST_RA_RB(ldsh) \
\
/* Load zero-extended 8-bit value from address rB into rA. */ \
/* This zero-extends the value. */ \
INSTR_LDST_RA_RB(ldb) \
\
\
\
/* Load sign-extended 8-bit value from address rB into rA. */ \
/* This sign-extends the value. */ \
INSTR_LDST_RA_RB(ldsb) \
\
/* Store 32-bit value in rA to address rB. */ \
INSTR_LDST_RA_RB(str) \
\
/* Store low 16 bits of rA to address rB. */ \
INSTR_LDST_RA_RB(sth) \
\
/* Store low 8 bits of rA to address rB. */ \
INSTR_LDST_RA_RB(stb)



#define LIST_OF_INSTR_G0_RA_RB__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
/* rA = rA + rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB(add) \
\
/* rA = rA + rB + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB(adc) \
\
/* rA = rA - rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB(sub) \
\
/* rA = rA + (~rB) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB(sbc) \
\
\
\
/* rA = rB - rA */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB(rsb) \
\
/* rA = rA * rB */ \
INSTR_RA_RB(mul) \
\
/* rA = rA & rB */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB(and) \
\
/* rA = rA | rB */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB(or) \
\
\
\
/* rA = rA ^ rB */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB(xor) \
\
/* Logical shift left */ \
/* rA = rA << rB */ \
INSTR_RA_RB(lsl) \
\
/* Logical shift right */ \
INSTR_RA_RB(lsr) \
\
/* Arithmetic shift right */ \
INSTR_RA_RB(asr) \
\
\
\
/* Rotate rA left by rB bits, then store result in rA. */ \
INSTR_RA_RB(rol) \
\
/* Rotate rA right by rB bits, then store result in rA. */ \
INSTR_RA_RB(ror) \
\
/* Rotate rB left (THROUGH carry) by 1 bit, then store result in rA. */ \
/* This instruction can only affect the C flag. */ \
INSTR_RA_RB(rlc) \
\
/* Rotate rB right (THROUGH carry) by 1 bit, then store result in rA. */ \
/* This instruction can only affect the C flag. */ \
INSTR_RA_RB(rrc)



#define LIST_OF_INSTR_G0_IRA_RA__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
/* Copy rA to the Interrupt Return Address */ \
INSTR_IRA_RA(cpy)

#define LIST_OF_INSTR_G0_RA_IRA__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE)\
/* Copy the Interrupt Return Address to rA */ \
INSTR_RA_IRA(cpy)

#define LIST_OF_INSTR_G0_RA_RB__COLLECTION_1(ENC_GROUP, ARGS, VARNAME, \
	VALUE)\
/* Subroutine call using (rA + rB) as destination address.  */ \
/* The return address is stored in the link register (lr). */ \
INSTR_RA_RB(callx) \
\
/* Set pc to destination address in (rA + rB). */ \
INSTR_RA_RB(jumpx)



#define LIST_OF_INSTR_G0_RA_PC__COLLECTION_0(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
/* Copy pc to rA (this can be used for pc-relative loads */ \
/* and stores) */ \
INSTR_RA_PC(cpy)



#define LIST_OF_INSTR_G0_RA_RB__COLLECTION_2(ENC_GROUP, ARGS, VARNAME, \
	VALUE) \
/* Copy */ \
/* rA = rB */ \
INSTR_RA_RB(cpy) \
\
/* rA = Sign extend of low 16 bits in rB */ \
/* Note that the high 16 bits of rB are ignored */ \
INSTR_RA_RB(seh) \
\
/* rA = Sign extend of low 8 bits in rB */ \
INSTR_RA_RB(seb)



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

#endif		// group_0_instructions_hpp
