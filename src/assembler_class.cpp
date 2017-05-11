#include "assembler_class.hpp"

namespace navichip32
{


assembler::assembler( int argc, char** argv, std::FILE* s_infile )
	: infile(s_infile), lex( s_infile, &we, &internal_pass, &user_sym_tbl,
	&special_sym_tbl ), we(&lex)
{
	internal_args_vec.clear();
	
	for ( int i=0; i<argc; ++i )
	{
		internal_args_vec.push_back(string_view(argv[i]));
	}
	
	// General purpose registers
	special_sym_tbl.enter( "r0", static_cast<tok>(tok_defn::reg), 0, 
		true );
	special_sym_tbl.enter( "r1", static_cast<tok>(tok_defn::reg), 1,
		true );
	special_sym_tbl.enter( "r2", static_cast<tok>(tok_defn::reg), 2,
		true );
	special_sym_tbl.enter( "r3", static_cast<tok>(tok_defn::reg), 3,
		true );
	special_sym_tbl.enter( "r4", static_cast<tok>(tok_defn::reg), 4,
		true );
	special_sym_tbl.enter( "r5", static_cast<tok>(tok_defn::reg), 5,
		true );
	special_sym_tbl.enter( "r6", static_cast<tok>(tok_defn::reg), 6,
		true );
	special_sym_tbl.enter( "r7", static_cast<tok>(tok_defn::reg), 7,
		true );
	special_sym_tbl.enter( "r8", static_cast<tok>(tok_defn::reg), 8,
		true );
	special_sym_tbl.enter( "r9", static_cast<tok>(tok_defn::reg), 9,
		true );
	special_sym_tbl.enter( "r10", static_cast<tok>(tok_defn::reg), 10,
		true );
	special_sym_tbl.enter( "r11", static_cast<tok>(tok_defn::reg), 11,
		true );
	special_sym_tbl.enter( "r12", static_cast<tok>(tok_defn::reg), 12,
		true );
	special_sym_tbl.enter( "r13", static_cast<tok>(tok_defn::reg), 13,
		true );
	special_sym_tbl.enter( "r14", static_cast<tok>(tok_defn::reg), 14,
		true );
	special_sym_tbl.enter( "r15", static_cast<tok>(tok_defn::reg), 15,
		true );
	special_sym_tbl.enter( "lr", static_cast<tok>(tok_defn::reg), 14,
		true );
	special_sym_tbl.enter( "sp", static_cast<tok>(tok_defn::reg), 15,
		true );
	
	// Special purpose registers
	special_sym_tbl.enter( "flags", 
		static_cast<tok>(tok_defn::reg_flags), 0, true );
	special_sym_tbl.enter( "ira", 
		static_cast<tok>(tok_defn::reg_ira), 0, true );
	special_sym_tbl.enter( "pc", 
		static_cast<tok>(tok_defn::reg_pc), 0, true );
	
	
	insert_grp_0_instructions();
	insert_grp_1_instructions();
	insert_grp_2_instructions();
	insert_grp_3_instructions();
	
	// Make copies of all the instructions with ".f" appended to the name
	for ( auto iter=special_sym_tbl.cbegin(); 
		iter!=special_sym_tbl.cend();
		++iter )
	{
		const symbol* sym = &iter->second;
		
		special_sym_tbl.enter( std::string(sym->name())
			+ std::string(".f"), sym->typ(), sym->val(), true );
	}
}

assembler::~assembler()
{
}

int assembler::run()
{
	
	return 0;
}


// Code generator stuff
void assembler::genb( s32 v )
{
	if ( pass() == 0 )
	{
		if ( last_lc() != lc() )
		{
			printf( "@%08x\n", lc() );
		}
		printf( "%02x\n", ( v & 0xff ) );
	}
	
	set_last_lc(lc());
	set_lc( lc() + 1 );
}
void assembler::gen( s32 v )
{
	genb( v >> 24 );
	genb( v >> 16 );
	genb( v >> 8 );
	genb(v);
}

// Parser stuff
const instruction* assembler::determine_instr()
{
	const long orig_pos = std::ftell(infile);
	
	// Keep lineno so that the function that called this one doesn't have
	// to know about what happened to the lexer.
	lex_keep_lineno();
	
	const long reset_pos = std::ftell(infile);
	
	const symbol* instr_sym = lex.special_nextsym();
	
	if ( ( lex.special_nextsym() == nullptr )
		|| ( instr_sym->typ() != static_cast<tok>(tok_defn::instr) ) )
	{
		we.expected("instruction");
	}
	
	const std::vector<instruction>& instr_vec = instr_tbl.at(instr_sym);
	
	
	//// Go to the end of the line
	//while (!at_end_of_line())
	//{
	//	lex(true);
	//	
	//	if (!at_end_of_line())
	//	{
	//		////real_iarg to_push = { lex.nextt(), lex.nextval(),
	//		////	lex.nextsym(), lex.special_nextt(), lex.special_nextval(),
	//		////	lex.special_nextsym() };
	//		////iarg_vec.push_back(to_push);
	//		//real_iarg to_push = { lex.nextt(), lex.nextval(),
	//		//	lex.nextsym() };
	//	}
	//}
	
	for ( size_t i=0; i<instr_vec.size(); ++i )
	{
		const instruction& iter = instr_vec.at(i);
		
		lex_keep_lineno();
		
		if ( test_iargs(iter) )
		{
			return &iter;
		}
		
		std::fseek( infile, reset_pos, SEEK_SET );
	}
	
	std::fseek( infile, orig_pos, SEEK_SET );
	
	
	return nullptr;
}
bool assembler::test_iargs( const instruction& iter )
{
	switch ( iter.iargs() )
	{
		case instr_args::noargs:
			return test_instr_noargs();
		case instr_args::ra:
			return test_instr_ra();
		case instr_args::ra_rb:
			return test_instr_ra_rb();
		case instr_args::ra_imm16u:
			return test_instr_ra_imm16u();
		case instr_args::imm16u:
			return test_instr_imm16u();
		case instr_args::imm16s:
			return test_instr_imm16s();
		case instr_args::branchoffset:
			return test_instr_branchoffset();
		case instr_args::flags:
			return test_instr_flags();
		case instr_args::ra_flags:
			return test_instr_ra_flags();
		case instr_args::flags_ra:
			return test_instr_flags_ra();
		case instr_args::ira:
			return test_instr_ira();
		case instr_args::ira_ra:
			return test_instr_ira_ra();
		case instr_args::ra_ira:
			return test_instr_ra_ira();
		case instr_args::ra_pc:
			return test_instr_ra_pc();
		case instr_args::ra_rb_imm16u:
			return test_instr_ra_rb_imm16u();
		case instr_args::ra_rb_imm16s:
			return test_instr_ra_rb_imm16s();
		case instr_args::ra_rb_rc_imm12s:
			return test_instr_ra_rb_rc_imm12s();
		case instr_args::ra_rb_rc:
			return test_instr_ra_rb_rc();
		case instr_args::ra_rb_abs:
			return test_instr_ra_rb_abs();
		
		default:
			we.unknown("instr_args!");
			break;
	}
	
	
	return false;
}

bool assembler::test_instr_noargs()
{
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_ra()
{
	// rA
	if (!test_iarg_reg())
	{
		return false;
	}
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_ra_rb()
{
	// rA
	if (!test_iarg_reg())
	{
		return false;
	}
	
	// Comma
	if (!lex_match_keep_lineno(','))
	{
		return false;
	}
	
	// rB
	if (!test_iarg_reg())
	{
		return false;
	}
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_ra_imm16u()
{
	// rA
	if (!test_iarg_reg())
	{
		return false;
	}
	
	// Comma
	if (!lex_match_keep_lineno(','))
	{
		return false;
	}
	
	// imm16u
	if (!test_iarg_immed16())
	{
		return false;
	}
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_imm16u()
{
	// imm16u
	if (!test_iarg_immed16())
	{
		return false;
	}
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_imm16s()
{
	// imm16s
	if (!test_iarg_immed16())
	{
		return false;
	}
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_branchoffset()
{
	// branch offset (16-bit, signed)
	if (!test_iarg_braoffs())
	{
		return false;
	}
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_flags()
{
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_ra_flags()
{
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_flags_ra()
{
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_ira()
{
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_ira_ra()
{
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_ra_ira()
{
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_ra_pc()
{
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_ra_rb_imm16u()
{
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_ra_rb_imm16s()
{
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_ra_rb_rc_imm12s()
{
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_ra_rb_rc()
{
	
	return lex_match_keep_lineno('\n');
}
bool assembler::test_instr_ra_rb_abs()
{
	
	return lex_match_keep_lineno('\n');
}


s32 assembler::unary( bool use_special, bool keep_lineno, bool* did_fail,
	bool allow_fail )
{
	s32 v;
	
	decltype(&lexer::nextt) some_nextt;
	decltype(&lexer::nextval) some_nextval;
	
	if (!use_special)
	{
		some_nextt = &lexer::nextt;
		some_nextval = &lexer::nextval;
	}
	else
	{
		some_nextt = &lexer::special_nextt;
		some_nextval = &lexer::special_nextval;
	}
	
	switch ((lex.*some_nextt)())
	{
		case static_cast<tok>(tok_defn::ident):
		case static_cast<tok>(tok_defn::number):
			v = (lex.*some_nextval)();
			lex(keep_lineno);
			break;
		
		case '-':
			lex(keep_lineno);
			return -unary( use_special, keep_lineno, did_fail, allow_fail );
		
		case '(':
			lex(keep_lineno);
			v = expr( use_special, keep_lineno, did_fail, allow_fail );
			
			//if (!lex.match( ')', keep_lineno ))
			if ( !lex_match_keep_lineno(')') && !allow_fail )
			{
				we.warn1("Missing ')' assumed");
			}
			break;
		
		default:
			if ( did_fail != nullptr )
			{
				*did_fail = true;
			}
			if (!allow_fail)
			{
				we.error("Ill-formed expression");
			}
			break;
	}
	
	return v;
}

s32 assembler::expr( bool use_special, bool keep_lineno, bool* did_fail,
	bool allow_fail, bool did_init )
{
	if ( !did_init && ( did_fail != nullptr ) )
	{
		*did_fail = false;
	}
	
	s32 v = unary( use_special, keep_lineno, did_fail, allow_fail );
	
	decltype(&lexer::nextt) some_nextt;
	
	if (!use_special)
	{
		some_nextt = &lexer::nextt;
	}
	else
	{
		some_nextt = &lexer::special_nextt;
	}
	
	while ( ( (lex.*some_nextt)() == '+' ) 
		|| ( (lex.*some_nextt)() == '-' ) )
	{
		switch ((lex.*some_nextt)())
		{
			case '+':
				lex(keep_lineno);
				v += unary( use_special, keep_lineno, did_fail, 
					allow_fail );
				break;
			case '-':
				lex(keep_lineno);
				v -= unary( use_special, keep_lineno, did_fail,
					allow_fail );
				break;
		}
	}
	
	return v;
}


s32 assembler::mask_immed( s32 to_mask, size_t mask )
{
	const u32 temp_0 = abs(to_mask);
	
	const u32 temp_1 = temp_0 & mask; 
	
	if ( to_mask < 0 )
	{
		const s32 temp_2 = temp_1;
		const s32 temp_3 = -temp_2;
		return temp_3;
	}
	
	return static_cast<s32>(temp_1);
}


s32 assembler::iarg_specific_reg( tok_defn typ, 
	const string_view& fail_msg, bool keep_lineno, 
	bool* did_fail, bool allow_fail )
{
	//expr( true, keep_lineno );
	lex(keep_lineno);
	
	if ( did_fail != nullptr )
	{
		*did_fail = false;
	}
	
	if ( ( lex.special_nextsym() != nullptr )
		&& ( lex.special_nextsym()->typ() == static_cast<tok>(typ) ) )
	{
		return lex.special_nextsym()->val();
	}
	
	if (!allow_fail)
	{
		we.expected(fail_msg);
	}
	if ( did_fail != nullptr )
	{
		*did_fail = true;
	}
	return -1;
}


s32 assembler::iarg_braoffs( bool keep_lineno, bool* did_fail, 
	bool allow_fail )
{
	const s32 temp_0 = expr( false, keep_lineno, did_fail, allow_fail,
		false );
	const s32 temp_1 = mask_immed( temp_0, ( ( 1 << 16 ) - 1 ) );
	
	if ( temp_1 != temp_0 )
	{
		if (!allow_fail)
		{
			we.error("Branch offset out of range.");
		}
	}
	
	return temp_1;
}
s32 assembler::iarg_immed16( bool keep_lineno, bool* did_fail, 
	bool allow_fail )
{
	const s32 temp_0 = expr( false, keep_lineno, did_fail, allow_fail,
		false );
	const s32 temp_1 = mask_immed( temp_0, ( ( 1 << 16 ) - 1 ) );
	
	if ( temp_1 != temp_0 )
	{
		if (!allow_fail)
		{
			we.warn( "Immediate value (16-bit) out of range, has been ",
				"masked." );
		}
	}
	
	return temp_1;
}
s32 assembler::iarg_immed12( bool keep_lineno, bool* did_fail, 
	bool allow_fail )
{
	const s32 temp_0 = expr( false, keep_lineno, did_fail, allow_fail,
		false );
	const s32 temp_1 = mask_immed( temp_0, ( ( 1 << 12 ) - 1 ) );
	
	if ( temp_1 != temp_0 )
	{
		if (!allow_fail)
		{
			we.warn( "Immediate value (12-bit) out of range, has been ",
				"masked." );
		}
	}
	
	return temp_1;
}


s32 assembler::line()
{
	
	
}


}
