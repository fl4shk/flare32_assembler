#ifndef token_stuff_etc_hpp
#define token_stuff_etc_hpp

#include "misc_includes.hpp"


namespace navichip32
{

typedef s32 tok;

// Pre-defined tokens
enum class tok_defn : tok
{
	reg = 9001,
	reg_flags,
	reg_ira,
	reg_pc,
	instr,
	
	
	ident,
	number,
	
	
	lim_tok_defn,
};

enum class instr_args : tok
{
	noargs = 9001,
	ra,
	ra_rb,
	ra_imm16u,
	
	
	imm16u,
	imm16s,
	branchoffset,
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
	
	
	pseudo_r0hidden_rb,
	pseudo_r0hidden_rb_imm16u,
	
	// cpn rA, rB
	pseudo_ra_rb_imm0hidden,
	
	// cpc rA, rB
	pseudo_ra_rb_imm16sneg1hidden,
	
	pseudo_ra_rb_r0hidden_imm0hidden,
	pseudo_ra_rb_rc_imm0hidden,
	pseudo_ra_rb_r0hidden_imm12s,
	pseudo_r0hidden_rb_rc,
	
	
	pseudo_ra_rahidden_rc,
	
	// cpy pc, rB
	pseudo_pc_rb,
	
	pseudo_ra_sphidden,
	
	
	pseudo_ra_r0hidden_abs,
	pseudo_r0hidden_r0hidden_abs,
	pseudo_ra_rahidden_abs,
	
};


template< typename typ_type >
inline tok cast_typ( typ_type typ )
{
	return static_cast<tok>(typ);
}

}

#endif		// token_stuff_etc_hpp
