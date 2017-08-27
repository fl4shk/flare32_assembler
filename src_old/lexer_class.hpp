#ifndef lexer_class_hpp
#define lexer_class_hpp

#include "token_stuff_etc.hpp"
#include "symbol_table_class.hpp"
//#include "warn_error_stuff.hpp"

namespace flare32
{

class warn_error;


class lexer
{
private:		// variables
	std::FILE* internal_infile = nullptr;
	warn_error* internal_we = nullptr;
	size_t* internal_pass = nullptr;
	
	// Symbol table with contents from program being assembled (labels,
	// etc.)
	symbol_table* internal_user_sym_tbl = nullptr;
	
	// Symbol table with contents constant across runs of the assembler
	symbol_table* internal_special_sym_tbl = nullptr;
	
	size_t internal_lineno = 1;
	
	
	tok internal_nextc = ' ';
	
	tok internal_nextt = ' ';
	s32 internal_nextval = 0;
	symbol* internal_nextsym = nullptr;
	
	tok internal_special_nextt = ' ';
	s32 internal_special_nextval = 0;
	symbol* internal_special_nextsym = nullptr;
	
	
private:		// functions
	tok advance( bool lineno );
	
	void eat_ws( bool keep_lineno );
	void lex_no_ws( bool keep_lineno );
	
	gen_setter_by_val(infile);
	gen_setter_by_val(we);
	gen_setter_by_val(pass);
	gen_setter_by_val(user_sym_tbl);
	gen_setter_by_val(special_sym_tbl);
	
	
	
public:		// functions
	inline lexer( std::FILE* s_infile, warn_error* s_we, size_t* s_pass,
		symbol_table* s_user_sym_tbl, symbol_table* s_special_sym_tbl )
	{
		init( s_infile, s_we, s_pass, s_user_sym_tbl, s_special_sym_tbl );
	}
	virtual inline ~lexer()
	{
	}
	
	void init( std::FILE* s_infile, warn_error* s_we, size_t* s_pass,
		symbol_table* s_user_sym_tbl, symbol_table* s_special_sym_tbl );
	
	bool match( tok typ, bool keep_lineno );
	bool match_no_ws( tok typ, bool keep_lineno );
	void assume( tok typ, bool keep_lineno );
	
	inline void operator () ( bool keep_lineno )
	{
		eat_ws(keep_lineno);
		lex_no_ws(keep_lineno);
	}
	
	
	gen_setter_by_val(nextc);
	gen_setter_by_val(nextt);
	gen_setter_by_val(nextval);
	gen_setter_by_val(nextsym);
	gen_setter_by_val(special_nextt);
	gen_setter_by_val(special_nextval);
	gen_setter_by_val(special_nextsym);
	gen_setter_by_val(lineno);
	
	
	gen_getter_by_val(infile);
	gen_getter_by_val(we);
	inline size_t pass() const
	{
		return *internal_pass;
	}
	gen_getter_by_val(user_sym_tbl);
	gen_getter_by_val(special_sym_tbl);
	gen_getter_by_val(lineno);
	gen_getter_by_val(nextc);
	gen_getter_by_val(nextt);
	gen_getter_by_val(nextval);
	gen_getter_by_val(nextsym);
	gen_getter_by_val(special_nextt);
	gen_getter_by_val(special_nextval);
	gen_getter_by_val(special_nextsym);
	
};


}

#include "warn_error_stuff.hpp"


#endif		// lexer_class_hpp
