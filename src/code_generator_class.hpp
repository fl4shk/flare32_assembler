#ifndef code_generator_class_hpp
#define code_generator_class_hpp

#include "misc_includes.hpp"


#include "symbol_table_class.hpp"
#include "define_table_class.hpp"

#include "parse_node_class.hpp"
#include "warn_error_class.hpp"

namespace flare32
{

class CodeGenerator
{
private:		// variables
	WarnError* __we = nullptr;
	size_t * __addr = nullptr, * __last_addr = nullptr;
	s32* __pass = nullptr;
	s32 last_pass;
	SymbolTable * __builtin_sym_tbl = nullptr, * __user_sym_tbl = nullptr;
	DefineTable* __define_tbl = nullptr;
	InstructionTable* __instr_tbl = nullptr;
	
public:		// functions
	inline CodeGenerator(WarnError* s_we, size_t* s_addr,
		size_t* s_last_addr, s32* s_pass, s32 s_last_pass,
		SymbolTable* s_builtin_sym_tbl, SymbolTable* s_user_sym_tbl,
		DefineTable* s_define_tbl, InstructionTable* s_instr_tbl)
		: __we(s_we), __addr(s_addr), __last_addr(s_last_addr),
		__pass(s_pass), last_pass(s_last_pass),
		__builtin_sym_tbl(s_builtin_sym_tbl),
		__user_sym_tbl(s_user_sym_tbl), __define_tbl(s_define_tbl),
		__instr_tbl(s_instr_tbl)
	{
	}

	// Code generator stuff
	inline void __encode_instr_group(u16& high_hword, PInstr instr) const
	{
		clear_and_set_bits_with_range(high_hword, instr->enc_group(),
			15, 14);
	}
	inline void __encode_affects_flags(u16& high_hword, PInstr instr) const
	{
		clear_and_set_bits_with_range(high_hword, instr->affects_flags(),
			13, 13);
	}
	void __encode_opcode(u16& high_hword, PInstr instr) const;
	void __encode_high_hword(u16& high_hword, 
		const std::vector<std::string>& regs, s64 expr_result,
		PInstr instr);
	void __encode_low(u16& g1g2_low, u32& g3_low, 
		const std::vector<std::string>& regs, s64 expr_result,
		PInstr instr);
	void __gen_low(u16 g1g2_low, u32 g3_low, PInstr instr);
	void encode_and_gen(const std::vector<std::string>& regs, 
		s64 expr_result, PInstr instr);

	void gen8(s32 v);
	void gen16(s32 v);
	void gen32(s32 v);

private:		// functions

	inline auto& we()
	{
		return *__we;
	}

	inline auto addr()
	{
		return *__addr;
	}

	inline auto last_addr()
	{
		return *__last_addr;
	}

	inline auto& set_addr(size_t n_addr)
	{
		*__addr = n_addr;
		return *__addr;
	}
	inline auto& set_last_addr(size_t n_last_addr)
	{
		*__last_addr = n_last_addr;
		return *__last_addr;
	}

	inline auto pass()
	{
		return *__pass;
	}

	inline auto& builtin_sym_tbl()
	{
		return *__builtin_sym_tbl;
	}

	inline auto& user_sym_tbl()
	{
		return *__user_sym_tbl;
	}

	inline auto& define_tbl()
	{
		return *__define_tbl;
	}

	inline auto& instr_tbl()
	{
		return *__instr_tbl;
	}


};

}


#endif		// code_generator_class_hpp
