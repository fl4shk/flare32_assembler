#ifndef assembler_class_hpp
#define assembler_class_hpp


#include "misc_includes.hpp"


#include "symbol_table_class.hpp"


namespace flare32
{

class Assembler
{
private:		// classes

private:		// variables
	SymbolTable __builtin_sym_tbl, __user_sym_tbl;
	InstructionTable __instr_tbl;

	// Where are we in the file?
	size_t __addr = 0;
	size_t __line_num = 1;

	int __next_char = ' ';
	PTok __next_tok = nullptr;
	std::string __next_sym_str;
	s64 __next_num = -1;

	//bool __changed = false;
	s32 __pass = 0;

	char* __input_filename = nullptr;
	std::FILE* __infile = nullptr;

public:		// functions
	Assembler(char* s_input_filename);

	int operator () ();



private:		// functions
	gen_getter_by_ref(builtin_sym_tbl)
	gen_getter_by_ref(user_sym_tbl)
	gen_getter_by_ref(instr_tbl)

	gen_getter_and_setter_by_val(addr)
	gen_getter_and_setter_by_val(line_num)
	gen_getter_and_setter_by_val(next_char)
	gen_getter_and_setter_by_val(next_tok)
	gen_getter_and_setter_by_con_ref(next_sym_str)
	gen_getter_and_setter_by_val(next_num)
	//gen_getter_and_setter_by_val(changed)
	gen_getter_and_setter_by_val(pass)
	gen_getter_and_setter_by_val(input_filename)
	gen_getter_and_setter_by_val(infile)

	void reinit();
	void fill_builtin_sym_tbl();

	template<typename... ArgTypes>
	void err_suffix(ArgTypes&&... args) const
	{
		printerr(", On line ", line_num(), ":  ", args..., "\n");
		exit(1);
	}
	template<typename... ArgTypes>
	void err(ArgTypes&&... args) const
	{
		printerr("Error");
		err_suffix(args...);
	}

	template<typename... ArgTypes>
	void expected(ArgTypes&&... args) const
	{
		err("Expected ", args...);
	}


	void __expected_tokens_innards() const
	{
	}
	template<typename... RemArgTypes>
	void __expected_tokens_innards(PTok tok, RemArgTypes&&... rem_args)
		const
	{
		printerr("\"", tok->str(), "\"");

		if (sizeof...(rem_args) > 0)
		{
			printerr(" or ");
			__expected_tokens_innards(rem_args...);
		}
	}
	
	template<typename... ArgTypes>
	void expected_tokens(ArgTypes&&... args) const
	{
		printerr("Expected token of type ");
		__expected_tokens_innards(args...);
		printerr("!\n");
		exit(1);
	}


	void need(PTok tok);

	void advance();
	void lex();

	void line();


	s64 handle_term();
	s64 handle_factor();
	s64 handle_expr();

	bool tok_is_punct(PTok some_tok) const;
	bool tok_is_ident_ish(PTok some_tok) const;

	inline bool next_tok_is_punct() const
	{
		return tok_is_punct(next_tok());
	}
	inline bool next_tok_is_ident_ish() const
	{
		return tok_is_ident_ish(next_tok());
	}


};

}

#endif		// assembler_class_hpp
