#include "lexer_class.hpp"


namespace assembler
{

lexer::lexer( std::FILE* s_infile ) : internal_infile(s_infile)
{
}

lexer::~lexer()
{
}


tok lexer::advance()
{
	if ( nextc() != EOF )
	{
		set_lineno( lineno() + ( nextc() == '\n' ) );
		set_nextc(getc(infile()));
	}
	
	return nextc();
}

void lexer::eat_ws()
{
	
	
}
tok lexer::comment()
{
	
}

tok lexer::ident()
{
	
}

tok lexer::digit()
{
	
}

tok lexer::lex_no_ws()
{
	
}




bool lexer::match( tok typ )
{
	if ( nextt() == typ )
	{
		this->operator () ();
		return true;
	}
	return false;
}
bool lexer::match_no_ws( tok typ )
{
	if ( nextt() == typ )
	{
		lex_no_ws();
		return true;
	}
	return false;
}

void lexer::assume( tok typ )
{
	if (!match(typ))
	{
		warn1( "Missing ", static_cast<char>(tok), " assumed" );
	}
}



}
