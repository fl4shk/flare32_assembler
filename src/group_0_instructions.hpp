#ifndef group_0_instructions_hpp
#define group_0_instructions_hpp


// Group 0 Instructions
// 00fo oooo aaaa bbbb

	// f:  1 if can affect flags (and instruction type supports it), 0 if
	// flags unchanged.

	// o:  opcode
	// a:  rA (destination register usually)
	// b:  rB

#define LIST_OF_INSTR_G0_RA_RB__COLLECTION_0(ARGS, VARNAME, VALUE) \
/* rA = rA + rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ARGS(ra_rb) VARNAME(Add) VALUE("add") \
\
/* rA = rA + rB + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ARGS(ra_rb) VARNAME(Adc) VALUE("adc") \
\
/* rA = rA - rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ARGS(ra_rb) VARNAME(Sub) VALUE("sub") \
\
/* rA = rA + (~rB) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ARGS(ra_rb) VARNAME(Sbc) VALUE("sbc") \
\
\
\
/* rA = rB - rA */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ARGS(ra_rb) VARNAME(Rsb) VALUE("rsb") \
\
/* rA = rA * rB */ \
ARGS(ra_rb) VARNAME(Mul) VALUE("mul") \
\
/* rA = rA & rB */ \
/* This instruction can affect the N and Z flags. */ \
ARGS(ra_rb) VARNAME(And) VALUE("and") \
\
/* rA = rA | rB */ \
/* This instruction can affect the N and Z flags. */ \
ARGS(ra_rb) VARNAME(Or) VALUE("or") \
\
\
\
/* rA = rA ^ rB */ \
/* This instruction can affect the N and Z flags. */ \
ARGS(ra_rb) VARNAME(Xor) VALUE("xor") \
\
/* Logical shift left */ \
/* rA = rA << rB */ \
ARGS(ra_rb) VARNAME(Lsl) VALUE("lsl") \
\
/* Logical shift right */ \
ARGS(ra_rb) VARNAME(Lsr) VALUE("lsr") \
\
/* Arithmetic shift right */ \
ARGS(ra_rb) VARNAME(Asr) VALUE("asr") \
\
\
\
/* Rotate rA left by rB bits, then store result in rA. */ \
ARGS(ra_rb) VARNAME(Rol) VALUE("rol") \
\
/* Rotate rA right by rB bits, then store result in rA. */ \
ARGS(ra_rb) VARNAME(Ror) VALUE("ror") \
\
/* Rotate rB left (THROUGH carry) by 1 bit, then store result in rA. */ \
/* This instruction can only affect the C flag. */ \
ARGS(ra_rb) VARNAME(Rlc) VALUE("rlc") \
\
/* Rotate rB right (THROUGH carry) by 1 bit, then store result in rA. */ \
/* This instruction can only affect the C flag. */ \
ARGS(ra_rb) VARNAME(Rrc) VALUE("rrc") \
\
\
\
/* rA = Sign extend of low 16 bits in rB */ \
/* Note that the high 16 bits of rB are ignored */ \
ARGS(ra_rb) VARNAME(Seh) VALUE("seh") \
\
/* rA = Sign extend of low 8 bits in rB */ \
ARGS(ra_rb) VARNAME(Seb) VALUE("seb") \
\
/* Load a 32-bit value into rA from the address in rB */ \
ARGS(ra_rb) VARNAME(Ldr) VALUE("ldr") \
\
/* Store rA to address in rB */ \
ARGS(ra_rb) VARNAME(Str) VALUE("str")



#define LIST_OF_INSTR_G0_FLAGS__COLLECTION_0(ARGS, VARNAME, VALUE) \
/* Push flags as 8-bit value onto the stack (high 4 bits of pushed */ \
/* value are set to zero before the push) */ \
ARGS(flags) VARNAME(Push) VALUE("push") \
\
/* Pop 8-bit value from the stack and store low 4 bits to flags */ \
ARGS(flags) VARNAME(Pop) VALUE("pop")


#define LIST_OF_INSTR_G0_RA_FLAGS__COLLECTION_0(ARGS, VARNAME, VALUE) \
/* Clear rA, then CoPY FRom Flags to rA */ \
ARGS(ra_flags) VARNAME(Cpy) VALUE("cpy")

#define LIST_OF_INSTR_G0_FLAGS_RA__COLLECTION_0(ARGS, VARNAME, VALUE) \
/* Copy to flags from rA */ \
/* This instruction can affect N, V, Z, and C flags. */ \
ARGS(flags_ra) VARNAME(Cpy) VALUE("cpy")


#define LIST_OF_INSTR_G0_NO_ARGS__COLLECTION_0(ARGS, VARNAME, VALUE) \
/* ENable Interrupts */ \
ARGS(no_args) VARNAME(Eni) VALUE("eni") \
\
/* DIsable Interrupts */ \
ARGS(no_args) VARNAME(Dii) VALUE("dii") \
\
/* Set the PC to interrupt RETurn address and enable Interrupts */ \
ARGS(no_args) VARNAME(Reti) VALUE("reti") \


#define LIST_OF_INSTR_G0_IRA__COLLECTION_0(ARGS, VARNAME, VALUE) \
/* Set the PC to the Interrupt Return Address, but DON'T enable */ \
/* interrupts */ \
ARGS(ira) VARNAME(Jump) VALUE("jump")



#define LIST_OF_INSTR_G0_IRA_RA__COLLECTION_0(ARGS, VARNAME, VALUE) \
/* Copy rA to the Interrupt Return Address */ \
ARGS(ira_ra) VARNAME(Cpy) VALUE("cpy")

#define LIST_OF_INSTR_G0_RA_IRA__COLLECTION_0(ARGS, VARNAME, VALUE) \
/* Copy the Interrupt Return Address to rA */ \
ARGS(ra_ira) VARNAME(Cpy) VALUE("cpy")


#define LIST_OF_INSTR_G0_RA_RB__COLLECTION_1(ARGS, VARNAME, VALUE) \
/* Subroutine call using (rA + rB) as destination address.  */ \
/* The return address is stored in the link register (lr). */ \
ARGS(ra_rb) VARNAME(Callx) VALUE("callx")

#define LIST_OF_INSTR_G0_RA_PC__COLLECTION_0(ARGS, VARNAME, VALUE) \
/* Copy pc to rA (this can be used for pc-relative loads */ \
/* and stores) */ \
ARGS(ra_pc) VARNAME(Cpy) VALUE("cpy")


#define LIST_OF_GROUP_0_INSTRUCTIONS(ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_RA_RB__COLLECTION_0(ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_FLAGS__COLLECTION_0(ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_RA_FLAGS__COLLECTION_0(ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_FLAGS_RA__COLLECTION_0(ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_NO_ARGS__COLLECTION_0(ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_IRA__COLLECTION_0(ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_IRA_RA__COLLECTION_0(ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_RA_IRA__COLLECTION_0(ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_RA_RB__COLLECTION_1(ARGS, VARNAME, VALUE) \
LIST_OF_INSTR_G0_RA_PC__COLLECTION_0(ARGS, VARNAME, VALUE) \


#endif		// group_0_instructions_hpp
