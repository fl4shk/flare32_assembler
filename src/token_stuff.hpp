#ifndef token_stuff_hpp
#define token_stuff_hpp

#include "misc_includes.hpp"


namespace assembler
{

typedef int tok;

// Pre-defined tokens
enum class tok_defn : tok
{
	ident = 9001,
	number,
	
	
	instr_noargs,
	instr_ra,
	instr_ra_rb,
	instr_ra_imm16u,
	instr_imm16u,
	instr_imm16s,
	instr_flags,
	instr_ra_flags,
	instr_flags_ra,
	instr_ira,
	instr_ira_ra,
	instr_ra_ira,
	instr_ra_pc,
	instr_ra_rb_imm16u,
	instr_ra_rb_imm16s,
	instr_ra_rb_rc_imm12s,
	instr_ra_rb_rc,
	instr_ra_rb_abs,
	
	
	// add.f rA, rB
	// add.f rA, rB, rC
	dot_f,
	
};


}

#endif		// token_stuff_hpp
