#ifndef instruction_class_hpp
#define instruction_class_hpp

#include "misc_includes.hpp"


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
/* Push registers rA and rb (as a pair) onto the  */ \
/* stack (in that order) */ \
ARGS(ra_rb) VARNAME(Push) VALUE("push") \
\
/* Pop two 32-bit values off the stack, storing the first popped */ \
/* value into rB and the second popped value into rA */ \
ARGS(ra_rb) VARNAME(Pop) VALUE("pop")



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


//// Group 1 Instructions
//// 01fo oooo aaaa bbbb  iiii iiii iiii iiii
//
//	// f:  1 if can affect flags (and instruction type supports it), 0 if
//	// flags unchanged.
//
//	// o:  opcode
//	// a:  rA
//	// b:  rB
//	// i:  16-bit immediate value
//
///* rA = rB + (zero-extended imm) */
///* This instruction can affect N, V, Z, and C flags. */
//INSTR_RA_RB_IMM(addi)
//
///* rA = rB + (zero-extended imm) + carry_flag */
///* Add with carry */
///* This instruction can affect N, V, Z, and C flags. */
//INSTR_RA_RB_IMM(adci)
//
///* rA = rB - (zero-extended imm) */
///* This instruction can affect N, V, Z, and C flags. */
//INSTR_RA_RB_IMM(subi)
//
///* rA = rB + (~(zero-extended imm)) + carry_flag */
///* Subtract with borrow (6502 style) */
///* This instruction can affect N, V, Z, and C flags. */
//INSTR_RA_RB_IMM(sbci)
//
//
//
///* rA = (zero-extended imm) - rB */
///* This instruction can affect N, V, Z, and C flags. */
//INSTR_RA_RB_IMM(rsbi)
//
///* rA = rB * (zero-extended imm) */
//INSTR_RA_RB_IMM(muli)
//
///* rA = rB & (zero-extended imm) */
///* This instruction can affect the N and Z flags. */
//INSTR_RA_RB_IMM(andi)
//
///* rA = rB | (zero-extended imm) */
///* This instruction can affect the N and Z flags. */
//INSTR_RA_RB_IMM(ori)
//
//
//
///* rA = rB ^ (zero-extended imm) */
///* This instruction can affect the N and Z flags. */
//INSTR_RA_RB_IMM(xori)
//
///* Logical shift left */
///* rA = rB << (zero-extended imm) */
//INSTR_RA_RB_IMM(lsli)
//
///* Logical shift right */
//INSTR_RA_RB_IMM(lsri)
//
///* Arithmetic shift right */
//INSTR_RA_RB_IMM(asri)
//
//
//
///* Rotate  left by (zero-extended imm) bits, then store result in rA. */
//INSTR_RA_RB_IMM(roli)
//
///* Rotate  right by (zero-extended imm) bits, then store result in rA. */
//INSTR_RA_RB_IMM(rori)
//
///* Branch always,  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(bra)
//
///* Branch never (effectively a NOP), */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(bnv)
//
//
//
///* Branch when Z == 0,  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(bne)
//
///* Branch when Z == 1,  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(beq)
//
///* Branch when C == 0 [unsigned less than],  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(bcc)
//
///* Branch when C == 1 [unsigned greater than or equal],  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(bcs)
//
//
//
///* Branch when (C == 0 or Z == 1) [unsigned less than or equal],  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(bls)
//
///* Branch when (C == 1 and Z == 0) [unsigned greater than],  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(bhi)
//
///* Branch when N == 0,  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(bpl)
//
///* Branch when N == 1,  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(bmi)
//
//
//
///* Branch when V == 0,  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(bvc)
//
///* Branch when V == 1,  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(bvs)
//
///* Branch when N == V [signed greater than or equal],  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(bge)
//
///* Branch when N != V [signed less than],  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(blt)
//
//
//
///* Branch when (N == V and Z == 0) [signed greater than],  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(bgt)
//
///* Branch when (N != V or Z == 1) [signed less than or equal],  */
///* to ((pc when instruction starts) */
///* + (sign-extended 16-bit immediate value)) */
//INSTR_IMM(ble)
//
///* rA = rB ^ (sign-extended imm) */
///* This instruction can affect the N and Z flags. */
//INSTR_RA_RB_IMM(xorsi)
//
///* Reserved for future expansion. */
//
//
//
//// Group 2 Instructions
//// 10fo oooo aaaa bbbb  cccc iiii iiii iiii
//
//	// f:  1 if can affect flags (and instruction type supports it), 0 if
//	// flags unchanged.
//
//	// o:  opcode
//	// a:  rA
//	// b:  rB
//	// c:  rc
//	// i:  12-bit immediate value
//
///* Load 32-bit value from address  */
///* (rB + rC + (sign-extended imm)) into rA. */
//INSTR_LDST_RA_RB_RC_IMM(ldr)
//
///* Load zero-extended 16-bit value from address  */
///* (rB + rC + (sign-extended imm)) into rA. */
///* This zero-extends the value. */
//INSTR_LDST_RA_RB_RC_IMM(ldh)
//
///* Load sign-extended 16-bit value from address (rB + rC + (sign-extended */
///* imm)) into rA. */
///* This sign-extends the value. */
//INSTR_LDST_RA_RB_RC_IMM(ldsh)
//
///* Load zero-extended 8-bit value from address  */
///* (rB + rC + (sign-extended imm)) into rA. */
///* This zero-extends the value. */
//INSTR_LDST_RA_RB_RC_IMM(ldb)
//
//
//
///* Load sign-extended 8-bit value from address  */
///* (rB + rC + (sign-extended imm)) into rA. */
///* This sign-extends the value. */
//INSTR_LDST_RA_RB_RC_IMM(ldsb)
//
///* Store 32-bit value in rA to address (rB + rC + (sign-extended imm)). */
//INSTR_LDST_RA_RB_RC_IMM(str)
//
///* Store low 16 bits of rA to address (rB + rC + (sign-extended imm)). */
//INSTR_LDST_RA_RB_RC_IMM(sth)
//
///* Store low 8 bits of rA to address (rB + rC + (sign-extended imm)). */
//INSTR_LDST_RA_RB_RC_IMM(stb)
//
//
///* rA = rB + rC */
///* This instruction can affect N, V, Z, and C flags. */
//INSTR_RA_RB_RC(add)
//
///* rA = rB + rC + carry_flag */
///* Add with carry */
///* This instruction can affect N, V, Z, and C flags. */
//INSTR_RA_RB_RC(adc)
//
///* rA = rB - rC */
///* This instruction can affect N, V, Z, and C flags. */
//INSTR_RA_RB_RC(sub)
//
///* rA = rB + (~rC) + carry_flag */
///* Subtract with borrow (6502 style) */
///* This instruction can affect N, V, Z, and C flags. */
//INSTR_RA_RB_RC(sbc)
//
//
//
///* rA = rC - rB */
///* This instruction can affect N, V, Z, and C flags. */
//INSTR_RA_RB_RC(rsb)
//
///* rA = rB * rC */
//INSTR_RA_RB_RC(mul)
//
///* rA = rB & rC */
///* This instruction can affect the N and Z flags. */
//INSTR_RA_RB_RC(and)
//
///* rA = rB | rC */
///* This instruction can affect the N and Z flags. */
//INSTR_RA_RB_RC(or)
//
//
//
///* rA = rB ^ rC */
///* This instruction can affect the N and Z flags. */
//INSTR_RA_RB_RC(xor)
//
///* Logical shift left */
///* rA = rB << rC */
//INSTR_RA_RB_RC(lsl)
//
///* Logical shift right */
//INSTR_RA_RB_RC(lsr)
//
///* Arithmetic shift right */
//INSTR_RA_RB_RC(asr)
//
//
//
///* Rotate rC left by rC bits, then store result in rA. */
//INSTR_RA_RB_RC(rol)
//
///* Rotate rC right by rC bits, then store result in rA. */
//INSTR_RA_RB_RC(ror)
//
///* Fused multiply-add */
///* rA = rA + (rB * rC) */
//INSTR_RA_RB_RC(fma)
//
///* Copy rC to rA and to rB */
///* If rA is the same register as rB, then the  */
///* register will only be written once. */
//INSTR_RA_RB_RC(cpyp)
//
//
//
///* Set pc to destination address in (rA + rB). */
//INSTR_RA_RB(jumpx)
//
///* Add 4 to rB, then load from address in rB into */
///* rA */
///* LoaD Register, Add Before */
//INSTR_LDST_RA_RB(ldrpb)
//
///* Store rA to address in rB, then subtract 4 from */
///* rB */
///* STore Register, Subtract After */
//INSTR_LDST_RA_RB(strma)
//
///* Reserved for future expansion. */
//
//
//
///* Reserved for future expansion. */
///* Reserved for future expansion. */
///* Reserved for future expansion. */
///* Reserved for future expansion. */
//
//
//
//// Group 3 Instructions
//// 11fo oooo aaaa bbbb  iiii iiii iiii iiii  iiii iiii iiii iiii
//
//	// f:  1 if can affect flags (and instruction type supports it), 0 if
//	// flags unchanged.
//
//	// o:  opcode
//	// a:  rA
//	// b:  rB
//	// i:  32-bit immediate value
//
///* Load 32-bit value from address (absolute_addr + rB) into rA. */
//INSTR_LDST_RA_RB_IMM(ldra)
//
///* Load zero-extended 16-bit value from address (absolute_addr + rB)  */
///* into rA. */
///* This zero-extends the value. */
//INSTR_LDST_RA_RB_IMM(ldha)
//
///* Load sign-extended 16-bit value from address (absolute_addr + rB)  */
///* into rA. */
///* This sign-extends the value. */
//INSTR_LDST_RA_RB_IMM(ldsha)
//
///* Load zero-extended 8-bit value from address (absolute_addr + rB)  */
///* into rA. */
///* This zero-extends the value. */
//INSTR_LDST_RA_RB_IMM(ldba)
//
//
//
///* Load sign-extended 8-bit value from address (absolute_addr + rB)  */
///* into rA. */
///* This sign-extends the value. */
//INSTR_LDST_RA_RB_IMM(ldsba)
//
///* Store 32-bit value in rA to address (absolute_addr + rB). */
//INSTR_LDST_RA_RB_IMM(stra)
//
///* Store low 16 bits of rA to address (absolute_addr + rB). */
//INSTR_LDST_RA_RB_IMM(stha)
//
///* Store low 8 bits of rA to address (absolute_addr + rB). */
//INSTR_LDST_RA_RB_IMM(stba)
//
//
//
///* Set pc to destination address in (rA + rB + absolute_addr). */
//INSTR_RA_RB_IMM(jumpa)
//
///* Subroutine call using (rA + rB + absolute_addr) as destination  */
///* address.  */
///* The return address is stored in the link register (lr). */
//INSTR_RA_RB_IMM(calla)
//
///* rA = 32-bit immediate, rB = same 32-bit immediate */
///* If rA is the same register as rB, then the  */
///* register will only be written once. */
//INSTR_RA_RB_IMM(cpypi)
//
///* Reserved for future expansion. */
//
//
//
///* Reserved for future expansion. */
///* Reserved for future expansion. */
///* Reserved for future expansion. */
///* Reserved for future expansion. */
//
//
//
///* Reserved for future expansion. */
///* Reserved for future expansion. */
///* Reserved for future expansion. */
///* Reserved for future expansion. */
//
//
//
///* Reserved for future expansion. */
///* Reserved for future expansion. */
///* Reserved for future expansion. */
///* Reserved for future expansion. */
//
//
//
///* Reserved for future expansion. */
///* Reserved for future expansion. */
///* Reserved for future expansion. */
///* Reserved for future expansion. */
//
//
//
///* Reserved for future expansion. */
///* Reserved for future expansion. */
///* Reserved for future expansion. */
///* Reserved for future expansion. */


namespace gigachip32
{


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


}

#endif		// instruction_class_hpp
