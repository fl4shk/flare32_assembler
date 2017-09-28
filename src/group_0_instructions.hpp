#ifndef group_0_instructions_hpp
#define group_0_instructions_hpp


// Group 0 Instructions
// 00fo oooo aaaa bbbb

	// f:  1 if can affect flags (and instruction type supports it), 0 if
	// flags unchanged.

	// o:  opcode
	// a: rA (destination register usually)
	// b: rB

#define LIST_OF_INSTR_G0_LDST_RA_RB__COLLECTION_0(INSTR_STUFF) \
/* Load 32-bit value from address rB into rA. */ \
INSTR_STUFF(0, ldst_ra_rb, Ldr, "ldr") \
\
/* Load zero-extended 16-bit value from address rB into rA. */ \
/* This zero-extends the value. */ \
INSTR_STUFF(0, ldst_ra_rb, Ldh, "ldh") \
\
/* Load sign-extended 16-bit value from address rB into rA. */ \
/* This sign-extends the value. */ \
INSTR_STUFF(0, ldst_ra_rb, Ldsh, "ldsh") \
\
/* Load zero-extended 8-bit value from address rB into rA. */ \
/* This zero-extends the value. */ \
INSTR_STUFF(0, ldst_ra_rb, Ldb, "ldb") \
\
\
\
/* Load sign-extended 8-bit value from address rB into rA. */ \
/* This sign-extends the value. */ \
INSTR_STUFF(0, ldst_ra_rb, Ldsb, "ldsb") \
\
/* Store 32-bit value in rA to address rB. */ \
INSTR_STUFF(0, ldst_ra_rb, Str, "str") \
\
/* Store low 16 bits of rA to address rB. */ \
INSTR_STUFF(0, ldst_ra_rb, Sth, "sth") \
\
/* Store low 8 bits of rA to address rB. */ \
INSTR_STUFF(0, ldst_ra_rb, Stb, "stb")



#define LIST_OF_INSTR_G0_RA_RB__COLLECTION_0(INSTR_STUFF) \
/* rA = rA + rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(0, ra_rb, Add, "add") \
\
/* rA = rA + rB + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(0, ra_rb, Adc, "adc") \
\
/* rA = rA - rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(0, ra_rb, Sub, "sub") \
\
/* rA = rA + (~rB) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(0, ra_rb, Sbc, "sbc") \
\
\
\
/* rA = rB - rA */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(0, ra_rb, Rsb, "rsb") \
\
/* rA = rA * rB */ \
INSTR_STUFF(0, ra_rb, Mul, "mul") \
\
/* rA = rA & rB */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_STUFF(0, ra_rb, And, "and") \
\
/* rA = rA | rB */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_STUFF(0, ra_rb, Or, "or") \
\
\
\
/* rA = rA ^ rB */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_STUFF(0, ra_rb, Xor, "xor") \
\
/* Logical shift left */ \
/* rA = rA << rB */ \
INSTR_STUFF(0, ra_rb, Lsl, "lsl") \
\
/* Logical shift right */ \
INSTR_STUFF(0, ra_rb, Lsr, "lsr") \
\
/* Arithmetic shift right */ \
INSTR_STUFF(0, ra_rb, Asr, "asr") \
\
\
\
/* Rotate rA left by rB bits, then store result in rA. */ \
INSTR_STUFF(0, ra_rb, Rol, "rol") \
\
/* Rotate rA right by rB bits, then store result in rA. */ \
INSTR_STUFF(0, ra_rb, Ror, "ror") \
\
/* Rotate rB left (THROUGH carry) by 1 bit, then store result in rA. */ \
/* This instruction can only affect the C flag. */ \
INSTR_STUFF(0, ra_rb, Rlc, "rlc") \
\
/* Rotate rB right (THROUGH carry) by 1 bit, then store result in rA. */ \
/* This instruction can only affect the C flag. */ \
INSTR_STUFF(0, ra_rb, Rrc, "rrc")



#define LIST_OF_INSTR_G0_IRA_RA__COLLECTION_0(INSTR_STUFF) \
/* Copy rA to the Interrupt Return Address */ \
INSTR_STUFF(0, ira_ra, Cpy, "cpy")

#define LIST_OF_INSTR_G0_RA_IRA__COLLECTION_0(INSTR_STUFF) \
/* Copy the Interrupt Return Address to rA */ \
INSTR_STUFF(0, ra_ira, Cpy, "cpy")

#define LIST_OF_INSTR_G0_RA_RB__COLLECTION_1(INSTR_STUFF) \
/* Subroutine call using (rA + rB) as destination address.  */ \
/* The return address is stored in the link register (lr). */ \
INSTR_STUFF(0, ra_rb, Callx, "callx") \
\
/* Set pc to destination address in (rA + rB). */ \
INSTR_STUFF(0, ra_rb, Jumpx, "jumpx")



#define LIST_OF_INSTR_G0_RA_PC__COLLECTION_0(INSTR_STUFF) \
/* Copy pc to rA (this can be used for pc-relative loads */ \
/* and stores) */ \
INSTR_STUFF(0, ra_pc, Cpy, "cpy")



#define LIST_OF_INSTR_G0_RA_RB__COLLECTION_2(INSTR_STUFF) \
/* Copy */ \
/* rA = rB */ \
INSTR_STUFF(0, ra_rb, Cpy, "cpy") \
\
/* rA = Sign extend of low 16 bits in rB */ \
/* Note that the high 16 bits of rB are ignored */ \
INSTR_STUFF(0, ra_rb, Seh, "seh") \
\
/* rA = Sign extend of low 8 bits in rB */ \
INSTR_STUFF(0, ra_rb, Seb, "seb")



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



#define LIST_OF_GROUP_0_INSTRUCTIONS(INSTR_STUFF) \
LIST_OF_INSTR_G0_LDST_RA_RB__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G0_RA_RB__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G0_IRA_RA__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G0_RA_IRA__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G0_RA_RB__COLLECTION_1(INSTR_STUFF) \
LIST_OF_INSTR_G0_RA_PC__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G0_RA_RB__COLLECTION_2(INSTR_STUFF) \


#endif		// group_0_instructions_hpp
