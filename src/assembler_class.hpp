#ifndef assembler_class_hpp
#define assembler_class_hpp

#include "lexer_class.hpp"


namespace navichip32
{

class assembler
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
	
	s32 expr();
	s32 unary();
	
	s32 reg();
	s32 immed16u();
	s32 immed16s();
	s32 immed12s();
	s32 absolute();
	s32 line();
	
	
public:		// functions
	assembler( int argc, char** argv, std::FILE* s_infile );
	
	virtual ~assembler();
	
	
	int run();
	
	gen_getter_by_con_ref(args_vec);
	gen_getter_by_val(pass);
	
};



}


#endif		// assembler_class_hpp
