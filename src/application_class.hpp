#ifndef application_class_hpp
#define application_class_hpp


#include "misc_includes.hpp"


#include "symbol_table_class.hpp"

class Application
{
private:		// classes

private:		// variables
	SymbolTable __sym_tbl, __user_sym_tbl;

	size_t __line_num = 1;

	int __next_char = ' ';
	PTok __next_tok = nullptr;
	std::string __next_sym_str;
	s64 __next_num = -1;

public:		// functions
	Application();

	int operator () ();



private:		// functions
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
	void expected(PTok tok) const
	{
		expected("token of type \"", tok->str(), "\"!");
	}
	void need(PTok tok);

	void advance();

	void lex();

	void parse();



	s64 handle_term();
	s64 handle_factor();
	s64 handle_expr();

	bool next_tok_is_punct() const;



	gen_getter_by_ref(sym_tbl)
	gen_getter_by_ref(user_sym_tbl)

	gen_getter_by_val(line_num)
	gen_getter_by_val(next_char)
	gen_getter_by_val(next_tok)
	gen_getter_by_con_ref(next_sym_str)
	gen_getter_by_val(next_num)


	gen_setter_by_val(line_num)
	gen_setter_by_val(next_char)
	gen_setter_by_val(next_tok)
	gen_setter_by_con_ref(next_sym_str)
	gen_setter_by_val(next_num);


};


#endif		// application_class_hpp
