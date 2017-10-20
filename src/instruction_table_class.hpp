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
	NoArgs,
	UImm16,
	SImm16,
	Imm32,

	Ra,
	RaUImm16,
	RaRb,
	RaRbUImm16,
	RaRbSImm16,
	RaRbRc,
	RaRbRcSImm12,

	LdStRaRb,
	LdStRaRbRcSImm12,
	LdStRaRbRc,
	LdStRaRbSImm12,

	Branch,


	LdStRaRbImm32,
	RaRbImm32,

	// Block moves (ldmia, stmia, stmdb) with number of {} args
	LdStBlock1To4,
	LdStBlock5To8,

	Ira,
	RaIra,
	IraRa,

	RaFlags,
	Flags,
	FlagsRa,

	RaPc,


	// umul, smul
	// 
	// umul rA:rB, rC, rD
	// smul rA:rB, rC, rD
	LongMul,

	// udivmod, sdivmod
	// 
	// udivmod rA:rB, rC:rD, rE:rF, rG:rH
	// sdivmod rA:rB, rC:rD, rE:rF, rG:rH
	LongDivMod,


	// udivmod, sdivmod
	// 
	// udivmod rA, rB, rC, rD
	// sdivmod rA, rB, rC, rD
	DivMod,


	// lsl, lsr, asr with 64-bit arguments
	// 
	// lsl rA:rB, rC:rD, rE:rF
	// lsr rA:rB, rC:rD, rE:rF
	// asr rA:rB, rC:rD, rE:rF
	LongBitShift,



	//PseudoLdStRaImm32,

	//PseudoRb,
	//PseudoRbImm,
	//PseudoRbRc,
	//PseudoRbRcImm,
	//PseudoRaRc,
	//PseudoPcRb,


	//// Block-move style push and pop
	//PseudoLdStStackBlock1To4,
	//PseudoLdStStackBlock5To8,
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
	inline Instruction() : Instruction("", 0, InstrArgs::NoArgs, -1)
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

	static const Instruction 
		LIST_OF_INSTRUCTIONS(INSTR_STUFF)

		Dummy;

	#undef INSTR_STUFF

	static const std::vector<PInstr> instr_g0_vec, instr_g1_vec,
		instr_g2_vec, instr_g3_vec;

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
