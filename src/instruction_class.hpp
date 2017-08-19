#ifndef instruction_class_hpp
#define instruction_class_hpp

#include "misc_includes.hpp"



enum class InstrArgs
{
	no_args,
	imm,

	ra,
	ra_imm,
	ra_rb,
	ra_rb_imm,
	ra_rb_rc,
	ra_rb_rc_imm,

	ldst_ra_rb_rc_imm,
	ldst_ra_rb_rc,
	ldst_ra_rb_imm,
	ldst_ra_rb,
	ldst_ra_imm,
	ldst_generic_ra_rb_rc_imm,

	ira,
	ra_ira,
	ira_ra,

	ra_flags,
	flags,
	flags_ra,

	ra_pc,

	pseudo_rb,
	pseudo_rb_imm,
	pseudo_rb_rc,
	pseudo_rb_rc_imm,
	pseudo_ra_rc,
	pseudo_pc_rb
};


// Group 0 instructions

/* rA = rA + rB */
/* This instruction can affect N, V, Z, and C flags. */
INSTR_RA_RB(add)

/* rA = rA + rB + carry_flag */
/* Add with carry */
/* This instruction can affect N, V, Z, and C flags. */
INSTR_RA_RB(adc)

/* rA = rA - rB */
/* This instruction can affect N, V, Z, and C flags. */
INSTR_RA_RB(sub)

/* rA = rA + (~rB) + carry_flag */
/* Subtract with borrow (6502 style) */
/* This instruction can affect N, V, Z, and C flags. */
INSTR_RA_RB(sbc)



/* rA = rB - rA */
/* This instruction can affect N, V, Z, and C flags. */
INSTR_RA_RB(rsb)

/* rA = rA * rB */
INSTR_RA_RB(mul)

/* rA = rA & rB */
/* This instruction can affect the N and Z flags. */
INSTR_RA_RB(and)

/* rA = rA | rB */
/* This instruction can affect the N and Z flags. */
INSTR_RA_RB(or)



/* rA = rA ^ rB */
/* This instruction can affect the N and Z flags. */
INSTR_RA_RB(xor)

/* Logical shift left */
/* rA = rA << rB */
INSTR_RA_RB(lsl)

/* Logical shift right */
INSTR_RA_RB(lsr)

/* Arithmetic shift right */
INSTR_RA_RB(asr)



/* Rotate rA left by rB bits, then store result in rA. */
INSTR_RA_RB(rol)

/* Rotate rA right by rB bits, then store result in rA. */
INSTR_RA_RB(ror)

/* Rotate rB left (THROUGH carry) by 1 bit, then store result in rA. */
/* This instruction can only affect the C flag. */
INSTR_RA_RB(rlc)

/* Rotate rB right (THROUGH carry) by 1 bit, then store result in rA. */
/* This instruction can only affect the C flag. */
INSTR_RA_RB(rrc)



/* rA = Sign extend of low 16 bits in rB */
/* Note that the high 16 bits of rB are ignored */
INSTR_RA_RB(seh)

/* rA = Sign extend of low 8 bits in rB */
INSTR_RA_RB(seb)

/* Push registers rA and rb (as a pair) onto the  */
/* stack (in that order) */
INSTR_RA_RB(push)

/* Pop two 32-bit values off the stack, storing the first popped */
/* value into rB and the second popped value into rA */
INSTR_RA_RB(pop)



/* Push flags as 8-bit value onto the stack (high 4 bits of pushed */
/* value are set to zero before the push) */
INSTR_FLAGS(push)

/* Pop 8-bit value from the stack and store low 4 bits to flags */
INSTR_FLAGS(pop)

/* Clear rA, then CoPY FRom Flags to rA */
INSTR_RA_FLAGS(cpy)

/* Copy to flags from rA */
/* This instruction can affect N, V, Z, and C flags. */
INSTR_FLAGS_RA(cpy)



/* ENable Interrupts */
INSTR_NO_ARGS(eni)

/* DIsable Interrupts */
INSTR_NO_ARGS(dii)

/* Set the PC to interrupt RETurn address and enable Interrupts */
INSTR_NO_ARGS(reti)

/* Set the PC to the Interrupt Return Address, but DON'T enable */
/* interrupts */
INSTR_IRA(jump)



/* Copy rA to the Interrupt Return Address */
INSTR_IRA_RA(cpy)

/* Copy the Interrupt Return Address to rA */
INSTR_RA_IRA(cpy)

/* Subroutine call using (rA + rB) as destination address.  */
/* The return address is stored in the link register (lr). */
INSTR_RA_RB(callx)

/* Copy pc to rA (this can be used for pc-relative loads */
/* and stores) */
INSTR_RA_PC(cpy)



class Instruction;
typedef const Instruction* PInstr;

class Instruction
{
private:		// variables
	std::string __str;
	bool __affects_flags;


public:		// constants
	
	gen_getter_by_con_ref(str);
	gen_getter_by_val(affects_flags);
	
};


#endif		// instruction_class_hpp
