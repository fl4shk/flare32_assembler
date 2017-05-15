#include "lexer_class.hpp"


namespace navichip32
{

void lexer::init( std::FILE* s_infile, warn_error* s_we, size_t* s_pass,
	symbol_table* s_user_sym_tbl, symbol_table* s_special_sym_tbl )
{
	set_infile(s_infile);
	set_we(s_we);
	set_pass(s_pass);
	set_user_sym_tbl(s_user_sym_tbl);
	set_special_sym_tbl(s_special_sym_tbl);
	set_lineno(1);
	set_nextc(' ');
	set_nextt(' ');
	set_nextval(0);
	set_nextsym(nullptr);
	set_special_nextt(' ');
	set_special_nextval(0);
	set_special_nextsym(nullptr);
}

tok lexer::advance( bool keep_lineno )
{
	if ( nextc() != EOF )
	{
		if (!keep_lineno)
		{
			set_lineno( lineno() + ( nextc() == '\n' ) );
		}
		set_nextc(getc(infile()));
	}
	
	return nextc();
}

void lexer::eat_ws( bool keep_lineno )
{
	// Ignore leading whitespace
	while ( isspace(nextc()) && ( nextc() != '\n' ) )
	{
		advance(keep_lineno);
	}
}

void lexer::lex_no_ws( bool keep_lineno )
{
	// Comment in assembler becomes end of line
	if ( nextc() == ';' )
	{
		do
		{
			advance(keep_lineno);
		} while ( ( nextc() != '\n' ) && ( nextc() != EOF ) );
		advance(keep_lineno);
		
		//return set_nextt('\n');
		set_nextt('\n');
		return;
	}
	
	// An ident?
	if ( isalpha(nextc()) || ( nextc() == '_' ) )
	{
		std::string ident_str;
		
		auto update = [&]() -> void
		{
			ident_str += nextc();
			advance(keep_lineno);
		};
		auto update_nextval_and_nextt = [&]() -> void
		{
			set_nextval(nextsym()->val());
			set_nextt(nextsym()->typ());
		};
		auto update_special_nextval_and_special_nextt = [&]() -> void
		{
			set_special_nextval(special_nextsym()->val());
			set_special_nextt(special_nextsym()->typ());
		};
		
		update();
		
		while ( isalnum(nextc()) || ( nextc() == '_' ) )
		{
			update();
		}
		
		symbol* ident_sym;
		
		// Handle instructions with a ".f" suffix.
		if ( nextc() == '.' )
		{
			update();
			
			while ( isalnum(nextc()) || ( nextc() == '_' ) )
			{
				update();
			}
			
			const bool did_find = special_sym_tbl()->find( ident_sym, 
				ident_str );
			
			// Only permit pre-inserted identifiers that have ".whatever".
			// This can be used for internal identifiers (besides
			// instructions)
			if (!did_find)
			{
				we()->invalid("identifier");
			}
			else
			{
				set_special_nextsym(ident_sym);
				update_special_nextval_and_special_nextt();
				set_nextsym(nullptr);
				set_nextval(special_nextval());
				set_nextt(special_nextt());
			}
		}
		else
		{
			//std::string aaaa = ident_str;
			
			const bool did_find = special_sym_tbl()->find( ident_sym,
				ident_str );
			
			
			if (did_find)
			{
				set_special_nextsym(ident_sym);
				update_special_nextval_and_special_nextt();
			}
			else
			{
				set_special_nextsym(nullptr);
			}
			
			set_nextsym(&(user_sym_tbl()->enter( ident_str, 
				static_cast<tok>(tok_defn::ident), 0, false )));
			update_nextval_and_nextt();
		}
		
		//return nextt();
		return;
	}
	
	// A number? (allows leading zeros)
	if ( isdigit(nextc()) )
	{
		set_nextval( nextc() - '0' );
		advance(keep_lineno);
		
		while ( isdigit(nextc()) )
		{
			set_nextval( ( nextval() * 10 ) + nextc() - '0' );
			advance(keep_lineno);
		}
		
		//return set_nextt(static_cast<tok>(tok_defn::number));
		set_nextt(static_cast<tok>(tok_defn::number));
		return;
	}
	
	
	// Must be punctuation?
	set_nextt(nextc());
	advance(keep_lineno);
	//return nextt();
}




bool lexer::match( tok typ, bool keep_lineno )
{
	if ( nextt() == typ )
	{
		this->operator () (keep_lineno);
		return true;
	}
	return false;
}
bool lexer::match_no_ws( tok typ, bool keep_lineno )
{
	if ( nextt() == typ )
	{
		lex_no_ws(keep_lineno);
		return true;
	}
	return false;
}

void lexer::assume( tok typ, bool keep_lineno )
{
	if (!match( typ, keep_lineno ))
	{
		we()->warn1( "Missing ", static_cast<char>(typ), " assumed" );
	}
}



}
