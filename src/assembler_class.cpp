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
const instruction* assembler::determine_instr
	( std::vector<assembler::real_iarg>& iarg_vec )
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
		iarg_vec.clear();
		
		lex_keep_lineno();
		
		if ( test_iargs( iter, iarg_vec ) )
		{
			return &iter;
		}
		
		std::fseek( infile, reset_pos, SEEK_SET );
	}
	
	std::fseek( infile, orig_pos, SEEK_SET );
	
	
	return nullptr;
}
bool assembler::test_iargs( const instruction& iter,
	std::vector<assembler::real_iarg>& iarg_vec )
{
	switch ( iter.iargs() )
	{
		case instr_args::noargs:
			return test_instr_noargs( iter, iarg_vec );
		case instr_args::ra:
			return test_instr_ra( iter, iarg_vec );
		case instr_args::ra_rb:
			return test_instr_ra_rb( iter, iarg_vec );
		case instr_args::ra_imm16u:
			return test_instr_ra_imm16u( iter, iarg_vec );
		case instr_args::imm16u:
			return test_instr_imm16u( iter, iarg_vec );
		case instr_args::imm16s:
			return test_instr_imm16s( iter, iarg_vec );
		case instr_args::branchoffset:
			return test_instr_branchoffset( iter, iarg_vec );
		case instr_args::flags:
			return test_instr_flags( iter, iarg_vec );
		case instr_args::ra_flags:
			return test_instr_ra_flags( iter, iarg_vec );
		case instr_args::flags_ra:
			return test_instr_flags_ra( iter, iarg_vec );
		case instr_args::ira:
			return test_instr_ira( iter, iarg_vec );
		case instr_args::ira_ra:
			return test_instr_ira_ra( iter, iarg_vec );
		case instr_args::ra_ira:
			return test_instr_ra_ira( iter, iarg_vec );
		case instr_args::ra_pc:
			return test_instr_ra_pc( iter, iarg_vec );
		case instr_args::ra_rb_imm16u:
			return test_instr_ra_rb_imm16u( iter, iarg_vec );
		case instr_args::ra_rb_imm16s:
			return test_instr_ra_rb_imm16s( iter, iarg_vec );
		case instr_args::ra_rb_rc_imm12s:
			return test_instr_ra_rb_rc_imm12s( iter, iarg_vec );
		case instr_args::ra_rb_rc:
			return test_instr_ra_rb_rc( iter, iarg_vec );
		case instr_args::ra_rb_abs:
			return test_instr_ra_rb_abs( iter, iarg_vec );
		
		default:
			we.unknown("instr_args!");
			break;
	}
	
	
	return false;
}


bool assembler::test_instr_noargs( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	if (lex_match_keep_lineno('\n'))
	{
		return true;
	}
	return false;
}
bool assembler::test_instr_ra( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_ra_rb( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_ra_imm16u( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_imm16u( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_imm16s( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_branchoffset( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_flags( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_ra_flags( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_flags_ra( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_ira( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_ira_ra( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_ra_ira( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_ra_pc( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_ra_rb_imm16u( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_ra_rb_imm16s( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_ra_rb_rc_imm12s( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_ra_rb_rc( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}
bool assembler::test_instr_ra_rb_abs( const instruction& iter,
	std::vector<real_iarg>& iarg_vec )
{
	
	return false;
}


s32 assembler::unary( bool use_special, bool keep_lineno )
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
			return -unary( use_special, keep_lineno );
		
		case '(':
			lex(keep_lineno);
			v = expr( use_special, keep_lineno );
			
			if (!lex.match( ')', keep_lineno ))
			{
				we.warn1("Missing ')' assumed");
			}
			break;
		
		default:
			we.error("Ill-formed expression");
			break;
	}
	
	return v;
}

s32 assembler::expr( bool use_special, bool keep_lineno )
{
	s32 v = unary( use_special, keep_lineno );
	
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
				v += unary( use_special, keep_lineno );
				break;
			case '-':
				lex(keep_lineno);
				v -= unary( use_special, keep_lineno );
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

s32 assembler::reg( bool keep_lineno )
{
	//expr( true, keep_lineno );
	lex(keep_lineno);
	
	if ( ( lex.special_nextsym() != nullptr )
		&& ( lex.special_nextsym()->typ() 
		== static_cast<tok>(tok_defn::reg) ) )
	{
		return lex.special_nextsym()->val();
	}
	
	we.expected("register");
	return -1;
}

s32 assembler::braoffs( bool keep_lineno )
{
	const s32 temp_0 = expr( false, keep_lineno );
	const s32 temp_1 = mask_immed( temp_0, ( ( 1 << 16 ) - 1 ) );
	
	if ( temp_1 != temp_0 )
	{
		we.error("Branch offset out of range.");
	}
	
	return temp_1;
}
s32 assembler::immed16( bool keep_lineno )
{
	const s32 temp_0 = expr( false, keep_lineno );
	const s32 temp_1 = mask_immed( temp_0, ( ( 1 << 16 ) - 1 ) );
	
	if ( temp_1 != temp_0 )
	{
		we.warn("Immediate value (16-bit) out of range, has been masked.");
	}
	
	return temp_1;
}
s32 assembler::immed12( bool keep_lineno )
{
	const s32 temp_0 = expr( false, keep_lineno );
	const s32 temp_1 = mask_immed( temp_0, ( ( 1 << 12 ) - 1 ) );
	
	if ( temp_1 != temp_0 )
	{
		we.warn("Immediate value (12-bit) out of range, has been masked.");
	}
	
	return temp_1;
}


s32 assembler::line()
{
	
	
}


}
