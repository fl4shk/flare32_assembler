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
	( std::vector<real_iarg>& iarg_vec )
{
	const instruction* ret = nullptr;
	
	const long orig_pos = std::ftell(infile);
	
	//// Keep lineno so that the function that called this one doesn't have
	//// to know about what happened to the lexer.
	//lex_keep_lineno();
	
	const long reset_pos = std::ftell(infile);
	
	const symbol* instr_sym = lex.special_nextsym();
	
	if ( ( lex.special_nextsym() == nullptr )
		|| ( instr_sym->typ() != static_cast<tok>(tok_defn::instr) ) )
	{
		//we.expected("instruction");
		return ret;
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
		
		//lex_keep_lineno();
		
		iarg_vec.clear();
		
		if ( handle_iargs( iter, true, iarg_vec ) )
		{
			//return &iter;
			ret = &iter;
			break;
		}
		
		std::fseek( infile, reset_pos, SEEK_SET );
	}
	
	std::fseek( infile, orig_pos, SEEK_SET );
	
	return ret;
}
bool assembler::handle_iargs( const instruction& iter, bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	switch ( iter.iargs() )
	{
		case instr_args::noargs:
			return handle_instr_noargs( just_test, iarg_vec );
		case instr_args::ra:
			return handle_instr_ra( just_test, iarg_vec );
		case instr_args::ra_rb:
			return handle_instr_ra_rb( just_test, iarg_vec );
		case instr_args::ra_imm16u:
			return handle_instr_ra_imm16u( just_test, iarg_vec );
		case instr_args::imm16u:
			return handle_instr_imm16u( just_test, iarg_vec );
		case instr_args::imm16s:
			return handle_instr_imm16s( just_test, iarg_vec );
		case instr_args::branchoffset:
			return handle_instr_branchoffset( just_test, iarg_vec );
		case instr_args::flags:
			return handle_instr_flags( just_test, iarg_vec );
		case instr_args::ra_flags:
			return handle_instr_ra_flags( just_test, iarg_vec );
		case instr_args::flags_ra:
			return handle_instr_flags_ra( just_test, iarg_vec );
		case instr_args::ira:
			return handle_instr_ira( just_test, iarg_vec );
		case instr_args::ira_ra:
			return handle_instr_ira_ra( just_test, iarg_vec );
		case instr_args::ra_ira:
			return handle_instr_ra_ira( just_test, iarg_vec );
		case instr_args::ra_pc:
			return handle_instr_ra_pc( just_test, iarg_vec );
		case instr_args::ra_rb_imm16u:
			return handle_instr_ra_rb_imm16u( just_test, iarg_vec );
		case instr_args::ra_rb_imm16s:
			return handle_instr_ra_rb_imm16s( just_test, iarg_vec );
		case instr_args::ra_rb_rc_imm12s:
			return handle_instr_ra_rb_rc_imm12s( just_test, iarg_vec );
		case instr_args::ra_rb_rc:
			return handle_instr_ra_rb_rc( just_test, iarg_vec );
		case instr_args::ra_rb_abs:
			return handle_instr_ra_rb_abs( just_test, iarg_vec );
		
		default:
			we.unknown("instr_args!");
			break;
	}
	
	
	return false;
}

bool assembler::handle_iarg_reg( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	bool did_fail;
	iarg_reg( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( lex, true ));
	}
	
	return !did_fail;
}
bool assembler::handle_iarg_reg_flags( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	bool did_fail;
	iarg_reg_flags( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( lex, true ));
	}
	
	return !did_fail;
}
bool assembler::handle_iarg_reg_ira( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	bool did_fail;
	iarg_reg_ira( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( lex, true ));
	}
	
	return !did_fail;
}
bool assembler::handle_iarg_reg_pc( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	bool did_fail;
	iarg_reg_pc( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( lex, true ));
	}
	
	return !did_fail;
}
bool assembler::handle_iarg_braoffs( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	bool did_fail;
	const s32 imm = iarg_braoffs( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( static_cast<tok>(tok_defn::number),
			imm ));
	}
	
	return !did_fail;
}
bool assembler::handle_iarg_immed16( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	bool did_fail;
	const s32 imm = iarg_immed16( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( static_cast<tok>(tok_defn::number),
			imm ));
	}
	
	return !did_fail;
}
bool assembler::handle_iarg_immed12( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	bool did_fail;
	const s32 imm = iarg_immed12( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( static_cast<tok>(tok_defn::number),
			imm ));
	}
	
	return !did_fail;
}
bool assembler::handle_iarg_abs( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	bool did_fail;
	const s32 imm = iarg_abs( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( static_cast<tok>(tok_defn::number),
			imm ));
	}
	
	return !did_fail;
}


bool assembler::handle_instr_noargs( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_ra( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	if (!handle_iarg_reg( just_test, iarg_vec ) )
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_ra_rb( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	
	// rA
	if ( !handle_iarg_reg( just_test, iarg_vec )
		
		// rB
		|| !handle_iarg_reg( just_test, iarg_vec ) )
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_ra_imm16u( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	if ( !handle_iarg_reg( just_test, iarg_vec )
		
		// imm16u
		|| !handle_iarg_immed16( just_test, iarg_vec ) )
	{
		return false;
	}
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_imm16u( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// imm16u
	if (!handle_iarg_immed16( just_test, iarg_vec ))
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_imm16s( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// imm16s
	if (!handle_iarg_immed16( just_test, iarg_vec ))
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_branchoffset( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// braoffs
	if (!handle_iarg_braoffs( just_test, iarg_vec ))
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_flags( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// flags, a special-purpose register
	if (!handle_iarg_reg_flags( just_test, iarg_vec ))
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_ra_flags( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	if ( !handle_iarg_reg( just_test, iarg_vec )
		
		// flags, a special-purpose register
		|| !handle_iarg_reg_flags( just_test, iarg_vec ) )
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_flags_ra( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// flags, a special-purpose register
	if ( !handle_iarg_reg_flags( just_test, iarg_vec )
		
		// rA
		|| !handle_iarg_reg( just_test, iarg_vec ) )
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_ira( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// ira, a special-purpose register
	if (!handle_iarg_reg_ira( just_test, iarg_vec ))
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_ira_ra( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// ira, a special-purpose register
	if ( !handle_iarg_reg_ira( just_test, iarg_vec )
		
		// rA
		|| !handle_iarg_reg( just_test, iarg_vec ) )
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_ra_ira( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	if ( !handle_iarg_reg( just_test, iarg_vec )
		
		// ira, a special-purpose register
		|| !handle_iarg_reg_ira( just_test, iarg_vec ) )
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_ra_pc( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	if ( !handle_iarg_reg( just_test, iarg_vec )
		
		// pc, a special-purpose register
		|| !handle_iarg_reg_pc( just_test, iarg_vec ) )
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_ra_rb_imm16u( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	if ( !handle_iarg_reg( just_test, iarg_vec )
		
		// rB
		|| !handle_iarg_reg( just_test, iarg_vec )
		
		// imm16u
		|| !handle_iarg_immed16( just_test, iarg_vec ) )
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_ra_rb_imm16s( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	if ( !handle_iarg_reg( just_test, iarg_vec )
		
		// rB
		|| !handle_iarg_reg( just_test, iarg_vec )
		
		// imm16s
		|| !handle_iarg_immed16( just_test, iarg_vec ) )
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_ra_rb_rc_imm12s( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	if ( !handle_iarg_reg( just_test, iarg_vec )
		
		// rB
		|| !handle_iarg_reg( just_test, iarg_vec )
		
		// rC
		|| !handle_iarg_reg( just_test, iarg_vec )
		
		// imm12s
		|| !handle_iarg_immed12( just_test, iarg_vec ) )
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_ra_rb_rc( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	if ( !handle_iarg_reg( just_test, iarg_vec )
		
		// rB
		|| !handle_iarg_reg( just_test, iarg_vec )
		
		// rC
		|| !handle_iarg_reg( just_test, iarg_vec ) )
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}
bool assembler::handle_instr_ra_rb_abs( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	if ( !handle_iarg_reg( just_test, iarg_vec )
		
		// rB
		|| !handle_iarg_reg( just_test, iarg_vec )
		
		// 32-bit absolute
		|| !handle_iarg_abs( just_test, iarg_vec ) )
	{
		return false;
	}
	
	return lex.match( '\n', just_test );
}


s32 assembler::unary( bool use_special, bool just_test, bool* did_fail )
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
			lex(just_test);
			break;
		
		case '-':
			lex(just_test);
			return -unary( use_special, just_test, did_fail );
		
		case '(':
			lex(just_test);
			v = expr( use_special, just_test, did_fail );
			
			//if (!lex.match( ')', just_test ))
			//if ( !lex_match_just_test(')') && !just_test )
			
			if ( !just_test && !lex.match( ')', just_test ) )
			{
				we.warn1("Missing ')' assumed");
			}
			break;
		
		default:
			set_did_fail( did_fail, true );
			if (!just_test)
			{
				we.error("Ill-formed expression");
			}
			break;
	}
	
	return v;
}

s32 assembler::expr( bool use_special, bool just_test, bool* did_fail,
	bool did_init )
{
	if (!did_init)
	{
		set_did_fail( did_fail, false );
	}
	
	s32 v = unary( use_special, just_test, did_fail );
	
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
				lex(just_test);
				v += unary( use_special, just_test, did_fail );
				break;
			case '-':
				lex(just_test);
				v -= unary( use_special, just_test, did_fail );
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
	const string_view& fail_msg, bool just_test, bool* did_fail )
{
	//expr( true, just_test );
	lex(just_test);
	
	set_did_fail( did_fail, false );
	
	if ( ( lex.special_nextsym() != nullptr )
		&& ( lex.special_nextsym()->typ() == static_cast<tok>(typ) ) )
	{
		return lex.special_nextsym()->val();
	}
	
	if (!just_test)
	{
		we.expected(fail_msg);
	}
	set_did_fail( did_fail, true );
	return -1;
}


s32 assembler::iarg_braoffs( bool just_test, bool* did_fail )
{
	const s32 temp_0 = expr( false, just_test, did_fail, false );
	const s32 temp_1 = mask_immed( temp_0, ( ( 1 << 16 ) - 1 ) );
	
	if ( temp_1 != temp_0 )
	{
		if (!just_test)
		{
			we.error("Branch offset out of range.");
		}
	}
	
	return temp_1;
}
s32 assembler::iarg_immed16( bool just_test, bool* did_fail )
{
	const s32 temp_0 = expr( false, just_test, did_fail, false );
	const s32 temp_1 = mask_immed( temp_0, ( ( 1 << 16 ) - 1 ) );
	
	if ( temp_1 != temp_0 )
	{
		if (!just_test)
		{
			we.warn( "Immediate value (16-bit) out of range, has been ",
				"masked." );
		}
	}
	
	return temp_1;
}
s32 assembler::iarg_immed12( bool just_test, bool* did_fail )
{
	const s32 temp_0 = expr( false, just_test, did_fail, false );
	const s32 temp_1 = mask_immed( temp_0, ( ( 1 << 12 ) - 1 ) );
	
	if ( temp_1 != temp_0 )
	{
		if (!just_test)
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
