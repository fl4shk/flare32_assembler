#include "assembler_class.hpp"

namespace flare32
{

Assembler::Assembler(char* s_input_filename) 
{
	set_input_filename(s_input_filename);
	set_infile(fopen(input_filename(), "r"));

	if (infile() == nullptr)
	{
		err("Cannot read file");
	}

	fill_builtin_sym_tbl();
}

int Assembler::operator () ()
{
	do
	{
		reinit();

		advance();
		lex();

		while (next_tok() != &Tok::Eof)
		{
			line();
		}

	} while (changed());

	return 0;
}



void Assembler::reinit()
{
	rewind(infile());
	set_line_num(1);
	set_next_char(' ');
	set_next_tok(nullptr);
	set_next_user_tok(nullptr);
	set_next_sym_str("");
	set_next_num(-1);
	set_changed(false);
}

void Assembler::fill_builtin_sym_tbl()
{
}


void Assembler::need(PTok tok)
{
	if (next_tok() == tok)
	{
		lex();
	}
	else
	{
		printerr("need():  ");
		expected_tokens(tok);
	}
}

void Assembler::advance()
{
	if (next_char() == EOF)
	{
		set_next_tok(&Tok::Eof);
		return;
	}

	//set_next_char(getchar());
	set_next_char(getc(infile()));

	if (next_char() == '\n')
	{
		++__line_num;
	}
}



void Assembler::lex()
{
	while (isspace(next_char()) && (next_char() != '\n'))
	{
		advance();
	}

	if (next_char() == EOF)
	{
		set_next_tok(&Tok::Eof);
		return;
	}

	std::string next_str;
	next_str += next_char();

	if (next_str == "")
	{
	}

	#define VARNAME(some_tok) \
		else if (next_str == Tok::some_tok.str()) \
		{ \
			set_next_tok(&Tok::some_tok); \
			advance(); \
			return; \
		}
	#define VALUE(some_str)

	LIST_OF_PUNCT_TOKENS(VARNAME, VALUE)
	LIST_OF_SINGLE_CHAR_OPERATOR_TOKENS(VARNAME, VALUE)

	#undef VARNAME

	// Find an identifier
	if (isalpha(next_char()) || (next_char() == '_'))
	{
		//printout("lex():  An ident?\n");
		next_str = "";
		next_str += next_char();
		advance();

		while (isalnum(next_char()) || (next_char() == '_'))
		{
			next_str += next_char();
			advance();
		}

		//printout("lex():  next_str, next_char():  ", next_str, ", ",
		//	(char)next_char(), "\n");

		// If we haven't seen a user symbol like this before...
		if (!user_sym_tbl().contains(next_str))
		{
			// ...Then create a new symbol
			//printout("Creating a new symbol....\n");
			Symbol to_insert(next_str, &Tok::Ident, 0);

			user_sym_tbl().at(next_str) = to_insert;
		}
		set_next_user_tok(user_sym_tbl().at(next_str).token());

		if (builtin_sym_tbl().contains(next_str))
		{
			const Symbol& temp = builtin_sym_tbl().at(next_str);
			set_next_tok(temp.token());
		}
		else
		{
			set_next_tok(&Tok::Ident);
		}

		set_next_sym_str(next_str);

		return;
	}

	// The constant 0
	if (next_char() == '0')
	{
		set_next_num(0);
		set_next_tok(&Tok::NatNum);

		advance();

		if (isdigit(next_char()))
		{
			expected("Natural number that does not start with 0!");
		}
	}

	// Find a constant natural number
	if (isdigit(next_char()))
	{
		set_next_num(0);

		do
		{
			set_next_num((next_num() * 10) + (next_char() - '0'));
			advance();
		} while (isdigit(next_char()));

		set_next_tok(&Tok::NatNum);

		return;

	}

	// BitShL
	if (next_char() == '<')
	{
		advance();

		if (next_char() == '<')
		{
			advance();
			set_next_tok(&Tok::BitShL);
		}
		else
		{
			expected("\"<<\" but got \"", next_str, "\"!");
		}

		return;
	}

	// BitShR
	if (next_char() == '>')
	{
		advance();

		if (next_char() == '>')
		{
			advance();
			set_next_tok(&Tok::BitShR);
		}
		else
		{
			expected("\">>\" but got \"", next_str, "\"!");
		}

		return;
	}


}

void Assembler::line()
{
	printout("line():  ", next_tok()->str(), "\n");
}



s64 Assembler::handle_expr()
{
	const auto old_next_tok = next_tok();

	s64 ret;

	if ((old_next_tok == &Tok::Plus) || (old_next_tok == &Tok::Minus))
	{
		lex();

		if (old_next_tok == &Tok::Plus)
		{
			ret = handle_term();
		}
		else // if (old_next_tok == &Tok::Minus)
		{
			ret = -handle_term();
		}
	}
	else
	{
		ret = handle_term();
	}

	if ((next_tok() == &Tok::Plus) || (next_tok() == &Tok::Minus))
	{
		ret += handle_expr();
	}

	return ret;

}

s64 Assembler::handle_term()
{
	s64 ret = handle_factor();

	while ((next_tok() == &Tok::Mult) || (next_tok() == &Tok::Div)
		|| (next_tok() == &Tok::BitAnd) || (next_tok() == &Tok::BitOr)
		|| (next_tok() == &Tok::BitXor) || (next_tok() == &Tok::BitShL) 
		|| (next_tok() == &Tok::BitShR))
	{
		const auto old_next_tok = next_tok();
		lex();

		if (old_next_tok == &Tok::Mult)
		{
			ret *= handle_factor();
		}
		else if (old_next_tok == &Tok::Div)
		{
			ret /= handle_factor();
		}
		else if (old_next_tok == &Tok::BitAnd)
		{
			ret &= handle_factor();
		}
		else if (old_next_tok == &Tok::BitOr)
		{
			ret |= handle_factor();
		}
		else if (old_next_tok == &Tok::BitXor)
		{
			ret ^= handle_factor();
		}
		else if (old_next_tok == &Tok::BitShL)
		{
			ret <<= handle_factor();
		}
		else if (old_next_tok == &Tok::BitShR)
		{
			ret >>= handle_factor();
		}
	}


	return ret;
}

s64 Assembler::handle_factor()
{
	if (next_tok() == &Tok::NatNum)
	{
		s64 ret = next_num();
		lex();
		return ret;
	}
	//else if (next_tok() == &Tok::Ident)
	else if (next_tok_is_ident_ish())
	{
		const Symbol& sym = user_sym_tbl().at(next_sym_str());
		s64 ret = sym.value();
		lex();
		return ret;
	}

	s64 ret;

	if (next_tok() != &Tok::LParen)
	{
		//expected("token of type \"", Tok::NatNum.str(), "\" or \"", 
		//	Tok::Ident.str(), "\" or \"", Tok::LParen.str(), "\"!");
		expected_tokens(&Tok::NatNum, &Tok::Ident, &Tok::LParen);
	}

	need(&Tok::LParen);

	ret = handle_expr();

	need(&Tok::RParen);

	return ret;
}






bool Assembler::next_tok_is_punct() const
{
	if (next_tok() == nullptr)
	{
	}
	
	#define VARNAME(some_tok) \
		else if (next_tok() == &Tok::some_tok) \
		{ \
			return true; \
		}
	#define VALUE(some_str) 
	
	LIST_OF_PUNCT_TOKENS(VARNAME, VALUE)

	#undef VARNAME
	#undef VALUE


	return false;
}

bool Assembler::next_tok_is_ident_ish() const
{
	if (next_tok() == nullptr)
	{
	}

	#define VARNAME(some_tok) \
		else if (next_tok() == &Tok::some_tok) \
		{ \
			return true; \
		}
	#define VALUE(some_str) 
	
	LIST_OF_IDENT_ISH_TOKENS(VARNAME, VALUE)

	#undef VARNAME
	#undef VALUE

	return false;
}

}
