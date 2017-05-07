#include "lexer_class.hpp"


namespace assembler
{

void lexer::init( std::FILE* s_infile, warn_error* s_we, size_t* s_pass )
{
	set_infile(s_infile);
	set_we(s_we);
	set_pass(s_pass);
	set_lineno(1);
	set_nextc(' ');
	set_nextt(' ');
	set_nextval(0);
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
	// Ignore leading whitespace
	while ( isspace(nextc()) && ( nextc() != '\n' ) )
	{
		advance();
	}
}

tok lexer::lex_no_ws()
{
	// Comment in assembler becomes end of line
	if ( nextc() == ';' )
	{
		do
		{
			advance();
		} while ( ( nextc() != '\n' ) && ( nextc() != EOF ) );
		advance();
		
		return set_nextt('\n');
	}
	
	// An ident?
	if ( isalpha(nextc()) || ( nextc() == '_' ) )
	{
		
	}
	
	// A number? (allows leading zeros)
	if ( isdigit(nextc()) )
	{
		set_nextval( nextc() - '0' );
		advance();
		
		while ( isdigit(nextc()) )
		{
			set_nextval( ( nextval() * 10 ) + nextc() - '0' );
			advance();
		}
		
		return set_nextt(static_cast<tok>(tok_defn::number));
	}
	
	// Must be punctuation?
	set_nextt(nextc());
	advance();
	return nextt();
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
		we()->warn1( "Missing ", static_cast<char>(typ), " assumed" );
	}
}



}
