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
	// Two passes
	for (set_pass(0); pass() < 2; set_pass(pass() + 1))
	{
		reinit();

		advance();
		lex();

		while (next_tok() != &Tok::Eof)
		{
			line();
		}

		printout("\n\n");
	}

	return 0;
}



void Assembler::reinit()
{
	rewind(infile());
	set_addr(0);
	set_line_num(0);
	set_next_char(' ');
	set_next_tok(nullptr);
	set_next_sym_str("");
	set_next_num(-1);
}

void Assembler::fill_builtin_sym_tbl()
{
	// General-purpose registers
	builtin_sym_tbl().insert_or_assign(Symbol("r0", &Tok::Reg, 0));
	builtin_sym_tbl().insert_or_assign(Symbol("r1", &Tok::Reg, 1));
	builtin_sym_tbl().insert_or_assign(Symbol("r2", &Tok::Reg, 2));
	builtin_sym_tbl().insert_or_assign(Symbol("r3", &Tok::Reg, 3));
	builtin_sym_tbl().insert_or_assign(Symbol("r4", &Tok::Reg, 4));
	builtin_sym_tbl().insert_or_assign(Symbol("r5", &Tok::Reg, 5));
	builtin_sym_tbl().insert_or_assign(Symbol("r6", &Tok::Reg, 6));
	builtin_sym_tbl().insert_or_assign(Symbol("r7", &Tok::Reg, 7));
	builtin_sym_tbl().insert_or_assign(Symbol("r8", &Tok::Reg, 8));
	builtin_sym_tbl().insert_or_assign(Symbol("r9", &Tok::Reg, 9));
	builtin_sym_tbl().insert_or_assign(Symbol("r10", &Tok::Reg, 10));
	builtin_sym_tbl().insert_or_assign(Symbol("r11", &Tok::Reg, 11));
	builtin_sym_tbl().insert_or_assign(Symbol("r12", &Tok::Reg, 12));
	builtin_sym_tbl().insert_or_assign(Symbol("r13", &Tok::Reg, 13));
	builtin_sym_tbl().insert_or_assign(Symbol("r14", &Tok::Reg, 14));
	builtin_sym_tbl().insert_or_assign(Symbol("r15", &Tok::Reg, 15));
	builtin_sym_tbl().insert_or_assign(Symbol("lr", &Tok::Reg, 14));
	builtin_sym_tbl().insert_or_assign(Symbol("sp", &Tok::Reg, 15));

	// Special-purpose registers
	builtin_sym_tbl().insert_or_assign(Symbol("pc", &Tok::RegPc, -1));
	builtin_sym_tbl().insert_or_assign(Symbol("ira", &Tok::RegIra, -1));
	builtin_sym_tbl().insert_or_assign(Symbol("flags", &Tok::RegFlags,
		-1));


	// Instructions
	for (const auto& outer_iter : __instr_tbl.instr_vec)
	{
		for (const auto& instr : *outer_iter)
		{
			builtin_sym_tbl().insert_or_assign(Symbol(instr->str(), 
				&Tok::Instr, -1));
		}
	}
}


void Assembler::need(const std::vector<ParseNode>& some_parse_vec, 
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
	//while (isspace(next_char()) && (next_char() != '\n'))
	while (isspace(next_char()) && (next_char() != '\n'))
	{
		advance();
	}

	if (next_char() == '\n')
	{
		set_next_tok(&Tok::Newline);
		advance();
		return;
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
	#undef VALUE

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
	std::vector<ParseNode> parse_vec, second_parse_vec;

	while ((next_tok() != &Tok::Newline) && (next_tok() != &Tok::Eof))
	{
		parse_vec.push_back(ParseNode(next_tok(), next_sym_str(),
			next_num()));
		lex();
	}

	//for (const auto& node : parse_vec)
	//{
	//	printout(node.next_tok->str(), "\t\t");
	//}
	//printout("\n");


	bool found_label = false;

	// Check for a label
	if (parse_vec.size() >= 2)
	{
		if (tok_is_ident_ish(parse_vec.at(0).next_tok) 
			&& parse_vec.at(1).next_tok == &Tok::Colon)
		{
			found_label = true;

			// Update the value of the label in the user symbol table.
			// This happens regardless of what pass we're on.
			user_sym_tbl().at(parse_vec.at(0).next_sym_str).set_value
				(addr());
		}
	}

	if (!found_label)
	{
		for (size_t i=0; i<parse_vec.size(); ++i)
		{
			// Ignore comments
			if (parse_vec.at(i).next_tok == &Tok::Semicolon)
			{
				break;
			}
			second_parse_vec.push_back(parse_vec.at(i));
		}
	}
	else
	{
		for (size_t i=2; i<parse_vec.size(); ++i)
		{
			// Ignore comments
			if (parse_vec.at(i).next_tok == &Tok::Semicolon)
			{
				break;
			}
			second_parse_vec.push_back(parse_vec.at(i));
		}
	}

	finish_line(second_parse_vec);
	lex();
}


void Assembler::finish_line
	(const std::vector<Assembler::ParseNode>& some_parse_vec)
{
	//for (const auto& node : some_parse_vec)
	//{
	//	printout(node.next_tok->str(), "\t\t");
	//}
	//printout("\n");

	if (some_parse_vec.size() == 0)
	{
		return;
	}

	
	//{
	//size_t index = 0;
	//const auto temp = handle_expr(some_parse_vec, index);

	//printout(temp, "\n");

	//set_addr(addr() + 4);
	//}

	if (some_parse_vec.at(0).next_tok != &Tok::Instr)
	{
		expected_tokens(&Tok::Instr);
	}

	const auto& instr_vec = __instr_tbl.at(some_parse_vec.at(0)
		.next_sym_str);



	bool complete = false;

	for (const auto& instr : instr_vec)
	{
		if (parse_instr(instr, some_parse_vec))
		{
			complete = true;
			break;
		}
	}

	if (!complete)
	{
		err("Invalid instruction arguments");
	}

}


bool Assembler::parse_instr(PInstr instr,
	const std::vector<Assembler::ParseNode>& some_parse_vec)
{
	switch (instr->args())
	{
		case InstrArgs::no_args:
			return __parse_instr_no_args(some_parse_vec, 
				instr);
		case InstrArgs::uimm16:
			return __parse_instr_uimm16(some_parse_vec, 
				instr);
		case InstrArgs::simm16:
			return __parse_instr_simm16(some_parse_vec, 
				instr);
		case InstrArgs::imm32:
			return __parse_instr_imm32(some_parse_vec, 
				instr);

		case InstrArgs::ra:
			return __parse_instr_ra(some_parse_vec, 
				instr);
		case InstrArgs::ra_uimm16:
			return __parse_instr_ra_uimm16(some_parse_vec, 
				instr);
		case InstrArgs::ra_rb:
			return __parse_instr_ra_rb(some_parse_vec, 
				instr);
		case InstrArgs::ra_rb_uimm16:
			return __parse_instr_ra_rb_uimm16(some_parse_vec, 
				instr);
		case InstrArgs::ra_rb_simm16:
			return __parse_instr_ra_rb_simm16(some_parse_vec, 
				instr);
		case InstrArgs::ra_rb_rc:
			return __parse_instr_ra_rb_rc(some_parse_vec, 
				instr);
		case InstrArgs::ra_rb_rc_simm12:
			return __parse_instr_ra_rb_rc_simm12(some_parse_vec, 
				instr);

		case InstrArgs::ldst_ra_rb:
			return __parse_instr_ldst_ra_rb(some_parse_vec, 
				instr);
		case InstrArgs::ldst_ra_rb_rc_simm12:
			return __parse_instr_ldst_ra_rb_rc_simm12(some_parse_vec, 
				instr);
		case InstrArgs::ldst_ra_rb_rc:
			return __parse_instr_ldst_ra_rb_rc(some_parse_vec, 
				instr);
		case InstrArgs::ldst_ra_rb_simm12:
			return __parse_instr_ldst_ra_rb_simm12(some_parse_vec, 
				instr);


		case InstrArgs::ldst_ra_rb_imm32:
			return __parse_instr_ldst_ra_rb_imm32(some_parse_vec, 
				instr);
		case InstrArgs::ra_rb_imm32:
			return __parse_instr_ra_rb_imm32(some_parse_vec, 
				instr);


		// Block moves (ldmia, stmia, stmdb) with number of {} args
		case InstrArgs::ldst_block_1_to_4:
			return __parse_instr_ldst_block_1_to_4(some_parse_vec, 
				instr);
		case InstrArgs::ldst_block_5_to_8:
			return __parse_instr_ldst_block_5_to_8(some_parse_vec, 
				instr);

		case InstrArgs::ira:
			return __parse_instr_ira(some_parse_vec, 
				instr);
		case InstrArgs::ra_ira:
			return __parse_instr_ra_ira(some_parse_vec, 
				instr);
		case InstrArgs::ira_ra:
			return __parse_instr_ira_ra(some_parse_vec, 
				instr);

		case InstrArgs::ra_flags:
			return __parse_instr_ra_flags(some_parse_vec, 
				instr);
		case InstrArgs::flags:
			return __parse_instr_flags(some_parse_vec, 
				instr);
		case InstrArgs::flags_ra:
			return __parse_instr_flags_ra(some_parse_vec, 
				instr);

		case InstrArgs::ra_pc:
			return __parse_instr_ra_pc(some_parse_vec, 
				instr);
	}

	return false;
}

bool Assembler::__parse_instr_no_args
	(const std::vector<Assembler::ParseNode>& some_parse_vec,
	PInstr instr)
{
	if (some_parse_vec.size() != 1)
	{
		return false;
	}

	if (some_parse_vec.at(0).next_tok != &Tok::Instr)
	{
		return false;
	}


	u16 high_hword = 0;
	u16 g1g2_low = 0;
	u32 g3_low = 0;

	encode_high_hword(high_hword, instr);
	gen16(high_hword);

	return true;
}
bool Assembler::__parse_instr_uimm16
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_simm16
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_imm32
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}

bool Assembler::__parse_instr_ra
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_ra_uimm16
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_ra_rb
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_ra_rb_uimm16
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_ra_rb_simm16
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_ra_rb_rc
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_ra_rb_rc_simm12
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}

bool Assembler::__parse_instr_ldst_ra_rb
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_ldst_ra_rb_rc_simm12
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_ldst_ra_rb_rc
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_ldst_ra_rb_simm12
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}


bool Assembler::__parse_instr_ldst_ra_rb_imm32
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_ra_rb_imm32
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}


// Block moves (ldmia, stmia, stmdb) with number of {} args
bool Assembler::__parse_instr_ldst_block_1_to_4
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_ldst_block_5_to_8
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}

bool Assembler::__parse_instr_ira
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_ra_ira
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_ira_ra
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}

bool Assembler::__parse_instr_ra_flags
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_flags
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}
bool Assembler::__parse_instr_flags_ra
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}

bool Assembler::__parse_instr_ra_pc
	(const std::vector<Assembler::ParseNode>& some_parse_vec, 
	PInstr instr)
{
	return true;
}



s64 Assembler::handle_expr(const std::vector<ParseNode>& some_parse_vec, 
	size_t& index)
{
	////const auto old_next_tok = next_tok();
	//const auto old_next_tok = some_parse_vec.at(index).next_tok;

	//s64 ret;

	//if ((old_next_tok == &Tok::Plus) || (old_next_tok == &Tok::Minus))
	//{
	//	//lex();
	//	++index;

	//	if (old_next_tok == &Tok::Plus)
	//	{
	//		ret = handle_term(some_parse_vec, index);
	//	}
	//	else // if (old_next_tok == &Tok::Minus)
	//	{
	//		ret = -handle_term(some_parse_vec, index);
	//	}
	//}
	//else
	//{
	//	ret = handle_term(some_parse_vec, index);
	//}

	//if (index >= some_parse_vec.size())
	//{
	//	return ret;
	//}

	////if ((next_tok() == &Tok::Plus) || (next_tok() == &Tok::Minus))
	//if ((some_parse_vec.at(index).next_tok == &Tok::Plus)
	//	|| (some_parse_vec.at(index).next_tok == &Tok::Minus))
	//{
	//	ret += handle_expr(some_parse_vec, index);
	//}

	//return ret;




	s64 ret = 0;

	if (some_parse_vec.at(index).next_tok == &Tok::Minus)
	{
		//lex();
		++index;
	}
	else if (some_parse_vec.at(index).next_tok == &Tok::Plus)
	{
		//lex();
		++index;
	}
	else if (tok_is_ident_ish(some_parse_vec.at(index).next_tok)
		|| (some_parse_vec.at(index).next_tok == &Tok::NatNum))
	{
	}
	else
	{
		printout("expr():  3, Eek!\n");
		return 9001;
	}


	ret = handle_term(some_parse_vec, index);

	if (index >= some_parse_vec.size())
	{
		return ret;
	}

	while ((some_parse_vec.at(index).next_tok == &Tok::Plus) 
		|| (some_parse_vec.at(index).next_tok == &Tok::Minus))
	{
		//const bool minus = (next_tok == Tok::Minus);
		const bool minus = (some_parse_vec.at(index).next_tok 
			== &Tok::Minus);

		//lex();
		++index;

		if (minus)
		{
			ret -= handle_term(some_parse_vec, index);
		}
		else
		{
			ret += handle_term(some_parse_vec, index);
		}

		if (index >= some_parse_vec.size())
		{
			return ret;
		}
	}

	return ret;

}

s64 Assembler::handle_term(const std::vector<ParseNode>& some_parse_vec, 
	size_t& index)
{
	s64 ret = handle_factor(some_parse_vec, index);

	if (index >= some_parse_vec.size())
	{
		return ret;
	}

	//const auto some_next_tok = some_parse_vec.at(index).next_tok;

	while ((some_parse_vec.at(index).next_tok == &Tok::Mult) 
		|| (some_parse_vec.at(index).next_tok == &Tok::Div)
		|| (some_parse_vec.at(index).next_tok == &Tok::BitAnd) 
		|| (some_parse_vec.at(index).next_tok == &Tok::BitOr)
		|| (some_parse_vec.at(index).next_tok == &Tok::BitXor) 
		|| (some_parse_vec.at(index).next_tok == &Tok::BitShL) 
		|| (some_parse_vec.at(index).next_tok == &Tok::BitShR))
	{
		const auto old_next_tok = some_parse_vec.at(index).next_tok;
		//lex();
		++index;

		if (old_next_tok == &Tok::Mult)
		{
			ret *= handle_factor(some_parse_vec, index);
		}
		else if (old_next_tok == &Tok::Div)
		{
			ret /= handle_factor(some_parse_vec, index);
		}
		else if (old_next_tok == &Tok::BitAnd)
		{
			ret &= handle_factor(some_parse_vec, index);
		}
		else if (old_next_tok == &Tok::BitOr)
		{
			ret |= handle_factor(some_parse_vec, index);
		}
		else if (old_next_tok == &Tok::BitXor)
		{
			ret ^= handle_factor(some_parse_vec, index);
		}
		else if (old_next_tok == &Tok::BitShL)
		{
			ret <<= handle_factor(some_parse_vec, index);
		}
		else if (old_next_tok == &Tok::BitShR)
		{
			ret >>= handle_factor(some_parse_vec, index);
		}


		if (index >= some_parse_vec.size())
		{
			return ret;
		}
	}


	return ret;


}

s64 Assembler::handle_factor(const std::vector<ParseNode>& some_parse_vec, 
	size_t& index)
{
	//if (next_tok() == &Tok::NatNum)
	if (some_parse_vec.at(index).next_tok == &Tok::NatNum)
	{
		//s64 ret = next_num();
		s64 ret = some_parse_vec.at(index).next_num;
		//lex();
		++index;
		return ret;
	}
	//else if (next_tok() == &Tok::Ident)
	//else if (next_tok_is_ident_ish())
	else if (tok_is_ident_ish(some_parse_vec.at(index).next_tok))
	{
		// This works because handle_factor() should only be called when
		// we're not asking for a user symbol
		const Symbol& sym = user_sym_tbl().at(some_parse_vec.at(index)
			.next_sym_str);
		s64 ret = sym.value();
		//lex();
		++index;
		return ret;
	}

	s64 ret;

	//if (next_tok() != &Tok::LParen)
	if (some_parse_vec.at(index).next_tok != &Tok::LParen)
	{
		//expected("token of type \"", Tok::NatNum.str(), "\" or \"", 
		//	Tok::Ident.str(), "\" or \"", Tok::LParen.str(), "\"!");
		expected_tokens(&Tok::NatNum, &Tok::Ident, &Tok::LParen);
	}

	need(some_parse_vec, index, &Tok::LParen);

	ret = handle_expr(some_parse_vec, index);

	need(some_parse_vec, index, &Tok::RParen);

	return ret;
}






bool Assembler::tok_is_punct(PTok some_tok) const
{
	if (some_tok == nullptr)
	{
	}
	
	#define VARNAME(other_tok) \
		else if (some_tok == &Tok::other_tok) \
		{ \
			return true; \
		}
	#define VALUE(other_str) 
	
	LIST_OF_PUNCT_TOKENS(VARNAME, VALUE)

	#undef VARNAME
	#undef VALUE

	return false;
}

bool Assembler::tok_is_ident_ish(PTok some_tok) const
{
	if (some_tok == nullptr)
	{
	}

	#define VARNAME(other_tok) \
		else if (some_tok == &Tok::other_tok) \
		{ \
			return true; \
		}
	#define VALUE(other_str) 
	
	LIST_OF_IDENT_ISH_TOKENS(VARNAME, VALUE)

	#undef VARNAME
	#undef VALUE

	return false;
}


// Code generator stuff
void Assembler::__encode_opcode(u16& high_hword, PInstr instr) const
{
	//for (const auto& outer_iter : __instr_tbl.instr_vec)
	for (size_t j=0; j<__instr_tbl.instr_vec.size(); ++j)
	{
		const auto& outer_iter = __instr_tbl.instr_vec.at(j);

		//for (const auto& other_instr : *outer_iter)
		for (size_t i=0; i<outer_iter->size(); ++i)
		{
			const auto& other_instr = outer_iter->at(i);
			if (instr == other_instr)
			{
				clear_and_set_bits_with_range(high_hword, i, 12, 8);
			}
		}
	}
}


void Assembler::encode_high_hword(u16& high_hword, PInstr instr) const
{
	__encode_instr_group(high_hword, instr);
	__encode_affects_flags(high_hword, instr);
	__encode_opcode(high_hword, instr);
}

void Assembler::gen8(s32 v)
{
	if (pass() == 1)
	{
		printf("%02x\n", (static_cast<u32>(v) & 0xff));
	}

	set_addr(addr() + 1);
}
void Assembler::gen16(s32 v)
{
	gen8(v >> 8);
	gen8(v);
}
void Assembler::gen32(s32 v)
{
	gen8(v >> 24);
	gen8(v >> 16);
	gen8(v >> 8);
	gen8(v);
}


}
