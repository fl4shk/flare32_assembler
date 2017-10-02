#ifndef lexer_class_hpp
#define lexer_class_hpp

#include "misc_includes.hpp"


#include "symbol_table_class.hpp"
#include "define_table_class.hpp"

#include "parse_node_class.hpp"
#include "warn_error_class.hpp"


namespace flare32
{

class Lexer
{
private:		// variables
	WarnError* __we = nullptr;
	SymbolTable * __builtin_sym_tbl = nullptr, * __user_sym_tbl = nullptr;
	DefineTable* __define_tbl = nullptr;
	InstructionTable* __instr_tbl = nullptr;
	FILE* __infile = nullptr;


public:		// functions
	inline Lexer(WarnError* s_we, SymbolTable* s_builtin_sym_tbl, 
		SymbolTable* s_user_sym_tbl, DefineTable* s_define_tbl,
		InstructionTable* s_instr_tbl)
		: __we(s_we), __builtin_sym_tbl(s_builtin_sym_tbl),
		__user_sym_tbl(s_user_sym_tbl), __define_tbl(s_define_tbl),
		__instr_tbl(s_instr_tbl)
	{
	}

	void need(const std::vector<ParseNode>& some_parse_vec, size_t& index, 
		PTok tok);

	void __advance_innards(int& some_next_char, 
		PTok& some_next_tok, std::string& some_next_sym_str,
		s64& some_next_num, size_t& some_line_num,
		size_t& some_outer_index, size_t& some_inner_index,
		std::vector<std::string>* some_str_vec=nullptr);
	void __lex_innards(int& some_next_char, 
		PTok& some_next_tok, PTok& some_prev_tok, 
		std::string& some_next_sym_str,
		s64& some_next_num, size_t& some_line_num,
		size_t& some_outer_index, size_t& some_inner_index,
		std::vector<std::string>* some_str_vec=nullptr,
		ParsePos* pos=nullptr);

	gen_setter_by_val(infile);



private:		// functions
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

	inline auto infile()
	{
		return __infile;
	}

	inline auto& we()
	{
		return *__we;
	}

};

}


#endif		// lexer_class_hpp
