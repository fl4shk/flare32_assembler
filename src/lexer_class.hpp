#ifndef lexer_class_hpp
#define lexer_class_hpp

#include "token_stuff_etc.hpp"
#include "symbol_table_class.hpp"
//#include "warn_error_stuff.hpp"

namespace navichip32
{

class warn_error;


class lexer
{
private:		// variables
	std::FILE* internal_infile = nullptr;
	warn_error* internal_we = nullptr;
	size_t* internal_pass = nullptr;
	symbol_table* internal_sym_tbl = nullptr;
	size_t internal_lineno = 1;
	tok internal_nextc = ' ';
	tok internal_nextt = ' ';
	int32_t internal_nextval = 0;
	symbol* internal_nextsym = nullptr;
	
	
	
private:		// functions
	tok advance();
	
	void eat_ws();
	tok lex_no_ws();
	
	gen_setter_by_val(infile);
	gen_setter_by_val(we);
	gen_setter_by_val(pass);
	gen_setter_by_val(sym_tbl);
	gen_setter_by_val(lineno);
	gen_setter_by_val(nextc);
	gen_setter_by_val(nextt);
	gen_setter_by_val(nextval);
	gen_setter_by_val(nextsym);
	
	
	
public:		// functions
	inline lexer( std::FILE* s_infile, warn_error* s_we, size_t* s_pass,
		symbol_table* s_sym_tbl )
	{
		init( s_infile, s_we, s_pass, s_sym_tbl );
	}
	virtual inline ~lexer()
	{
	}
	
	void init( std::FILE* s_infile, warn_error* s_we, size_t* s_pass,
		symbol_table* s_sym_tbl );
	
	bool match( tok typ );
	bool match_no_ws( tok typ );
	void assume( tok typ );
	
	inline tok operator () ()
	{
		eat_ws();
		return lex_no_ws();
	}
	
	gen_getter_by_val(infile);
	gen_getter_by_val(we);
	inline size_t pass() const
	{
		return *internal_pass;
	}
	gen_getter_by_val(sym_tbl);
	gen_getter_by_val(lineno);
	gen_getter_by_val(nextc);
	gen_getter_by_val(nextt);
	gen_getter_by_val(nextval);
	gen_getter_by_val(nextsym);
	
};


}

#include "warn_error_stuff.hpp"


#endif		// lexer_class_hpp
