#ifndef lexer_class_hpp
#define lexer_class_hpp

#include "token_stuff.hpp"
#include "symbol_table_class.hpp"

namespace assembler
{


class lexer
{
private:		// variables
	std::FILE* internal_infile = nullptr;
	int internal_lineno = 1;
	tok internal_nextc = ' ';
	tok internal_nextt = ' ';
	
	
	
private:		// functions
	tok advance();
	
	void eat_ws();
	tok comment();
	tok ident();
	tok digit();
	
	tok lex_no_ws();
	
	gen_setter_by_val(lineno);
	gen_setter_by_val(nextc);
	gen_setter_by_val(nextt);
	
public:		// functions
	lexer( std::FILE* s_infile );
	virtual ~lexer();
	
	bool match( tok typ );
	bool match_no_ws( tok typ );
	void assume( tok typ );
	
	inline tok operator () ()
	{
		eat_ws();
		return lex_no_ws();
	}
	
	gen_getter_by_val(infile);
	
	
	gen_getter_by_val(lineno);
	gen_getter_by_val(nextc);
	gen_getter_by_val(nextt);
	
};


}


#endif		// lexer_class_hpp
