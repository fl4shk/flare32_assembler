#ifndef token_stuff_etc_hpp
#define token_stuff_etc_hpp

#include "misc_includes.hpp"


namespace navichip32
{

typedef int32_t tok;

// Pre-defined tokens
enum class tok_defn : tok
{
	reg = 9001,
	ident,
	//bad_ident,
	number,
	
	instr,
};

enum class instr_args : tok
{
	noargs = 9001,
	ra,
	ra_rb,
	ra_imm16u,
	imm16u,
	imm16s,
	flags,
	ra_flags,
	flags_ra,
	ira,
	ira_ra,
	ra_ira,
	ra_pc,
	ra_rb_imm16u,
	ra_rb_imm16s,
	ra_rb_rc_imm12s,
	ra_rb_rc,
	ra_rb_abs,
};

}

#endif		// token_stuff_etc_hpp
