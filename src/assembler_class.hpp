#ifndef assembler_class_hpp
#define assembler_class_hpp

#include "lexer_class.hpp"
#include "instruction_table_class.hpp"


namespace navichip32
{


class assembler
{
private:		// variables
	std::vector<string_view> internal_args_vec;
	size_t internal_pass = 0;
	
	// Code generator stuff
	unsigned int internal_lc = 0;
	unsigned int internal_last_lc = -1;
	bool internal_changed = false;
	
	
	// Input file
	std::FILE* infile;
	
	// Class instances
	lexer lex;
	warn_error we;
	symbol_table user_sym_tbl;
	symbol_table special_sym_tbl;
	instruction_table instr_tbl;
	
	
private:		// functions
	gen_setter_by_val(pass);
	gen_setter_by_val(lc);
	gen_setter_by_val(last_lc);
	gen_setter_by_val(changed);
	
	// Constructor stuff
	void insert_grp_0_instructions();
	void insert_grp_1_instructions();
	void insert_grp_2_instructions();
	void insert_grp_3_instructions();
	
	// Code generator stuff
	void genb( s32 v );
	void gen( s32 v );
	
	
	// Parser stuff
	const instruction* determine_instr();
	s32 unary();
	s32 expr();
	
	s32 mask_immed( s32 to_mask, size_t mask );
	
	s32 reg();
	
	s32 braoffs();
	s32 immed16();
	s32 immed12();
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
	gen_getter_by_val(lc);
	gen_getter_by_val(last_lc);
	gen_getter_by_val(changed);
	
};



}


#endif		// assembler_class_hpp
