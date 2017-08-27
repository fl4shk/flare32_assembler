#ifndef instruction_class_hpp
#define instruction_class_hpp

#include "misc_includes.hpp"


#include "group_0_instructions.hpp"
#include "group_1_instructions.hpp"
#include "group_2_instructions.hpp"
#include "group_3_instructions.hpp"



namespace flare32
{


enum class InstrArgs
{
	no_args,
	uimm16,
	simm16,
	imm32,

	ra,
	ra_rb,
	ra_rb_uimm16,
	ra_rb_simm16,
	ra_rb_rc,
	ra_rb_rc_simm12,

	ldst_ra_rb_rc_simm12,
	ldst_ra_rb_rc,
	ldst_ra_rb_simm12,
	ldst_ra_rb,
	ldst_generic_ra_rb_rc_simm12,


	// Block moves (ldmia, stmia, stmdb) with number of {} args
	ldst_block_1,
	ldst_block_2,
	ldst_block_3,
	ldst_block_4,
	ldst_block_5,
	ldst_block_6,
	ldst_block_7,
	ldst_block_8,

	ira,
	ra_ira,
	ira_ra,

	ra_flags,
	flags,
	flags_ra,

	ra_pc,

	//pseudo_ldst_ra_imm32,

	//pseudo_rb,
	//pseudo_rb_imm,
	//pseudo_rb_rc,
	//pseudo_rb_rc_imm,
	//pseudo_ra_rc,
	//pseudo_pc_rb,


	//// Block-move style push and pop
	//pseudo_ldst_stack_block_1,
	//pseudo_ldst_stack_block_2,
	//pseudo_ldst_stack_block_3,
	//pseudo_ldst_stack_block_4,
	//pseudo_ldst_stack_block_5,
	//pseudo_ldst_stack_block_6,
	//pseudo_ldst_stack_block_7,
	//pseudo_ldst_stack_block_8,
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
