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

///* Load 32-bit value from address  */ \
/* (rB + rC + (sign-extended imm)) into rA. */ \
INSTR_LDST_RA_RB_RC_IMM(ldr,imm) \
\
/* Load zero-extended 16-bit value from address  */ \
/* (rB + rC + (sign-extended imm)) into rA. */ \
/* This zero-extends the value. */ \
INSTR_LDST_RA_RB_RC_IMM(ldh,imm) \
\
/* Load sign-extended 16-bit value from address  */ \
/* (rB + rC + (sign-extended imm)) into rA. */ \
/* This sign-extends the value. */ \
INSTR_LDST_RA_RB_RC_IMM(ldsh,imm) \
\
/* Load zero-extended 8-bit value from address  */ \
/* (rB + rC + (sign-extended imm)) into rA. */ \
/* This zero-extends the value. */ \
INSTR_LDST_RA_RB_RC_IMM(ldb,imm) \
\
\
\
/* Load sign-extended 8-bit value from address  */ \
/* (rB + rC + (sign-extended imm)) into rA. */ \
/* This sign-extends the value. */ \
INSTR_LDST_RA_RB_RC_IMM(ldsb,imm) \
\
/* Store 32-bit value in rA to address  */ \
/* (rB + rC + (sign-extended imm)). */ \
INSTR_LDST_RA_RB_RC_IMM(str,imm) \
\
/* Store low 16 bits of rA to address  */ \
/* (rB + rC + (sign-extended imm)). */ \
INSTR_LDST_RA_RB_RC_IMM(sth,imm) \
\
/* Store low 8 bits of rA to address  */ \
/* (rB + rC + (sign-extended imm)). */ \
INSTR_LDST_RA_RB_RC_IMM(stb,imm) \
\
\
/* rA = rB + rC */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_RC(add) \
\
/* rA = rB + rC + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_RC(adc) \
\
/* rA = rB - rC */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_RC(sub) \
\
/* rA = rB + (~rC) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_RC(sbc) \
\
\
\
/* rA = rC - rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_RC(rsb) \
\
/* rA = rB * rC */ \
INSTR_RA_RB_RC(mul) \
\
/* rA = rB & rC */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_RC(and) \
\
/* rA = rB | rC */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_RC(or) \
\
\
\
/* rA = rB ^ rC */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_RC(xor) \
\
/* Logical shift left */ \
/* rA = rB << rC */ \
INSTR_RA_RB_RC(lsl) \
\
/* Logical shift right */ \
INSTR_RA_RB_RC(lsr) \
\
/* Arithmetic shift right */ \
INSTR_RA_RB_RC(asr) \
\
\
\
/* Rotate rC left by rC bits, then store result in rA. */ \
INSTR_RA_RB_RC(rol) \
\
/* Rotate rC right by rC bits, then store result in rA. */ \
INSTR_RA_RB_RC(ror) \
\
/* Fused multiply-add */ \
/* rA = rA + (rB * rC) */ \
INSTR_RA_RB_RC(fma) \
\
/* Copy rC to rA and to rB */ \
/* If rA is the same register as rB, then the  */ \
/* register will only be written once. */ \
INSTR_RA_RB_RC(cpyp) \
\
\
\
/* Set pc to destination address in (rA + rB). */ \
INSTR_RA_RB(jumpx) \

// STore Multiple, Decrement Before
// Note that this instruction takes multiple forms
// Form 0:
	// Encoding:  10f0 oooo aaaa 0000 0000 0000 xxxx 0000
	// Effect:  
		// rX -= 4;
		// [rX] = rA;
	// Syntax:  stmdb rX, {rA}

// Form 1:
	// Encoding:  10f0 oooo aaaa bbbb 0000 0000 xxxx 0001
	// Effect:  
		// rX -= 8;
		// [rX] = rA;
		// [rX + 4] = rB;
	// Syntax:  stmdb rX, {rA, rB}

// Form 2:
	// Encoding:  10f0 oooo aaaa bbbb cccc 0000 xxxx 0010
	// Effect:  
		// rX -= 12;
		// [rX] = rA;
		// [rX + 4] = rB;
		// [rX + 8] = rC;
	// Syntax:  stmdb rX, {rA, rB, rC}

// Form 3:
	// Encoding:  10f0 oooo aaaa bbbb cccc dddd xxxx 0011
	// Effect:  
		// rX -= 16;
		// [rX] = rA;
		// [rX + 4] = rB;
		// [rX + 8] = rC;
		// [rX + 12] = rD;
	// Syntax:  stmdb rX, {rA, rB, rC, rD}



// LoaD Multiple, Increment After
// Note that this instruction takes multiple forms
// Form 0:
	// Encoding:  10f0 oooo aaaa 0000 0000 0000 xxxx 0000
	// Effect:  
		// rA = [rX]; 
		// rX += 4;
	// Syntax:  ldmia rX, {rA}

// Form 1:
	// Encoding:  10f0 oooo aaaa bbbb 0000 0000 xxxx 0001
	// Effect:  
		// rA = [rX]; 
		// rB = [rX + 4];
		// rX += 8;
	// Syntax:  ldmia rX, {rA, rB}

// Form 2:
	// Encoding:  10f0 oooo aaaa bbbb cccc 0000 xxxx 0010
	// Effect:  
		// rA = [rX]; 
		// rB = [rX + 4];
		// rC = [rX + 8];
		// rX += 12;
	// Syntax:  ldmia rX, {rA, rB, rC}

// Form 3:
	// Encoding:  10f0 oooo aaaa bbbb cccc dddd xxxx 0011
	// Effect:  
		// rA = [rX]; 
		// rB = [rX + 4];
		// rC = [rX + 8];
		// rD = [rX + 12];
		// rX += 16;
	// Syntax:  ldmia rX, {rA, rB, rC, rD}


// STore Multiple, Increment After
// Note that this instruction takes multiple forms
// Form 0:
	// Encoding:  10f0 oooo aaaa 0000 0000 0000 xxxx 0000
	// Effect:  
		// [rX] = rA;
		// rX += 4;
	// Syntax:  stmia rX, {rA}

// Form 1:
	// Encoding:  10f0 oooo aaaa bbbb 0000 0000 xxxx 0001
	// Effect:  
		// [rX] = rA;
		// [rX + 4] = rB;
		// rX += 8;
	// Syntax:  stmia rX, {rA, rB}

// Form 2:
	// Encoding:  10f0 oooo aaaa bbbb cccc 0000 xxxx 0010
	// Effect:  
		// [rX] = rA;
		// [rX + 4] = rB;
		// [rX + 8] = rC;
		// rX += 12;
	// Syntax:  stmia rX, {rA, rB, rC}

// Form 3:
	// Encoding:  10f0 oooo aaaa bbbb cccc dddd xxxx 0011
	// Effect:  
		// [rX] = rA;
		// [rX + 4] = rB;
		// [rX + 8] = rC;
		// [rX + 12] = rD;
		// rX += 16;
	// Syntax:  stmia rX, {rA, rB, rC, rD}




// Reserved for future expansion.
// Reserved for future expansion.
// Reserved for future expansion.
// Reserved for future expansion.


#endif		// group_2_instructions_hpp
