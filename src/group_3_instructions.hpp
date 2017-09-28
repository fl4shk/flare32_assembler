#ifndef group_3_instructions_hpp
#define group_3_instructions_hpp


// Group 3 Instructions
// Non Block Moves Version:  
	// 11fo oooo aaaa bbbb  iiii iiii iiii iiii  iiii iiii iiii iiii

	// f:  1 if can affect flags (and instruction type supports it), 0 if
	// flags unchanged.

	// o:  opcode
	// a: rA
	// b: rB
	// i:  32-bit immediate value

// Block Moves Version (stmdb, ldmia, stmia, push, pop):  
	// 11fo oooo aaaa bbbb  cccc dddd eeee ffff  gggg hhhh xxxx 00ii

	// f:  1 if can affect flags (and instruction type supports it), 0 if
	// flags unchanged.

	// o:  opcode
	// a: rA
	// b: rB
	// c: rC
	// d: rD
	// e: rE
	// f: rF
	// g: rG
	// h: rH
	// x: rX
	// i:  2-bit immediate value


#define LIST_OF_INSTR_G3_LDST_RA_RB_IMM32__COLLECTION_0(INSTR_STUFF) \
/* Load 32-bit value from address (absolute_addr + rB) into rA. */ \
INSTR_STUFF(3, ldst_ra_rb_imm32, Ldra, "ldra") \
\
/* Load zero-extended 16-bit value from address (absolute_addr + rB) into \
rA. */ \
/* This zero-extends the value. */ \
INSTR_STUFF(3, ldst_ra_rb_imm32, Ldha, "ldha") \
\
/* Load sign-extended 16-bit value from address (absolute_addr + rB) into \
rA. */ \
/* This sign-extends the value. */ \
INSTR_STUFF(3, ldst_ra_rb_imm32, Ldsha, "ldsha") \
\
/* Load zero-extended 8-bit value from address (absolute_addr + rB) into \
rA. */ \
/* This zero-extends the value. */ \
INSTR_STUFF(3, ldst_ra_rb_imm32, Ldba, "ldba") \
\
\
\
/* Load sign-extended 8-bit value from address (absolute_addr + rB) into \
rA. */ \
/* This sign-extends the value. */ \
INSTR_STUFF(3, ldst_ra_rb_imm32, Ldsba, "ldsba") \
\
/* Store 32-bit value in rA to address (absolute_addr + rB). */ \
INSTR_STUFF(3, ldst_ra_rb_imm32, Stra, "stra") \
\
/* Store low 16 bits of rA to address (absolute_addr + rB). */ \
INSTR_STUFF(3, ldst_ra_rb_imm32, Stha, "stha") \
\
/* Store low 8 bits of rA to address (absolute_addr + rB). */ \
INSTR_STUFF(3, ldst_ra_rb_imm32, Stba, "stba") \



#define LIST_OF_INSTR_G3_RA_RB_IMM32__COLLECTION_0(INSTR_STUFF) \
/* Set pc to destination address in (rA + rB + absolute_addr). */ \
INSTR_STUFF(3, ra_rb_imm32, Jumpa, "jumpa") \
\
/* Subroutine call using (rA + rB + absolute_addr) as destination  \
address. */ \
/* The return address is stored in the link register (lr). */ \
INSTR_STUFF(3, ra_rb_imm32, Calla, "calla") \
\
/* rA = 32-bit immediate, rB = same 32-bit immediate */ \
/* If rA is the same register as rB, then the  */ \
/* register will only be written once. */ \
INSTR_STUFF(3, ra_rb_imm32, Cpypi, "cpypi") \



#define LIST_OF_INSTR_G3_LDST_BLOCK_5_TO_8__COLLECTION_0(INSTR_STUFF) \
/* STore Multiple, Decrement Before */ \
/* Note that this instruction takes multiple forms */ \
	/* Syntax:  stmdb rX, {rA, rB, rC, rD, rE} */ \
INSTR_STUFF(3, ldst_block_5_to_8, Stmdb, "stmdb") \
\
\
\
/* LoaD Multiple, Increment After */ \
/* Note that this instruction takes multiple forms */ \
	/* Syntax:  ldmia rX, {rA, rB, rC, rD, rE} */ \
INSTR_STUFF(3, ldst_block_5_to_8, Ldmia, "ldmia") \
\
\
/* STore Multiple, Increment After */ \
/* Note that this instruction takes multiple forms */ \
	/* Syntax:  stmia rX, {rA, rB, rC, rD, rE} */ \
INSTR_STUFF(3, ldst_block_5_to_8, Stmia, "stmia") \


#define LIST_OF_INSTR_G3_FLAGS__COLLECTION_0(INSTR_STUFF) \
/* Push flags as 8-bit value onto the stack (high 4 bits of pushed */ \
/* value are set to zero before the push) */ \
INSTR_STUFF(3, flags, Push, "push") \
\
/* Pop 8-bit value from the stack and store low 4 bits to flags */ \
INSTR_STUFF(3, flags, Pop, "pop")



#define LIST_OF_INSTR_G3_RA_FLAGS__COLLECTION_0(INSTR_STUFF) \
/* Clear rA, then CoPY FRom Flags to rA */ \
INSTR_STUFF(3, ra_flags, Cpy, "cpy")

#define LIST_OF_INSTR_G3_FLAGS_RA__COLLECTION_0(INSTR_STUFF) \
/* Copy to flags from rA */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(3, flags_ra, Cpy, "cpy")


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
//// Set pc to destination address in (rA + absolute_addr).
//// Encoded like this:  jumpa rA, r0, absolute_addr
//RA_IMM(jumpa)

// Pseudo instruction:
//// Set pc to destination address in (absolute_addr).
//// Encoded like this:  jumpa r0, r0, absolute_addr
//IMM(jumpa)

// Pseudo instruction:
//// Subroutine call using (rA + absolute_addr) as destination address. 
//// The return address is stored in the link register (lr).
//// Encoded like this:  calla rA, r0, absolute_addr
//RA_IMM(calla)

// Pseudo instruction:
//// Subroutine call using (absolute_addr) as destination address. 
//// The return address is stored in the link register (lr).
//// Encoded like this:  calla r0, r0, absolute_addr
//IMM(calla)



// Pseudo instruction:
//// rA = 32-bit immediate
//// Encoded like this:  cpypi rA, rA, imm
//RA_IMM(cpyi)



// Pseudo instruction:
// Pop
// Note that this instruction takes multiple forms
	// Syntax:  pop rA, rB, rC, rD, rE


// Pseudo instruction:
// Push
// Note that this instruction takes multiple forms
	// Syntax:  push rA, rB, rC, rD, rE

#define LIST_OF_GROUP_3_INSTRUCTIONS(INSTR_STUFF) \
LIST_OF_INSTR_G3_LDST_RA_RB_IMM32__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G3_RA_RB_IMM32__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G3_LDST_BLOCK_5_TO_8__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G3_FLAGS__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G3_RA_FLAGS__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G3_FLAGS_RA__COLLECTION_0(INSTR_STUFF)


#endif		// group_3_instructions_hpp
