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


/* Load 32-bit value from address (rB + rC + (sign-extended imm)) into 
rA. */ \
INSTR_LDST_RA_RB_RC_IMM(ldr) \

/* Load zero-extended 16-bit value from address (rB + rC + (sign-extended
imm)) into rA. */ \
/* This zero-extends the value. */ \
INSTR_LDST_RA_RB_RC_IMM(ldh) \

/* Load sign-extended 16-bit value from address (rB + rC + (sign-extended
imm)) into rA. */ \
/* This sign-extends the value. */ \
INSTR_LDST_RA_RB_RC_IMM(ldsh) \

/* Load zero-extended 8-bit value from address (rB + rC + (sign-extended
 imm)) into rA. */ \
/* This zero-extends the value. */ \
INSTR_LDST_RA_RB_RC_IMM(ldb) \



/* Load sign-extended 8-bit value from address (rB + rC + (sign-extended
imm)) into rA. */ \
/* This sign-extends the value. */ \
INSTR_LDST_RA_RB_RC_IMM(ldsb) \

/* Store 32-bit value in rA to address (rB + rC + (sign-extended 
imm)). */ \
INSTR_LDST_RA_RB_RC_IMM(str) \

/* Store low 16 bits of rA to address (rB + rC + (sign-extended imm)). */ \
INSTR_LDST_RA_RB_RC_IMM(sth) \

/* Store low 8 bits of rA to address (rB + rC + (sign-extended imm)). */ \
INSTR_LDST_RA_RB_RC_IMM(stb) \


/* rA = rB + rC */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_RC(add) \

/* rA = rB + rC + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_RC(adc) \

/* rA = rB - rC */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_RC(sub) \

/* rA = rB + (~rC) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_RC(sbc) \



/* rA = rC - rB */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_RA_RB_RC(rsb) \

/* rA = rB * rC */ \
INSTR_RA_RB_RC(mul) \

/* rA = rB & rC */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_RC(and) \

/* rA = rB | rC */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_RC(or) \



/* rA = rB ^ rC */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_RA_RB_RC(xor) \

/* Logical shift left */ \
/* rA = rB << rC */ \
INSTR_RA_RB_RC(lsl) \

/* Logical shift right */ \
INSTR_RA_RB_RC(lsr) \

/* Arithmetic shift right */ \
INSTR_RA_RB_RC(asr) \



/* Rotate rC left by rC bits, then store result in rA. */ \
INSTR_RA_RB_RC(rol) \

/* Rotate rC right by rC bits, then store result in rA. */ \
INSTR_RA_RB_RC(ror) \

/* Fused multiply-add */ \
/* rA = rA + (rB * rC) */ \
INSTR_RA_RB_RC(fma) \

/* Copy rC to rA and to rB */ \
/* If rA is the same register as rB, then the  */ \
/* register will only be written once. */ \
INSTR_RA_RB_RC(cpyp) \



/* STore Multiple, Decrement Before */ \
/* Note that this instruction takes multiple forms */ \
/* Form 0: */ \
	/* Encoding:  10f0 oooo aaaa 0000 0000 0000 xxxx 0000  */ \
	/* Effect:    */ \
		/* rX -= 4;  */ \
		/* [rX] = rA;  */ \
	/* Syntax:  stmdb rX, {rA} */ \

/* Form 1: */ \
	/* Encoding:  10f0 oooo aaaa bbbb 0000 0000 xxxx 0001  */ \
	/* Effect:    */ \
		/* rX -= 8;  */ \
		/* [rX] = rA;  */ \
		/* [rX + 4] = rB;  */ \
	/* Syntax:  stmdb rX, {rA, rB} */ \

/* Form 2: */ \
	/* Encoding:  10f0 oooo aaaa bbbb cccc 0000 xxxx 0010  */ \
	/* Effect:    */ \
		/* rX -= 12;  */ \
		/* [rX] = rA;  */ \
		/* [rX + 4] = rB;  */ \
		/* [rX + 8] = rC;  */ \
	/* Syntax:  stmdb rX, {rA, rB, rC} */ \

/* Form 3: */ \
	/* Encoding:  10f0 oooo aaaa bbbb cccc dddd xxxx 0011  */ \
	/* Effect:    */ \
		/* rX -= 16;  */ \
		/* [rX] = rA;  */ \
		/* [rX + 4] = rB;  */ \
		/* [rX + 8] = rC;  */ \
		/* [rX + 12] = rD;  */ \
	/* Syntax:  stmdb rX, {rA, rB, rC, rD} */ \



/* LoaD Multiple, Increment After */ \
/* Note that this instruction takes multiple forms */ \
/* Form 0: */ \
	/* Encoding:  10f0 oooo aaaa 0000 0000 0000 xxxx 0000  */ \
	/* Effect:    */ \
		/* rA = [rX];   */ \
		/* rX += 4;  */ \
	/* Syntax:  ldmia rX, {rA} */ \

/* Form 1: */ \
	/* Encoding:  10f0 oooo aaaa bbbb 0000 0000 xxxx 0001  */ \
	/* Effect:    */ \
		/* rA = [rX];   */ \
		/* rB = [rX + 4];  */ \
		/* rX += 8;  */ \
	/* Syntax:  ldmia rX, {rA, rB} */ \

/* Form 2: */ \
	/* Encoding:  10f0 oooo aaaa bbbb cccc 0000 xxxx 0010  */ \
	/* Effect:    */ \
		/* rA = [rX];   */ \
		/* rB = [rX + 4];  */ \
		/* rC = [rX + 8];  */ \
		/* rX += 12;  */ \
	/* Syntax:  ldmia rX, {rA, rB, rC} */ \

/* Form 3: */ \
	/* Encoding:  10f0 oooo aaaa bbbb cccc dddd xxxx 0011  */ \
	/* Effect:    */ \
		/* rA = [rX];   */ \
		/* rB = [rX + 4];  */ \
		/* rC = [rX + 8];  */ \
		/* rD = [rX + 12];  */ \
		/* rX += 16;  */ \
	/* Syntax:  ldmia rX, {rA, rB, rC, rD} */ \


/* STore Multiple, Increment After */ \
/* Note that this instruction takes multiple forms */ \
/* Form 0: */ \
	/* Encoding:  10f0 oooo aaaa 0000 0000 0000 xxxx 0000  */ \
	/* Effect:    */ \
		/* [rX] = rA;  */ \
		/* rX += 4;  */ \
	/* Syntax:  stmia rX, {rA} */ \

/* Form 1: */ \
	/* Encoding:  10f0 oooo aaaa bbbb 0000 0000 xxxx 0001  */ \
	/* Effect:    */ \
		/* [rX] = rA;  */ \
		/* [rX + 4] = rB;  */ \
		/* rX += 8;  */ \
	/* Syntax:  stmia rX, {rA, rB} */ \

/* Form 2: */ \
	/* Encoding:  10f0 oooo aaaa bbbb cccc 0000 xxxx 0010  */ \
	/* Effect:    */ \
		/* [rX] = rA;  */ \
		/* [rX + 4] = rB;  */ \
		/* [rX + 8] = rC;  */ \
		/* rX += 12;  */ \
	/* Syntax:  stmia rX, {rA, rB, rC} */ \

/* Form 3: */ \
	/* Encoding:  10f0 oooo aaaa bbbb cccc dddd xxxx 0011  */ \
	/* Effect:    */ \
		/* [rX] = rA;  */ \
		/* [rX + 4] = rB;  */ \
		/* [rX + 8] = rC;  */ \
		/* [rX + 12] = rD;  */ \
		/* rX += 16;  */ \
	/* Syntax:  stmia rX, {rA, rB, rC, rD} */ \

/* ENable Interrupts */ \
INSTR_NO_ARGS(eni) \



/* DIsable Interrupts */ \
INSTR_NO_ARGS(dii) \

/* Set the PC to interrupt RETurn address and enable Interrupts */ \
INSTR_NO_ARGS(reti) \

/* Set the PC to the Interrupt Return Address, but DON'T enable */ \
/* interrupts */ \
INSTR_IRA(jump) \

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
// Form 0:
	// Encoding:  10f0 oooo aaaa 0000 0000 0000 1111 0000
	// Encoded like this:  ldmia sp, {rA}
	// Effect:  
		// rA = [sp];
		// sp += 4;
	// Syntax:  pop rA

// Form 1:
	// Encoding:  10f0 oooo aaaa bbbb 0000 0000 1111 0001
	// Encoded like this:  ldmia sp, {rA, rB}
	// Effect:  
		// rA = [sp];
		// rB = [sp + 4];
		// sp += 8;
	// Syntax:  pop rA, rB

// Form 2:
	// Encoding:  10f0 oooo aaaa bbbb cccc 0000 1111 0010
	// Encoded like this:  ldmia sp, {rA, rB, rC}
	// Effect:  
		// rA = [sp];
		// rB = [sp + 4];
		// rC = [sp + 8];
		// sp += 12;
	// Syntax:  pop rA, rB, rC

// Form 3:
	// Encoding:  10f0 oooo aaaa bbbb cccc dddd 1111 0011
	// Encoded like this:  ldmia sp, {rA, rB, rC, rD}
	// Effect:  
		// rA = [sp];
		// rB = [sp + 4];
		// rC = [sp + 8];
		// rD = [sp + 12];
		// sp += 16;
	// Syntax:  pop rA, rB, rC, rD


// Pseudo instruction:
// Push
// Note that this instruction takes multiple forms
// Form 0:
	// Encoding:  10f0 oooo aaaa 0000 0000 0000 xxxx 0000
	// Encoded like this:  stmdb sp, {rA}
	// Effect:  
		// sp -= 4;
		// [sp] = rA;
	// Syntax:  push rA

// Form 1:
	// Encoding:  10f0 oooo aaaa bbbb 0000 0000 xxxx 0001
	// Encoded like this:  stmdb sp, {rA, rB}
	// Effect:  
		// sp -= 8;
		// [sp] = rA;
		// [sp + 4] = rB;
	// Syntax:  push rA, rB

// Form 2:
	// Encoding:  10f0 oooo aaaa bbbb cccc 0000 xxxx 0010
	// Encoded like this:  stmdb sp, {rA, rB, rC}
	// Effect:  
		// sp -= 12;
		// [sp] = rA;
		// [sp + 4] = rB;
		// [sp + 8] = rC;
	// Syntax:  push rA, rB, rC

// Form 3:
	// Encoding:  10f0 oooo aaaa bbbb cccc dddd xxxx 0011
	// Effect:  
	// Encoded like this:  stmdb sp, {rA, rB, rC, rD}
		// sp -= 16;
		// [sp] = rA;
		// [sp + 4] = rB;
		// [sp + 8] = rC;
		// [sp + 12] = rD;
	// Syntax:  push rA, rB, rC, rD


#endif		// group_2_instructions_hpp
