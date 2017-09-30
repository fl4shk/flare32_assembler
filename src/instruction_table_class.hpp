#ifndef instruction_table_hpp
#define instruction_table_hpp

#include "misc_includes.hpp"


#include "group_0_instructions.hpp"
#include "group_1_instructions.hpp"
#include "group_2_instructions.hpp"
#include "group_3_instructions.hpp"

// Non-pseudo instructions
#define LIST_OF_INSTRUCTIONS(INSTR_STUFF) \
	LIST_OF_GROUP_0_INSTRUCTIONS(INSTR_STUFF) \
	LIST_OF_GROUP_1_INSTRUCTIONS(INSTR_STUFF) \
	LIST_OF_GROUP_2_INSTRUCTIONS(INSTR_STUFF) \
	LIST_OF_GROUP_3_INSTRUCTIONS(INSTR_STUFF)

namespace flare32
{


enum class InstrArgs
{
	no_args,
	uimm16,
	simm16,
	imm32,

	ra,
	ra_uimm16,
	ra_rb,
	ra_rb_uimm16,
	ra_rb_simm16,
	ra_rb_rc,
	ra_rb_rc_simm12,

	ldst_ra_rb,
	ldst_ra_rb_rc_simm12,
	ldst_ra_rb_rc,
	ldst_ra_rb_simm12,

	branch,


	ldst_ra_rb_imm32,
	ra_rb_imm32,


	// Block moves (ldmia, stmia, stmdb) with number of {} args
	ldst_block_1_to_4,
	ldst_block_5_to_8,

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
	//pseudo_ldst_stack_block_1_to_4,
	//pseudo_ldst_stack_block_5_to_8,
};





class Instruction;
typedef const Instruction* PInstr;

class Instruction
{
private:		// variables
	std::string __str;
	bool __affects_flags;
	InstrArgs __args;
	s32 __enc_group;


public:		// constants
	inline Instruction() : Instruction("", 0, InstrArgs::no_args, -1)
	{
	}
	inline Instruction(const std::string& s_str, bool s_affects_flags,
		InstrArgs s_args, s32 s_enc_group) : __str(s_str), 
		__affects_flags(s_affects_flags), __args(s_args),
		__enc_group(s_enc_group)
	{
	}
	inline Instruction(std::string&& s_str, bool s_affects_flags,
		InstrArgs s_args, s32 s_enc_group) : __str(std::move(s_str)), 
		__affects_flags(s_affects_flags), __args(s_args),
		__enc_group(s_enc_group)
	{
	}

	inline Instruction(const Instruction& to_copy) = default;
	inline Instruction(Instruction&& to_move) = default;

	inline Instruction& operator = (const Instruction& to_copy) = default;
	inline Instruction& operator = (Instruction&& to_move) = default;

	gen_getter_by_con_ref(str)
	gen_getter_by_val(affects_flags)
	gen_getter_by_val(args)
	gen_getter_by_val(enc_group)

};

class InstructionTable
{
private:		// variables
	std::map<std::string, std::vector<PInstr>> __table;

public:		// static constant variables
	#define INSTR_STUFF(enc_group, args, varname, value) \
	varname##_##args##_##enc_group,

	#define INSTR_STUFF_AFFECTS_FLAGS(enc_group, args, varname, value) \
	varname##_##args##_##enc_group##_affects_flags,

	static const Instruction 
		LIST_OF_INSTRUCTIONS(INSTR_STUFF)

		LIST_OF_INSTRUCTIONS(INSTR_STUFF_AFFECTS_FLAGS)

		Dummy;

	#undef INSTR_STUFF
	#undef INSTR_STUFF_AFFECTS_FLAGS

	static const std::vector<PInstr> instr_g0_vec, instr_g1_vec,
		instr_g2_vec, instr_g3_vec;

	//static const std::vector<PInstr> instr_vec;
	static const std::vector<const std::vector<PInstr>*> instr_vec;

public:		// functions
	InstructionTable();

	inline const std::vector<PInstr>& at
		(const std::string& some_name) const
	{
		return __table.at(some_name);
	}

	inline bool contains(const std::string& some_name) const
	{
		return (__table.count(some_name) == 1);
	}


};


}

#endif		// instruction_table_hpp
