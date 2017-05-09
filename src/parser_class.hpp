#ifndef parser_class_hpp
#define parser_class_hpp

#include "lexer_class.hpp"


namespace assembler
{

class parser
{
private:		// variables
	std::vector<string_view> internal_args_vec;
	size_t internal_pass = 0;
	
	std::FILE* infile;
	
	lexer lex;
	symbol_table sym_tbl;
	warn_error we;
	
	
private:		// functions
	gen_setter_by_val(pass);
	
	int expr();
	int unary();
	
	
public:		// functions
	parser( int argc, char** argv, std::FILE* s_infile );
	
	virtual ~parser();
	
	
	int run();
	
	gen_getter_by_con_ref(args_vec);
	gen_getter_by_val(pass);
	
};



}


#endif		// parser_class_hpp
