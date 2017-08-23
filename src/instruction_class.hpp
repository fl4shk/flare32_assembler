#ifndef instruction_class_hpp
#define instruction_class_hpp

#include "misc_includes.hpp"


#include "group_0_instructions.hpp"
#include "group_1_instructions.hpp"
#include "group_2_instructions.hpp"
#include "group_3_instructions.hpp"



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


	ldst_block_rx_ra,
	ldst_block_rx_ra_rb,
	ldst_block_rx_ra_rb_rc,
	ldst_block_rx_ra_rb_rc_rd,
	ldst_block_rx_ra_rb_rc_rd_re,
	ldst_block_rx_ra_rb_rc_rd_re_rf,
	ldst_block_rx_ra_rb_rc_rd_re_rf_rg,
	ldst_block_rx_ra_rb_rc_rd_re_rf_rg_rh,

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
	pseudo_pc_rb,


	// Block-move style push and pop
	pseudo_ldst_stack_block_ra,
	pseudo_ldst_stack_block_ra_rb,
	pseudo_ldst_stack_block_ra_rb_rc,
	pseudo_ldst_stack_block_ra_rb_rc_rd,
	pseudo_ldst_stack_block_ra_rb_rc_rd_re,
	pseudo_ldst_stack_block_ra_rb_rc_rd_re_rf,
	pseudo_ldst_stack_block_ra_rb_rc_rd_re_rf_rg,
	pseudo_ldst_stack_block_ra_rb_rc_rd_re_rf_rg_rh,
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
