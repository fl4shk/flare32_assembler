#include "lexer_class.hpp"

namespace flare32
{


void Lexer::need(const std::vector<ParseNode>& some_parse_vec, 
	size_t& index, PTok tok)
{
	//if (next_tok() == tok)
	if (some_parse_vec.at(index).next_tok == tok)
	{
		//lex();
		++index;
	}
	else
	{
		printerr("need():  ");
		we().expected_tokens(tok);
	}
}

void Lexer::__advance_innards(int& some_next_char, 
	PTok& some_next_tok, std::string& some_next_sym_str,
	s64& some_next_num, size_t& some_line_num,  
	size_t& some_outer_index, size_t& some_inner_index,
	std::vector<std::string>* some_str_vec)
{
	auto next_char = [&]() -> int
	{
		return some_next_char;
	};

	auto set_next_char = [&](int n_next_char) -> void
	{
		some_next_char = n_next_char;
	};


	auto set_next_tok = [&](PTok tok) -> void
	{
		some_next_tok = tok;
	};

	auto fake_getc = [&]() -> int
	{
		if (some_outer_index >= some_str_vec->size())
		{
			return EOF;
		}

		if (some_inner_index >= some_str_vec->at(some_outer_index).size())
		{
			some_inner_index = 0;
			++some_outer_index;

			//if (some_outer_index < some_str_vec->size())
			//{
			//	printout("returning \\n\n");
			//	return '\n';
			//}
			//else
			if (some_outer_index >= some_str_vec->size())
			{
				//printout("returning EOF\n");
				return EOF;
			}
		}

		const auto ret = some_str_vec->at(some_outer_index)
			.at(some_inner_index++);
		//printout("returning '", ret, "'\n");

		return ret;
	};


	if (some_str_vec == nullptr)
	{
		if (next_char() == EOF)
		{
			set_next_tok(&Tok::Eof);
			return;
		}

		//set_next_char(getchar());
		set_next_char(getc(infile()));
	}
	else // if (some_str_vec != nullptr)
	{
		if (next_char() == EOF)
		{
			set_next_tok(&Tok::Eof);
			return;
		}

		set_next_char(fake_getc());
	}

	if (next_char() == '\n')
	{
		++some_line_num;
	}
}



void Lexer::__lex_innards(int& some_next_char, 
	PTok& some_next_tok, PTok& some_prev_tok, 
	std::string& some_next_sym_str,
	s64& some_next_num, size_t& some_line_num,
	size_t& some_outer_index, size_t& some_inner_index,
	std::vector<std::string>* some_str_vec,
	ParsePos* pos)
{
	auto next_char = [&]() -> int
	{
		return some_next_char;
	};


	auto next_tok = [&]() -> PTok
	{
		return some_next_tok;
	};

	auto set_next_tok = [&](PTok tok) -> void
	{
		some_prev_tok = some_next_tok;
		some_next_tok = tok;
	};

	auto prev_tok = [&]() -> PTok
	{
		return some_prev_tok;
	};

	//auto next_sym_str = [&]() -> const std::string&
	//{
	//	return some_next_sym_str;
	//};

	auto set_next_sym_str = [&](const std::string& n_next_sym_str) -> void
	{
		some_next_sym_str = n_next_sym_str;
	};

	auto next_num = [&]() -> s64
	{
		return some_next_num;
	};
	auto set_next_num = [&](s64 n_next_num) -> void
	{
		some_next_num = n_next_num;
	};

	auto call_advance = [&]() -> void
	{
		__advance_innards(some_next_char, some_next_tok,
			some_next_sym_str, some_next_num, some_line_num,  
			some_outer_index, some_inner_index, some_str_vec);
		//switch (next_char())
		//{
		//	case '\n':
		//		printout("lex:  \\n\n");
		//		break;

		//	case EOF:
		//		printout("lex:  EOF\n");
		//		break;

		//	default:
		//		printout("lex:  '", (char)next_char(), "'\n");
		//		break;
		//}
	};


	while (isspace(next_char()) && (next_char() != '\n'))
	//while (isspace(next_char()) && (next_char() != '\n')
	//	&& (next_char() != EOF))
	{
		call_advance();
	}


	if (pos != nullptr)
	{
		pos->outer_index = some_outer_index;
		pos->inner_index = some_inner_index - 1;
	}

	if (next_char() == '\n')
	{
		printout("lex:  Setting next_tok to newline\n");
		set_next_tok(&Tok::Newline);
		call_advance();
		return;
	}

	if (next_char() == EOF)
	{
		printout("lex:  Setting next_tok to EOF\n");
		set_next_tok(&Tok::Eof);
		return;
	}

	std::string next_str;
	next_str += next_char();


	// Find assembler directives
	if (next_char() == '.')
	{
		call_advance();
		while (isalnum(next_char()) || next_char() == '_')
		{
			next_str += next_char();
			call_advance();
		}

		if (next_str == "")
		{
		}

		#define TOKEN_STUFF(varname, value) \
			else if (next_str == Tok::varname.str()) \
			{ \
				set_next_tok(&Tok::varname); \
				return; \
			}

		LIST_OF_DIRECTIVE_TOKENS(TOKEN_STUFF)
		#undef TOKEN_STUFF

		else
		{
			we().err("Invalid assembler directive");
		}
	}



	if (next_str == "")
	{
	}

	#define TOKEN_STUFF(varname, value) \
		else if (next_str == Tok::varname.str()) \
		{ \
			set_next_tok(&Tok::varname); \
			call_advance(); \
			return; \
		}

	LIST_OF_PUNCT_TOKENS(TOKEN_STUFF)
	LIST_OF_SINGLE_CHAR_OPERATOR_TOKENS(TOKEN_STUFF)

	#undef TOKEN_STUFF


	//// Find a .define name
	//if (next_char() == '`')
	//{
	//	next_str = "";
	//	next_str += next_char();
	//	call_advance();

	//	if (isalpha(next_char())
	//}

	// Find an identifier
	if (isalpha(next_char()) || (next_char() == '_')
		|| (next_char() == '`'))
	{
		//printout("lex():  An ident?\n");
		next_str = "";
		next_str += next_char();
		call_advance();

		while (isalnum(next_char()) || (next_char() == '_'))
		{
			next_str += next_char();
			call_advance();
		}

		if (next_char() == '.')
		{
			next_str += next_char();
			call_advance();

			while (isalnum(next_char()) || (next_char() == '_'))
			{
				next_str += next_char();
				call_advance();
			}
		}

		// Defines must start with "`"
		if (next_str.front() == '`')
		{
			if (!user_sym_tbl().contains(next_str))
			{
				// Need to use next_tok() here because we haven't
				// set_next_tok() yet.
				if (((prev_tok() == &Tok::Newline)
					|| (prev_tok() == nullptr))
					&& (next_tok() != &Tok::DotDef))
				{
					we().err("Undefined .def (perhaps just not YET ",
						"defined?)");
				}

				Symbol to_insert(next_str, &Tok::Ident, 0,
					SymType::DefineName);

				user_sym_tbl().insert_or_assign(to_insert);
			}
		}
		// If we haven't seen a user symbol like this before...
		else if (!user_sym_tbl().contains(next_str))
		{
			// ...Then create a new symbol
			//printout("Creating a new symbol....\n");
			Symbol to_insert(next_str, &Tok::Ident, 0);


			// Need to use next_tok() here because we haven't
			// set_next_tok() yet.
			#define TOKEN_STUFF(varname, value) \
				(next_tok() == &Tok::varname) ||
			if (LIST_OF_EQUATE_DIRECTIVE_TOKENS(TOKEN_STUFF) false)
			{
				to_insert.set_type(SymType::EquateName);
			}
			#undef TOKEN_STUFF
			//else if (next_tok() == &Tok::DotDef)
			//{
			//	to_insert.set_type(SymType::DefineName);
			//}
			else
			{
				to_insert.set_type(SymType::Other);
			}
			
			//printout((int)to_insert.type(), "\n");

			user_sym_tbl().insert_or_assign(to_insert);
		}


		//printout("lex():  next_str, next_char():  ", next_str, ", ",
		//	(char)next_char(), "\n");
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

	// The constant 0... or a hexadecimal or binary number!
	if (next_char() == '0')
	{
		set_next_num(0);
		set_next_tok(&Tok::NatNum);

		call_advance();

		if (isdigit(next_char()))
		{
			we().expected("Natural number that does not start with 0!");
		}

		// Hexadecimal number
		if (next_char() == 'x')
		{
			call_advance();

			if (!isxdigit(next_char()))
			{
				we().expected("Hexadecimal number");
			}

			while (isxdigit(next_char()))
			{
				if ((next_char() >= 'a') && (next_char() <= 'f'))
				{
					set_next_num((next_num() * 16) 
						+ (next_char() - 'a' + 0xa));
				}
				else if ((next_char() >= 'A') && (next_char() <= 'F'))
				{
					set_next_num((next_num() * 16) 
						+ (next_char() - 'A' + 0xa));
				}
				else // if ((next_char() >= '0') && (next_char() <= '9'))
				{
					set_next_num((next_num() * 16) + (next_char() - '0'));
				}

				call_advance();
			}
		}

		// Binary number
		if (next_char() == 'b')
		{
			call_advance();

			if ((next_char() != '0') && (next_char() != '1'))
			{
				we().expected("Binary number");
			}

			while ((next_char() == '0') || (next_char() == '1'))
			{
				set_next_num((next_num() * 2) + (next_char() - '0'));

				call_advance();
			}
		}

		return;
	}

	// Find a constant natural number
	if (isdigit(next_char()))
	{
		set_next_num(0);

		do
		{
			set_next_num((next_num() * 10) + (next_char() - '0'));
			call_advance();
		} while (isdigit(next_char()));

		set_next_tok(&Tok::NatNum);

		return;
	}

	// BitShL
	if (next_char() == '<')
	{
		call_advance();

		if (next_char() == '<')
		{
			call_advance();
			set_next_tok(&Tok::BitShL);
		}
		else
		{
			we().expected("\"<<\" but got \"", next_str, "\"!");
		}

		return;
	}

	// BitShR
	if (next_char() == '>')
	{
		call_advance();

		if (next_char() == '>')
		{
			call_advance();
			set_next_tok(&Tok::BitShR);
		}
		else
		{
			we().expected("\">>\" but got \"", next_str, "\"!");
		}

		return;
	}

	set_next_tok(&Tok::Bad);
}

}
