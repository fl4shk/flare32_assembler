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

		//printout("\n\n");
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


	// Find assembler directives
	#define VALUE(some_str)

	if (next_char() == '.')
	{
		advance();
		while (isalnum(next_char()) || next_char() == '_')
		{
			next_str += next_char();
			advance();
		}

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

		LIST_OF_DIRECTIVE_TOKENS(VARNAME, VALUE)
		#undef VARNAME
	}



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

		if (next_char() == '.')
		{
			next_str += next_char();
			advance();

			while (isalnum(next_char()) || (next_char() == '_'))
			{
				next_str += next_char();
				advance();
			}
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

		return;
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

	set_next_tok(&Tok::Bad);
}

void Assembler::line()
{
	std::vector<ParseNode> parse_vec, second_parse_vec;

	while ((next_tok() != &Tok::Newline) && (next_tok() != &Tok::Eof)
		&& (next_tok() != &Tok::Bad))
	{
		parse_vec.push_back(ParseNode(next_tok(), next_sym_str(),
			next_num()));
		lex();
	}

	if (next_tok() == &Tok::Bad)
	{
		set_line_num(line_num() + 1);
		err("Invalid syntax");
	}

	if (parse_vec.size() == 0)
	{
		lex();
		return;
	}

	//for (const auto& node : parse_vec)
	//{
	//	printout(node.next_tok->str(), "\t\t");
	//}
	//printout("\n");

	size_t index = 1;

	// Check for assembler directives
	if (parse_vec.front().next_tok == &Tok::DotOrg)
	{
		set_addr(handle_expr(parse_vec, index));

		if (index != parse_vec.size())
		{
			err("extra characters on line");
		}

		return;
	}


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

	
	#define VARNAME(stuff) (parse_vec.at(i).next_tok == &Tok::stuff) ||
	#define VALUE(stuff)

	if (!found_label)
	{
		for (size_t i=0; i<parse_vec.size(); ++i)
		{
			// Ignore comments
			//if (parse_vec.at(i).next_tok == &Tok::Semicolon)
			if (LIST_OF_COMMENT_TOKENS(VARNAME, VALUE) false)
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
			//if (parse_vec.at(i).next_tok == &Tok::Semicolon)
			if (LIST_OF_COMMENT_TOKENS(VARNAME, VALUE) false)
			{
				break;
			}
			second_parse_vec.push_back(parse_vec.at(i));
		}
	}
	#undef VARNAME
	#undef VALUE

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

		case InstrArgs::branch:
			return __parse_instr_branch(some_parse_vec,
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

#define spvat(x) some_parse_vec.at(x)

bool Assembler::__parse_instr_no_args
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	//size_t index = 1;
	s64 expr_result = 0;

	// op
	if (some_parse_vec.size() != 1)
	{
		return false;
	}

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_uimm16
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op expr
	if (some_parse_vec.size() < 2)
	{
		return false;
	}

	expr_result = handle_expr(some_parse_vec, index);

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_simm16
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op expr
	if (some_parse_vec.size() < 2)
	{
		return false;
	}

	expr_result = handle_expr(some_parse_vec, index);

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_imm32
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op expr
	if (some_parse_vec.size() < 2)
	{
		return false;
	}

	expr_result = handle_expr(some_parse_vec, index);

	encode_and_gen(regs, expr_result, instr);

	return true;
}

bool Assembler::__parse_instr_ra
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	//size_t index = 1;
	s64 expr_result = 0;


	// op rA
	if (some_parse_vec.size() != 2)
	{
		return false;
	}

	if (spvat(1).next_tok != &Tok::Reg)
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_ra_uimm16
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , expr
	if (some_parse_vec.size() < 4)
	{
		return false;
	}


	if ((spvat(index++).next_tok != &Tok::Reg)
		|| (spvat(index++).next_tok != &Tok::Comma))
	{
		return false;
	}

	expr_result = handle_expr(some_parse_vec, index);

	regs.push_back(spvat(1).next_sym_str);

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_ra_rb
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , rB
	if (some_parse_vec.size() != 4)
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma, 
		&Tok::Reg))
	{
		return false;
	}


	regs.push_back(spvat(1).next_sym_str);
	regs.push_back(spvat(3).next_sym_str);

	
	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_ra_rb_uimm16
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , rB , expr
	if (some_parse_vec.size() < 6)
	{
		return false;
	}


	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma,
		&Tok::Reg, &Tok::Comma))
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);
	regs.push_back(spvat(3).next_sym_str);

	expr_result = handle_expr(some_parse_vec, index);

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_ra_rb_simm16
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , rB , expr
	if (some_parse_vec.size() < 6)
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma,
		&Tok::Reg, &Tok::Comma))
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);
	regs.push_back(spvat(3).next_sym_str);

	expr_result = handle_expr(some_parse_vec, index);

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_ra_rb_rc
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , rB , rC
	if (some_parse_vec.size() != 6)
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma,
		&Tok::Reg, &Tok::Comma, &Tok::Reg))
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);
	regs.push_back(spvat(3).next_sym_str);
	regs.push_back(spvat(5).next_sym_str);

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_ra_rb_rc_simm12
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , rB , rC , expr
	if (some_parse_vec.size() < 8)
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma,
		&Tok::Reg, &Tok::Comma, &Tok::Reg, &Tok::Comma))
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);
	regs.push_back(spvat(3).next_sym_str);
	regs.push_back(spvat(5).next_sym_str);


	expr_result = handle_expr(some_parse_vec, index);


	encode_and_gen(regs, expr_result, instr);

	return true;
}

bool Assembler::__parse_instr_ldst_ra_rb
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , [ rB ]
	if (some_parse_vec.size() != 6)
	{
		return false;
	}


	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma,
		&Tok::LBracket, &Tok::Reg, &Tok::RBracket))
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);
	regs.push_back(spvat(4).next_sym_str);

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_ldst_ra_rb_rc_simm12
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , [ rB , rC , expr ]
	if ((some_parse_vec.size() < 10)
		|| (some_parse_vec.back().next_tok != &Tok::RBracket))
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma,
		&Tok::LBracket, // [
		&Tok::Reg, &Tok::Comma, // rB ,
		&Tok::Reg, &Tok::Comma)) // rC ,
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);
	regs.push_back(spvat(4).next_sym_str);
	regs.push_back(spvat(6).next_sym_str);

	expr_result = handle_expr(some_parse_vec, index);

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_ldst_ra_rb_rc
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , [ rB , rC ]
	if ((some_parse_vec.size() != 8)
		|| (some_parse_vec.back().next_tok != &Tok::RBracket))
	{
		return false;
	}


	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma,
		&Tok::LBracket, // [
		&Tok::Reg, &Tok::Comma, // rB ,
		&Tok::Reg, // rC
		&Tok::RBracket))  // ]
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);
	regs.push_back(spvat(4).next_sym_str);
	regs.push_back(spvat(6).next_sym_str);

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_ldst_ra_rb_simm12
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , [ rB , expr ]
	if ((some_parse_vec.size() < 8)
		|| (some_parse_vec.back().next_tok != &Tok::RBracket))
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma,
		&Tok::LBracket, // [
		&Tok::Reg, &Tok::Comma)) // rB ,
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);
	regs.push_back(spvat(4).next_sym_str);

	expr_result = handle_expr(some_parse_vec, index);

	encode_and_gen(regs, expr_result, instr);

	return true;
}


bool Assembler::__parse_instr_branch
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op expr
	if (some_parse_vec.size() < 2)
	{
		return false;
	}

	expr_result = handle_expr(some_parse_vec, index) - addr();

	switch (instr->enc_group())
	{
		case 0:
			expr_result -= 2;
			break;

		case 1:
			expr_result -= 4;
			break;

		case 2:
			expr_result -= 4;
			break;

		case 3:
			expr_result -= 6;
			break;
	}


	encode_and_gen(regs, expr_result, instr);

	return true;
}


bool Assembler::__parse_instr_ldst_ra_rb_imm32
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , [ rB , expr ]
	if ((some_parse_vec.size() < 8)
		|| (some_parse_vec.back().next_tok != &Tok::RBracket))
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma,
		&Tok::LBracket, // [
		&Tok::Reg, &Tok::Comma)) // rB ,
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);
	regs.push_back(spvat(4).next_sym_str);

	expr_result = handle_expr(some_parse_vec, index);

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_ra_rb_imm32
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , rB , expr
	if (some_parse_vec.size() < 6)
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma,
		&Tok::Reg, &Tok::Comma))
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);
	regs.push_back(spvat(3).next_sym_str);


	expr_result = handle_expr(some_parse_vec, index);

	encode_and_gen(regs, expr_result, instr);

	return true;
}


// Block moves (ldmia, stmia, stmdb) with number of {} args
bool Assembler::__parse_instr_ldst_block_1_to_4
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , { rB }
	if (some_parse_vec.size() == 6)
	{
		const auto node1 = spvat(index++);
		const auto node2 = spvat(index++);
		const auto node3 = spvat(index++);
		const auto node4 = spvat(index++);
		const auto node5 = spvat(index++);

		if ((node1.next_tok != &Tok::Reg)
			|| (node2.next_tok != &Tok::Comma)
			|| (node3.next_tok != &Tok::LBrace)
			|| (node4.next_tok != &Tok::Reg)
			|| (node5.next_tok != &Tok::RBrace))
		{
			return false;
		}

		regs.push_back(node1.next_sym_str);
		regs.push_back(node4.next_sym_str);
	}

	// op rA , { rB , rC }
	else if (some_parse_vec.size() == 8)
	{
		const auto node1 = spvat(index++);
		const auto node2 = spvat(index++);
		const auto node3 = spvat(index++);
		const auto node4 = spvat(index++);
		const auto node5 = spvat(index++);
		const auto node6 = spvat(index++);
		const auto node7 = spvat(index++);

		if ((node1.next_tok != &Tok::Reg)
			|| (node2.next_tok != &Tok::Comma)
			|| (node3.next_tok != &Tok::LBrace)
			|| (node4.next_tok != &Tok::Reg)
			|| (node5.next_tok != &Tok::Comma)
			|| (node6.next_tok != &Tok::Reg)
			|| (node7.next_tok != &Tok::RBrace))
		{
			return false;
		}

		regs.push_back(node1.next_sym_str);
		regs.push_back(node4.next_sym_str);
		regs.push_back(node6.next_sym_str);
	}
	// op rA , { rB , rC , rD }
	else if (some_parse_vec.size() == 10)
	{
		const auto node1 = spvat(index++);
		const auto node2 = spvat(index++);
		const auto node3 = spvat(index++);
		const auto node4 = spvat(index++);
		const auto node5 = spvat(index++);
		const auto node6 = spvat(index++);
		const auto node7 = spvat(index++);
		const auto node8 = spvat(index++);
		const auto node9 = spvat(index++);

		if ((node1.next_tok != &Tok::Reg)
			|| (node2.next_tok != &Tok::Comma)
			|| (node3.next_tok != &Tok::LBrace)
			|| (node4.next_tok != &Tok::Reg)
			|| (node5.next_tok != &Tok::Comma)
			|| (node6.next_tok != &Tok::Reg)
			|| (node7.next_tok != &Tok::Comma)
			|| (node8.next_tok != &Tok::Reg)
			|| (node9.next_tok != &Tok::RBrace))
		{
			return false;
		}

		regs.push_back(node1.next_sym_str);
		regs.push_back(node4.next_sym_str);
		regs.push_back(node6.next_sym_str);
		regs.push_back(node8.next_sym_str);
	}
	// op rA , { rB , rC , rD , rE }
	else if (some_parse_vec.size() == 12)
	{
		const auto node1 = spvat(index++);
		const auto node2 = spvat(index++);
		const auto node3 = spvat(index++);
		const auto node4 = spvat(index++);
		const auto node5 = spvat(index++);
		const auto node6 = spvat(index++);
		const auto node7 = spvat(index++);
		const auto node8 = spvat(index++);
		const auto node9 = spvat(index++);
		const auto node10 = spvat(index++);
		const auto node11 = spvat(index++);

		if ((node1.next_tok != &Tok::Reg)
			|| (node2.next_tok != &Tok::Comma)
			|| (node3.next_tok != &Tok::LBrace)
			|| (node4.next_tok != &Tok::Reg)
			|| (node5.next_tok != &Tok::Comma)
			|| (node6.next_tok != &Tok::Reg)
			|| (node7.next_tok != &Tok::Comma)
			|| (node8.next_tok != &Tok::Reg)
			|| (node9.next_tok != &Tok::Comma)
			|| (node10.next_tok != &Tok::Reg)
			|| (node11.next_tok != &Tok::RBrace))
		{
			return false;
		}

		regs.push_back(node1.next_sym_str);
		regs.push_back(node4.next_sym_str);
		regs.push_back(node6.next_sym_str);
		regs.push_back(node8.next_sym_str);
		regs.push_back(node10.next_sym_str);
	}
	else
	{
		return false;
	}

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_ldst_block_5_to_8
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op rA , { rB , rC , rD , rE , rF }
	if (some_parse_vec.size() == 14)
	{
		const auto node1 = spvat(index++);
		const auto node2 = spvat(index++);
		const auto node3 = spvat(index++);
		const auto node4 = spvat(index++);
		const auto node5 = spvat(index++);
		const auto node6 = spvat(index++);
		const auto node7 = spvat(index++);
		const auto node8 = spvat(index++);
		const auto node9 = spvat(index++);
		const auto node10 = spvat(index++);
		const auto node11 = spvat(index++);
		const auto node12 = spvat(index++);
		const auto node13 = spvat(index++);

		if ((node1.next_tok != &Tok::Reg)
			|| (node2.next_tok != &Tok::Comma)
			|| (node3.next_tok != &Tok::LBrace)
			|| (node4.next_tok != &Tok::Reg)
			|| (node5.next_tok != &Tok::Comma)
			|| (node6.next_tok != &Tok::Reg)
			|| (node7.next_tok != &Tok::Comma)
			|| (node8.next_tok != &Tok::Reg)
			|| (node9.next_tok != &Tok::Comma)
			|| (node10.next_tok != &Tok::Reg)
			|| (node11.next_tok != &Tok::Comma)
			|| (node12.next_tok != &Tok::Reg)
			|| (node13.next_tok != &Tok::RBrace))
		{
			return false;
		}

		regs.push_back(node1.next_sym_str);
		regs.push_back(node4.next_sym_str);
		regs.push_back(node6.next_sym_str);
		regs.push_back(node8.next_sym_str);
		regs.push_back(node10.next_sym_str);
		regs.push_back(node12.next_sym_str);
	}
	// op rA , { rB , rC , rD , rE , rF , rG }
	else if (some_parse_vec.size() == 16)
	{
		const auto node1 = spvat(index++);
		const auto node2 = spvat(index++);
		const auto node3 = spvat(index++);
		const auto node4 = spvat(index++);
		const auto node5 = spvat(index++);
		const auto node6 = spvat(index++);
		const auto node7 = spvat(index++);
		const auto node8 = spvat(index++);
		const auto node9 = spvat(index++);
		const auto node10 = spvat(index++);
		const auto node11 = spvat(index++);
		const auto node12 = spvat(index++);
		const auto node13 = spvat(index++);
		const auto node14 = spvat(index++);
		const auto node15 = spvat(index++);

		if ((node1.next_tok != &Tok::Reg)
			|| (node2.next_tok != &Tok::Comma)
			|| (node3.next_tok != &Tok::LBrace)
			|| (node4.next_tok != &Tok::Reg)
			|| (node5.next_tok != &Tok::Comma)
			|| (node6.next_tok != &Tok::Reg)
			|| (node7.next_tok != &Tok::Comma)
			|| (node8.next_tok != &Tok::Reg)
			|| (node9.next_tok != &Tok::Comma)
			|| (node10.next_tok != &Tok::Reg)
			|| (node11.next_tok != &Tok::Comma)
			|| (node12.next_tok != &Tok::Reg)
			|| (node13.next_tok != &Tok::Comma)
			|| (node14.next_tok != &Tok::Reg)
			|| (node15.next_tok != &Tok::RBrace))
		{
			return false;
		}

		regs.push_back(node1.next_sym_str);
		regs.push_back(node4.next_sym_str);
		regs.push_back(node6.next_sym_str);
		regs.push_back(node8.next_sym_str);
		regs.push_back(node10.next_sym_str);
		regs.push_back(node12.next_sym_str);
		regs.push_back(node14.next_sym_str);
	}
	// op rA , { rB , rC , rD , rE , rF , rG , rH }
	else if (some_parse_vec.size() == 18)
	{
		const auto node1 = spvat(index++);
		const auto node2 = spvat(index++);
		const auto node3 = spvat(index++);
		const auto node4 = spvat(index++);
		const auto node5 = spvat(index++);
		const auto node6 = spvat(index++);
		const auto node7 = spvat(index++);
		const auto node8 = spvat(index++);
		const auto node9 = spvat(index++);
		const auto node10 = spvat(index++);
		const auto node11 = spvat(index++);
		const auto node12 = spvat(index++);
		const auto node13 = spvat(index++);
		const auto node14 = spvat(index++);
		const auto node15 = spvat(index++);
		const auto node16 = spvat(index++);
		const auto node17 = spvat(index++);

		if ((node1.next_tok != &Tok::Reg)
			|| (node2.next_tok != &Tok::Comma)
			|| (node3.next_tok != &Tok::LBrace)
			|| (node4.next_tok != &Tok::Reg)
			|| (node5.next_tok != &Tok::Comma)
			|| (node6.next_tok != &Tok::Reg)
			|| (node7.next_tok != &Tok::Comma)
			|| (node8.next_tok != &Tok::Reg)
			|| (node9.next_tok != &Tok::Comma)
			|| (node10.next_tok != &Tok::Reg)
			|| (node11.next_tok != &Tok::Comma)
			|| (node12.next_tok != &Tok::Reg)
			|| (node13.next_tok != &Tok::Comma)
			|| (node14.next_tok != &Tok::Reg)
			|| (node15.next_tok != &Tok::Comma)
			|| (node16.next_tok != &Tok::Reg)
			|| (node17.next_tok != &Tok::RBrace))
		{
			return false;
		}

		regs.push_back(node1.next_sym_str);
		regs.push_back(node4.next_sym_str);
		regs.push_back(node6.next_sym_str);
		regs.push_back(node8.next_sym_str);
		regs.push_back(node10.next_sym_str);
		regs.push_back(node12.next_sym_str);
		regs.push_back(node14.next_sym_str);
		regs.push_back(node16.next_sym_str);
	}
	// op rA , { rB , rC , rD , rE , rF , rG , rH , rI }
	else if (some_parse_vec.size() == 20)
	{
		const auto node1 = spvat(index++);
		const auto node2 = spvat(index++);
		const auto node3 = spvat(index++);
		const auto node4 = spvat(index++);
		const auto node5 = spvat(index++);
		const auto node6 = spvat(index++);
		const auto node7 = spvat(index++);
		const auto node8 = spvat(index++);
		const auto node9 = spvat(index++);
		const auto node10 = spvat(index++);
		const auto node11 = spvat(index++);
		const auto node12 = spvat(index++);
		const auto node13 = spvat(index++);
		const auto node14 = spvat(index++);
		const auto node15 = spvat(index++);
		const auto node16 = spvat(index++);
		const auto node17 = spvat(index++);
		const auto node18 = spvat(index++);
		const auto node19 = spvat(index++);

		if ((node1.next_tok != &Tok::Reg)
			|| (node2.next_tok != &Tok::Comma)
			|| (node3.next_tok != &Tok::LBrace)
			|| (node4.next_tok != &Tok::Reg)
			|| (node5.next_tok != &Tok::Comma)
			|| (node6.next_tok != &Tok::Reg)
			|| (node7.next_tok != &Tok::Comma)
			|| (node8.next_tok != &Tok::Reg)
			|| (node9.next_tok != &Tok::Comma)
			|| (node10.next_tok != &Tok::Reg)
			|| (node11.next_tok != &Tok::Comma)
			|| (node12.next_tok != &Tok::Reg)
			|| (node13.next_tok != &Tok::Comma)
			|| (node14.next_tok != &Tok::Reg)
			|| (node15.next_tok != &Tok::Comma)
			|| (node16.next_tok != &Tok::Reg)
			|| (node17.next_tok != &Tok::Comma)
			|| (node18.next_tok != &Tok::Reg)
			|| (node19.next_tok != &Tok::RBrace))
		{
			return false;
		}

		regs.push_back(node1.next_sym_str);
		regs.push_back(node4.next_sym_str);
		regs.push_back(node6.next_sym_str);
		regs.push_back(node8.next_sym_str);
		regs.push_back(node10.next_sym_str);
		regs.push_back(node12.next_sym_str);
		regs.push_back(node14.next_sym_str);
		regs.push_back(node16.next_sym_str);
		regs.push_back(node18.next_sym_str);
	}
	else
	{
		return false;
	}

	encode_and_gen(regs, expr_result, instr);

	return true;
}

bool Assembler::__parse_instr_ira
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op ira
	if (some_parse_vec.size() != 2)
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::RegIra))
	{
		return false;
	}

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_ra_ira
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;


	// op rA , ira
	if (some_parse_vec.size() != 4)
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma,
		&Tok::RegIra))
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_ira_ra
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op ira , rA
	if (some_parse_vec.size() != 4)
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::RegIra, &Tok::Comma,
		&Tok::Reg))
	{
		return false;
	}

	regs.push_back(spvat(3).next_sym_str);

	encode_and_gen(regs, expr_result, instr);

	return true;
}

bool Assembler::__parse_instr_ra_flags
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;


	// op rA , flags
	if (some_parse_vec.size() != 4)
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma,
		&Tok::RegFlags))
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_flags
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op flags
	if (some_parse_vec.size() != 2)
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::RegFlags))
	{
		return false;
	}

	encode_and_gen(regs, expr_result, instr);

	return true;
}
bool Assembler::__parse_instr_flags_ra
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;

	// op flags , rA
	if (some_parse_vec.size() != 4)
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::RegFlags, &Tok::Comma,
		&Tok::Reg))
	{
		return false;
	}

	regs.push_back(spvat(3).next_sym_str);

	encode_and_gen(regs, expr_result, instr);

	return true;
}

bool Assembler::__parse_instr_ra_pc
	(const std::vector<Assembler::ParseNode>& some_parse_vec, PInstr instr)
{
	std::vector<std::string> regs;
	size_t index = 1;
	s64 expr_result = 0;


	// op rA , pc
	if (some_parse_vec.size() != 4)
	{
		return false;
	}

	if (!check_tokens(some_parse_vec, index, &Tok::Reg, &Tok::Comma,
		&Tok::RegPc))
	{
		return false;
	}

	regs.push_back(spvat(1).next_sym_str);

	encode_and_gen(regs, expr_result, instr);

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

		ret = -handle_term(some_parse_vec, index);
	}
	else if (some_parse_vec.at(index).next_tok == &Tok::Plus)
	{
		//lex();
		++index;

		ret = handle_term(some_parse_vec, index);
	}
	else if (tok_is_ident_ish(some_parse_vec.at(index).next_tok)
		|| (some_parse_vec.at(index).next_tok == &Tok::NatNum)
		|| (some_parse_vec.at(index).next_tok == &Tok::LParen))
	{
		ret = handle_term(some_parse_vec, index);
	}
	else if (some_parse_vec.at(index).next_tok == &Tok::Period)
	{
		ret = addr();
	}
	else
	{
		//err("expr():  3, Eek!\n");
		//return 9001;
		err("Invalid expression");
	}



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
				return;
			}
		}
	}
}


void Assembler::__encode_high_hword(u16& high_hword, 
	const std::vector<std::string>& regs, s64 expr_result, PInstr instr)
{
	__encode_instr_group(high_hword, instr);
	__encode_affects_flags(high_hword, instr);
	__encode_opcode(high_hword, instr);

	switch (instr->args())
	{
		case InstrArgs::ldst_block_1_to_4:
		case InstrArgs::ldst_block_5_to_8:
			// Encode rA
			if (regs.size() >= 2)
			{
				clear_and_set_bits_with_range(high_hword, 
					builtin_sym_tbl().at(regs.at(1)).value(), 7, 4);
			}

			// Encode rB
			if (regs.size() >= 3)
			{
				clear_and_set_bits_with_range(high_hword, 
					builtin_sym_tbl().at(regs.at(2)).value(), 3, 0);
			}
			
			break;

		default:
			// Encode rA
			if (regs.size() >= 1)
			{
				clear_and_set_bits_with_range(high_hword, 
					builtin_sym_tbl().at(regs.at(0)).value(), 7, 4);
			}

			// Encode rB
			if (regs.size() >= 2)
			{
				clear_and_set_bits_with_range(high_hword, 
					builtin_sym_tbl().at(regs.at(1)).value(), 3, 0);
			}
			break;
	}

}


void Assembler::__encode_low(u16& g1g2_low, u32& g3_low, 
	const std::vector<std::string>& regs, s64 expr_result, PInstr instr)
{
	auto handle_enc_group_2 = [&]() -> void
	{
		// Non-block moves version
		if (instr->args() != InstrArgs::ldst_block_1_to_4)
		{
			if (regs.size() == 3)
			{
				clear_and_set_bits_with_range(g1g2_low, 
					builtin_sym_tbl().at(regs.at(2)).value(), 15, 12);
			}
			else if (regs.size() > 3)
			{
				err("__encode_low()::handle_enc_group_2() non else:  ",
					"Eek!\n");
			}
			clear_and_set_bits_with_range(g1g2_low, expr_result, 11, 0);
		}

		// Block moves version
		else
		{
			clear_and_set_bits_with_range(g1g2_low, regs.size() - 2, 1, 0);

			clear_and_set_bits_with_range(g1g2_low, 
				builtin_sym_tbl().at(regs.at(0)).value(), 7, 4);

			//if (regs.size() >= 3)
			//{
			//		
			//		
			//}
			if (regs.size() >= 4)
			{
				clear_and_set_bits_with_range(g1g2_low, 
					builtin_sym_tbl().at(regs.at(3)).value(), 15, 12);
			}
			if (regs.size() >= 5)
			{
				clear_and_set_bits_with_range(g1g2_low,
					builtin_sym_tbl().at(regs.at(4)).value(), 11, 8);
			}

			if ((regs.size() < 2) || (regs.size() > 5))
			{
				err("__encode_low()::handle_enc_group_2() else:  Eek!\n");
			}
		}
	};

	auto handle_enc_group_3 = [&]() -> void
	{
		// Non-block moves version
		if (instr->args() != InstrArgs::ldst_block_5_to_8)
		{
			//if (regs.size() == 3)
			//{
			//	clear_and_set_bits_with_range(g3_low, 
			//		builtin_sym_tbl().at(regs.at(2)).value(), 15, 12);
			//}
			//else if (regs.size() > 3)
			//{
			//	err("__encode_low()::handle_enc_group_3() non else:  ",
			//		"Eek!\n");
			//}
			g3_low = expr_result;
		}

		// Block moves version
		else
		{
			clear_and_set_bits_with_range(g3_low, regs.size() - 6, 1, 0);

			clear_and_set_bits_with_range(g3_low, 
				builtin_sym_tbl().at(regs.at(0)).value(), 7, 4);

			//if (regs.size() >= 3)
			//{
			//		
			//		
			//}

			//if (regs.size() >= 4)
			{
				clear_and_set_bits_with_range(g3_low, 
					builtin_sym_tbl().at(regs.at(3)).value(), 31, 28);
			}
			//if (regs.size() >= 5)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(4)).value(), 27, 24);
			}
			if (regs.size() >= 6)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(5)).value(), 23, 20);
			}
			if (regs.size() >= 7)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(6)).value(), 19, 16);
			}
			if (regs.size() >= 8)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(7)).value(), 15, 12);
			}
			if (regs.size() >= 9)
			{
				clear_and_set_bits_with_range(g3_low,
					builtin_sym_tbl().at(regs.at(8)).value(), 11, 8);
			}

			//clear_and_set_bits_with_range(g3_low,
			//	builtin_sym_tbl().at(regs.at()));

			if ((regs.size() < 6) || (regs.size() > 9))
			{
				err("__encode_low()::handle_enc_group_3() else:  Eek!\n");
			}
		}

	};

	switch (instr->enc_group())
	{
		case 0:
			break;

		case 1:
			g1g2_low = expr_result;
			break;

		case 2:
			handle_enc_group_2();
			break;

		case 3:
			handle_enc_group_3();
			break;
	}
}

void Assembler::encode_and_gen
	(const std::vector<std::string>& regs, s64 expr_result, 
	PInstr instr)
{
	u16 high_hword = 0;
	u16 g1g2_low = 0;
	u32 g3_low = 0;

	__encode_high_hword(high_hword, regs, expr_result, instr);
	__encode_low(g1g2_low, g3_low, regs, expr_result, instr);
	gen16(high_hword);
	__gen_low(g1g2_low, g3_low, instr);

	if (pass() == 1)
	{
		printout("\n");
	}

}


#undef spvat


void Assembler::__gen_low(u16 g1g2_low, u32 g3_low, PInstr instr) 
{
	switch (instr->enc_group())
	{
		case 0:
			break;

		case 1:
			gen16(g1g2_low);
			break;

		case 2:
			gen16(g1g2_low);
			break;

		case 3:
			gen32(g3_low);
			break;
	}
}

void Assembler::gen8(s32 v)
{
	if (pass() == 1)
	{
		if (last_addr() != addr())
		{
			printf("@%08x\n", static_cast<u32>(addr()));
		}
		printf("%02x\n", (static_cast<u32>(v) & 0xff));
	}

	set_last_addr(set_addr(addr() + 1));
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
