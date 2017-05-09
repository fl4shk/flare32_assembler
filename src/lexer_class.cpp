#include "lexer_class.hpp"


namespace navichip32
{

void lexer::init( std::FILE* s_infile, warn_error* s_we, size_t* s_pass,
	symbol_table* s_sym_tbl )
{
	set_infile(s_infile);
	set_we(s_we);
	set_pass(s_pass);
	set_sym_tbl(s_sym_tbl);
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
	// Comment in navichip32 becomes end of line
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
		std::string ident_str;
		
		auto update = [&]() -> void
		{
			ident_str += nextc();
			advance();
		};
		auto update_nextval_and_nextt = [&]() -> void
		{
			set_nextval(nextsym()->val());
			set_nextt(nextsym()->typ());
		};
		auto do_enter = [&]( tok typ ) -> void
		{
			set_nextsym(&(sym_tbl()->enter( std::move(ident_str), typ, 
				0 )));
			update_nextval_and_nextt(); };
		
		update();
		
		while ( isalnum(nextc()) || ( nextc() == '_' ) )
		{
			update();
		}
		
		
		// Handle instructions with a ".f" suffix.
		if ( nextc() == '.' )
		{
			update();
			
			//if ( nextc() == 'f' )
			//{
			//	update();
			//	
			//	if (!isspace(nextc()))
			//	{
			//		invalid_ident();
			//	}
			//	else
			//	{
			//		//do_enter(static_cast<tok>(tok_defn::bad_ident));
			//	}
			//}
			//else
			//{
			//	invalid_ident();
			//}
			
			while ( isalnum(nextc()) || ( nextc() == '_' ) )
			{
				update();
			}
			
			symbol* ident_sym;
			const bool did_find = sym_tbl()->find( ident_sym, ident_str );
			
			if (!did_find)
			{
				invalid_ident();
			}
			else
			{
				set_nextsym(ident_sym);
				update_nextval_and_nextt();
			}
		}
		else
		{
			do_enter(static_cast<tok>(tok_defn::ident));
		}
		
		return nextt();
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
