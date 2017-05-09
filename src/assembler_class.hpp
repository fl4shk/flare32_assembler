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
	
	s32 mask_immed( s32 to_mask, size_t mask );
	
	s32 reg();
	
	inline s32 immed16()
	{
		return mask_immed( expr(), ( ( 1 << 16 ) - 1 ) );
	}
	inline s32 immed12()
	{
		return mask_immed( expr(), ( ( 1 << 12 ) - 1 ) );
	}
	inline s32 absolute()
	{
		return expr();
	}
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
