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
	special_sym_tbl.enter( "r0", cast_typ(tok_defn::reg), 0, true );
	special_sym_tbl.enter( "r1", cast_typ(tok_defn::reg), 1, true );
	special_sym_tbl.enter( "r2", cast_typ(tok_defn::reg), 2, true );
	special_sym_tbl.enter( "r3", cast_typ(tok_defn::reg), 3, true );
	special_sym_tbl.enter( "r4", cast_typ(tok_defn::reg), 4, true );
	special_sym_tbl.enter( "r5", cast_typ(tok_defn::reg), 5, true );
	special_sym_tbl.enter( "r6", cast_typ(tok_defn::reg), 6, true );
	special_sym_tbl.enter( "r7", cast_typ(tok_defn::reg), 7, true );
	special_sym_tbl.enter( "r8", cast_typ(tok_defn::reg), 8, true );
	special_sym_tbl.enter( "r9", cast_typ(tok_defn::reg), 9, true );
	special_sym_tbl.enter( "r10", cast_typ(tok_defn::reg), 10, true );
	special_sym_tbl.enter( "r11", cast_typ(tok_defn::reg), 11, true );
	special_sym_tbl.enter( "r12", cast_typ(tok_defn::reg), 12, true );
	special_sym_tbl.enter( "r13", cast_typ(tok_defn::reg), 13, true );
	special_sym_tbl.enter( "r14", cast_typ(tok_defn::reg), 14, true );
	special_sym_tbl.enter( "r15", cast_typ(tok_defn::reg), 15, true );
	special_sym_tbl.enter( "lr", cast_typ(tok_defn::reg), 14, true );
	special_sym_tbl.enter( "sp", cast_typ(tok_defn::reg), 15, true );
	
	// Special purpose registers
	special_sym_tbl.enter( "flags", cast_typ(tok_defn::reg_flags), 0, 
		true );
	special_sym_tbl.enter( "ira", cast_typ(tok_defn::reg_ira), 0, true );
	special_sym_tbl.enter( "pc", cast_typ(tok_defn::reg_pc), 0, true );
	
	
	insert_grp_0_instructions();
	insert_grp_1_instructions();
	insert_grp_2_instructions();
	insert_grp_3_instructions();
	
}

assembler::~assembler()
{
}

int assembler::run()
{
	set_pass(0);
	do
	{
		set_changed(false);
		
		set_pass( pass() + 1 );
		if ( pass() > 100 )
		{
			we.error("Cannot resolve references");
		}
		
		
		set_lc(0);
		lex.set_lineno(0);;
		std::rewind(infile);
		lex.set_nextc(' ');
		lex.set_nextt(' ');
		//lex_regular();
		
		while ( lex.nextt() != EOF )
		{
			line();
		}
		
	} while (changed());
	
	set_pass(0);
	set_changed(false);
	set_lc(0);
	lex.set_lineno(0);
	std::rewind(infile);
	lex.set_nextc(' ');
	lex.set_nextt(' ');
	//lex_regular();
	while ( lex.nextt() != EOF )
	{
		line();
	}
	
	// Success!
	return 0;
}


// Code generator stuff
void assembler::gen8( s32 v )
{
	if ( pass() == 0 )
	{
		if ( last_lc() != lc() )
		{
			printf( "@%08x\n", lc() );
		}
		printf( "%02x\n", ( static_cast<u32>(v) & 0xff ) );
		
		//const auto to_print_byte = ( static_cast<u32>(v) & 0xff );
		//
		//std::bitset<8> to_print(to_print_byte);
		//
		//printout( to_print, "\n" );
	}
	
	set_last_lc(set_lc( lc() + 1 ));
}
void assembler::gen16( s32 v )
{
	gen8( static_cast<u32>(v) >> 8 );
	gen8(static_cast<u32>(v));
}
void assembler::gen32( s32 v )
{
	gen8( static_cast<u32>(v) >> 24 );
	gen8( static_cast<u32>(v) >> 16 );
	gen8( static_cast<u32>(v) >> 8 );
	gen8(static_cast<u32>(v));
}

void assembler::gen_any_instruction( const size_t grp, 
	const bool has_dot_f, const size_t opcode, 
	const std::vector<real_iarg>& iarg_vec )
{
	u32 ra = 0, rb = 0, rc = 0, imm = 0;
	
	for ( size_t i=0; i<iarg_vec.size(); ++i )
	{
		const std::string& name = iarg_vec.at(i).name;
		const s32 nextval = iarg_vec.at(i).nextval;
		
		if ( name == "ra" )
		{
			ra = nextval;
		}
		else if ( name == "rb" )
		{
			rb = nextval;
		}
		else if ( name == "rc" )
		{
			rc = nextval;
		}
		else if ( name == "imm" )
		{
			imm = nextval;
		}
	}
	
	
	u32 temp;
	
	// Encoding stuff used by EVERY instruction
	clear_and_set_bits_with_range( temp, grp, 15, 14 );
	clear_and_set_bits_with_range( temp, ( has_dot_f ? 1 : 0 ), 13, 13 );
	clear_and_set_bits_with_range( temp, opcode, 12, 8 );
	clear_and_set_bits_with_range( temp, ra, 7, 4 );
	clear_and_set_bits_with_range( temp, rb, 3, 0 );
	
	gen16(temp);
	
	switch (grp)
	{
		// Group 0 Instructions
		// 00fo oooo aaaa bbbb
		// 
		//  f:  1 if can affect flags (and instruction type supports it), 0
		//  if flags unchanged.
		// 
		//  o:  opcode
		//  a:  rA (destination register usually)
		//  b:  rB
		case 0:
			break;
		
		
		// Group 1 Instructions
		// 01fo oooo aaaa bbbb  iiii iiii iiii iiii
		// 
		//  f:  1 if can affect flags (and instruction type supports it), 0
		//  if flags unchanged.
		// 
		//  o:  opcode
		//  a:  rA
		//  b:  rB
		//  i:  16-bit immediate value
		case 1:
			gen16(imm);
			break;
		
		
		// Group 2 Instructions
		// 10fo oooo aaaa bbbb  cccc iiii iiii iiii
		// 
		//  f:  1 if can affect flags (and instruction type supports it), 0
		//  if flags unchanged.
		//  
		//  o:  opcode
		//  a:  rA
		//  b:  rB
		//  c:  rc
		//  i:  12-bit immediate value
		case 2:
			//clear_and_set_bits_with_range( temp, rc, 
			clear_and_set_bits_with_range( temp, rc, 15, 12 );
			clear_and_set_bits_with_range( temp, imm, 11, 0 );
			gen16(temp);
			
			break;
		
		
		// Group 3 Instructions
		// 11fo oooo aaaa bbbb  iiii iiii iiii iiii  iiii iiii iiii iiii
		// 
		//  f:  1 if can affect flags (and instruction type supports it), 0
		//  if flags unchanged.
		//  
		//  o:  opcode
		//  a:  rA
		//  b:  rB
		//  i:  32-bit immediate value
		case 3:
			gen32(imm);
			break;
		
		default:
			we.error("assembler::gen_any_instruction():  Eek 2!\n");
			break;
	}
	
	
	if ( pass() == 0 )
	{
		printout("\n");
	}
}


// Parser stuff
const instruction* assembler::determine_instr()
{
	std::vector<real_iarg> iarg_vec;
	const instruction* ret = nullptr;
	
	const long orig_pos = std::ftell(infile);
	const symbol* instr_sym = lex.special_nextsym();
	
	// Keep lineno so that the function that called this one doesn't have
	// to know about what happened to the lexer.
	//lex_keep_lineno();
	
	const long reset_pos = std::ftell(infile);
	
	
	if ( ( instr_sym == nullptr )
		|| ( instr_sym->typ() != cast_typ(tok_defn::instr) ) )
	{
		//we.expected("instruction");
		return ret;
	}
	
	const std::vector<instruction>& instr_vec = instr_tbl.at(instr_sym);
	
	
	const auto temp_nextc = lex.nextc();
	
	const auto temp_nextt = lex.nextt();
	const auto temp_nextval = lex.nextval();
	const auto temp_nextsym = lex.nextsym();
	
	const auto temp_special_nextt = lex.special_nextt();
	const auto temp_special_nextval = lex.special_nextval();
	const auto temp_special_nextsym = lex.special_nextsym();
	
	auto restore_lex = [&]() -> void
	{
		lex.set_nextc(temp_nextc);
		
		lex.set_nextt(temp_nextt);
		lex.set_nextval(temp_nextval);
		lex.set_nextsym(temp_nextsym);
		
		lex.set_special_nextt(temp_special_nextt);
		lex.set_special_nextval(temp_special_nextval);
		lex.set_special_nextsym(temp_special_nextsym);
	};
	
	for ( size_t i=0; i<instr_vec.size(); ++i )
	{
		const instruction& iter = instr_vec.at(i);
		
		lex_keep_lineno();
		
		iarg_vec.clear();
		
		if ( parse_iargs( iter, true, iarg_vec ) )
		{
			//return &iter;
			ret = &iter;
			break;
		}
		
		std::fseek( infile, reset_pos, SEEK_SET );
		
		restore_lex();
	}
	restore_lex();
	
	std::fseek( infile, orig_pos, SEEK_SET );
	
	return ret;
}
bool assembler::parse_iargs( const instruction& iter, bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	switch ( iter.iargs() )
	{
		case instr_args::noargs:
			return parse_instr_noargs( just_test, iarg_vec );
		case instr_args::ra:
			return parse_instr_ra( just_test, iarg_vec );
		case instr_args::ra_rb:
			return parse_instr_ra_rb( just_test, iarg_vec );
		case instr_args::ra_imm16u:
			return parse_instr_ra_imm16u( just_test, iarg_vec );
		case instr_args::imm16u:
			return parse_instr_imm16u( just_test, iarg_vec );
		case instr_args::imm16s:
			return parse_instr_imm16s( just_test, iarg_vec );
		case instr_args::branchoffset:
			return parse_instr_branchoffset( just_test, iarg_vec );
		case instr_args::flags:
			return parse_instr_flags( just_test, iarg_vec );
		case instr_args::ra_flags:
			return parse_instr_ra_flags( just_test, iarg_vec );
		case instr_args::flags_ra:
			return parse_instr_flags_ra( just_test, iarg_vec );
		case instr_args::ira:
			return parse_instr_ira( just_test, iarg_vec );
		case instr_args::ira_ra:
			return parse_instr_ira_ra( just_test, iarg_vec );
		case instr_args::ra_ira:
			return parse_instr_ra_ira( just_test, iarg_vec );
		case instr_args::ra_pc:
			return parse_instr_ra_pc( just_test, iarg_vec );
		case instr_args::ra_rb_imm16u:
			return parse_instr_ra_rb_imm16u( just_test, iarg_vec );
		case instr_args::ra_rb_imm16s:
			return parse_instr_ra_rb_imm16s( just_test, iarg_vec );
		case instr_args::ra_rb_rc_imm12s:
			return parse_instr_ra_rb_rc_imm12s( just_test, iarg_vec );
		case instr_args::ra_rb_rc:
			return parse_instr_ra_rb_rc( just_test, iarg_vec );
		case instr_args::ra_rb_abs:
			return parse_instr_ra_rb_abs( just_test, iarg_vec );
		
		
		
		case instr_args::pseudo_r0hidden_rb:
			return parse_instr_pseudo_r0hidden_rb
				( just_test, iarg_vec );
		case instr_args::pseudo_r0hidden_rb_imm16u:
			return parse_instr_pseudo_r0hidden_rb_imm16u
				( just_test, iarg_vec );
		
		// cpn rA, rB
		case instr_args::pseudo_ra_rb_imm0hidden:
			return parse_instr_pseudo_ra_rb_imm0hidden
				( just_test, iarg_vec );
		
		// cpc rA, rB
		case instr_args::pseudo_ra_rb_imm16sneg1hidden:
			return parse_instr_pseudo_ra_rb_imm16sneg1hidden
				( just_test, iarg_vec );
		
		case instr_args::pseudo_ra_rb_r0hidden_imm0hidden:
			return parse_instr_pseudo_ra_rb_r0hidden_imm0hidden
				( just_test, iarg_vec );
		case instr_args::pseudo_ra_rb_rc_imm0hidden:
			return parse_instr_pseudo_ra_rb_rc_imm0hidden
				( just_test, iarg_vec );
		case instr_args::pseudo_ra_rb_r0hidden_imm12s:
			return parse_instr_pseudo_ra_rb_r0hidden_imm12s
				( just_test, iarg_vec );
		case instr_args::pseudo_r0hidden_rb_rc:
			return parse_instr_pseudo_r0hidden_rb_rc
				( just_test, iarg_vec );
		
		
		case instr_args::pseudo_ra_rahidden_rc:
			return parse_instr_pseudo_ra_rahidden_rc
				( just_test, iarg_vec );
		
		// cpy pc, rB
		case instr_args::pseudo_pc_rb:
			return parse_instr_pseudo_pc_rb
				( just_test, iarg_vec );
		
		case instr_args::pseudo_ra_sphidden:
			return parse_instr_pseudo_ra_sphidden
				( just_test, iarg_vec );
		
		
		case instr_args::pseudo_ra_r0hidden_abs:
			return parse_instr_pseudo_ra_r0hidden_abs
				( just_test, iarg_vec );
		case instr_args::pseudo_r0hidden_r0hidden_abs:
			return parse_instr_pseudo_r0hidden_r0hidden_abs
				( just_test, iarg_vec );
		case instr_args::pseudo_ra_rahidden_abs:
			return parse_instr_pseudo_ra_rahidden_abs
				( just_test, iarg_vec );
		default:
			we.unknown("instr_args!");
			break;
	}
	
	
	return false;
}

bool assembler::parse_iarg_reg( bool just_test, 
	std::vector<real_iarg>& iarg_vec, const std::string& name )
{
	bool did_fail;
	iarg_reg( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( lex, true ));
		iarg_vec.back().name = name;
	}
	
	return !did_fail;
}
bool assembler::parse_iarg_reg_flags( bool just_test, 
	std::vector<real_iarg>& iarg_vec, const std::string& name )
{
	bool did_fail;
	iarg_reg_flags( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( lex, true ));
		iarg_vec.back().name = name;
	}
	
	return !did_fail;
}
bool assembler::parse_iarg_reg_ira( bool just_test, 
	std::vector<real_iarg>& iarg_vec, const std::string& name )
{
	bool did_fail;
	iarg_reg_ira( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( lex, true ));
		iarg_vec.back().name = name;
	}
	
	return !did_fail;
}
bool assembler::parse_iarg_reg_pc( bool just_test, 
	std::vector<real_iarg>& iarg_vec, const std::string& name )
{
	bool did_fail;
	iarg_reg_pc( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( lex, true ));
		iarg_vec.back().name = name;
	}
	
	return !did_fail;
}
bool assembler::parse_iarg_braoffs( bool just_test, 
	std::vector<real_iarg>& iarg_vec, const std::string& name )
{
	bool did_fail;
	const s32 imm = iarg_braoffs( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( cast_typ(tok_defn::number),
			imm ));
		iarg_vec.back().name = name;
	}
	
	return !did_fail;
}
bool assembler::parse_iarg_immed16( bool just_test, 
	std::vector<real_iarg>& iarg_vec, const std::string& name )
{
	bool did_fail;
	const s32 imm = iarg_immed16( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( cast_typ(tok_defn::number),
			imm ));
		iarg_vec.back().name = name;
	}
	
	return !did_fail;
}
bool assembler::parse_iarg_immed12( bool just_test, 
	std::vector<real_iarg>& iarg_vec, const std::string& name )
{
	bool did_fail;
	const s32 imm = iarg_immed12( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( cast_typ(tok_defn::number),
			imm ));
		iarg_vec.back().name = name;
	}
	
	return !did_fail;
}
bool assembler::parse_iarg_abs( bool just_test, 
	std::vector<real_iarg>& iarg_vec, const std::string& name )
{
	bool did_fail;
	const s32 imm = iarg_abs( just_test, &did_fail );
	
	if ( !just_test && !did_fail )
	{
		iarg_vec.push_back(real_iarg( cast_typ(tok_defn::number),
			imm ));
		iarg_vec.back().name = name;
	}
	
	return !did_fail;
}


bool assembler::parse_instr_noargs( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	return lex.match( '\n', just_test );
}

#ifdef IARG_X
#error "Can't re-define IARG_X"
#endif

#define IARG_X( suffix, str ) \
	if (!parse_iarg_##suffix( just_test, iarg_vec, str )) \
	{ \
		return false; \
	}

#ifdef IARG_HIDDEN
#error "Can't re-define IARG_HIDDEN"
#endif

#define IARG_HIDDEN( nextt, nextval, str ) \
	iarg_vec.push_back(real_iarg( cast_typ(nextt), nextval )); \
	iarg_vec.back().name = str; \

#ifdef IARG_SAME
#error "Can't re-define IARG_SAME"
#endif

#define IARG_SAME( old_name, str ) \
	for ( size_t i=0; i<iarg_vec.size(); ++i ) \
	{ \
		if ( iarg_vec.at(i).name == old_name ) \
		{ \
			iarg_vec.push_back(iarg_vec.at(i)); \
			iarg_vec.back().name = str; \
		} \
	}

#ifdef IARG_ASSUME_COMMA
#error "Can't re-define assume_comma"
#endif

#define IARG_ASSUME_COMMA \
	/* lex(just_test); */ \
	if ( !lex.match( ',', just_test ) ) \
	{ \
		return false; \
	}

bool assembler::parse_instr_ra( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_ra_rb( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// rB
	IARG_X( reg, "rb" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_ra_imm16u( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// imm16u
	IARG_X( immed16, "imm" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_imm16u( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// imm16u
	IARG_X( immed16, "imm" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_imm16s( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// imm16s
	IARG_X( immed16, "imm" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_branchoffset( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// braoffs
	IARG_X( braoffs, "imm" )
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_flags( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// flags, a special-purpose register
	IARG_X( reg_flags, "" )
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_ra_flags( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// flags, a special-purpose register
	IARG_X( reg_flags, "" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_flags_ra( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// flags, a special-purpose register
	IARG_X( reg_flags, "" );
	
	IARG_ASSUME_COMMA
	
	// rA
	IARG_X( reg, "ra" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_ira( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// ira, a special-purpose register
	IARG_X( reg_ira, "" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_ira_ra( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// ira, a special-purpose register
	IARG_X( reg_ira, "" );
	
	IARG_ASSUME_COMMA
	
	// rA
	IARG_X( reg, "ra" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_ra_ira( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// ira, a special-purpose register
	IARG_X( reg_ira, "" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_ra_pc( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// pc, a special-purpose register
	IARG_X( reg_pc, "" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_ra_rb_imm16u( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// rB
	IARG_X( reg, "rb" )
	
	IARG_ASSUME_COMMA
	
	// imm16u
	IARG_X( immed16, "imm" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_ra_rb_imm16s( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// rB
	IARG_X( reg, "rb" );
	
	IARG_ASSUME_COMMA
	
	// imm16s
	IARG_X( immed16, "imm" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_ra_rb_rc_imm12s( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// rB
	IARG_X( reg, "rb" );
	
	IARG_ASSUME_COMMA
	
	// rC
	IARG_X( reg, "rc" );
	
	IARG_ASSUME_COMMA
	
	// imm12s
	IARG_X( immed12, "imm" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_ra_rb_rc( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// rB
	IARG_X( reg, "rb" );
	
	IARG_ASSUME_COMMA
	
	// rC
	IARG_X( reg, "rc" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_ra_rb_abs( bool just_test, 
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// rB
	IARG_X( reg, "rb" );
	
	IARG_ASSUME_COMMA
	
	// 32-bit absolute
	IARG_X( abs, "imm" );
	
	return lex_match_end_of_line(just_test);
}


// Pseudo instruction argument parsing
bool assembler::parse_instr_pseudo_r0hidden_rb( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	// r0hidden
	
	// rB
	IARG_X( reg, "rb" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_pseudo_r0hidden_rb_imm16u( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	// r0hidden
	
	// rB
	IARG_X( reg, "rb" );
	
	IARG_ASSUME_COMMA
	
	// imm16u
	IARG_X( immed16, "imm" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_pseudo_ra_rb_imm0hidden( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	IARG_X( reg, "rb" );
	
	// imm0hidden
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_pseudo_ra_rb_imm16sneg1hidden( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// rB
	IARG_X( reg, "rb" );
	
	// imm16sneg1hidden
	IARG_HIDDEN( tok_defn::number, -1, "imm" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_pseudo_ra_rb_r0hidden_imm0hidden
	( bool just_test, std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// rB
	IARG_X( reg, "rb" );
	
	// r0hidden
	
	// imm0hidden
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_pseudo_ra_rb_rc_imm0hidden( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// rB
	IARG_X( reg, "rb" );
	
	IARG_ASSUME_COMMA
	
	// rC
	IARG_X( reg, "rc" );
	
	// imm0hidden
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_pseudo_ra_rb_r0hidden_imm12s( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// rB
	IARG_X( reg, "rb" );
	
	IARG_ASSUME_COMMA
	
	// r0hidden
	
	
	// imm12s
	IARG_X( immed12, "imm" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_pseudo_r0hidden_rb_rc( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	// r0hidden
	
	// rB
	IARG_X( reg, "rb" );
	
	IARG_ASSUME_COMMA
	
	// rC
	IARG_X( reg, "rc" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_pseudo_ra_rahidden_rc( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_SAME( "ra", "rb" );
	
	IARG_ASSUME_COMMA
	
	// rC
	IARG_X( reg, "rc" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_pseudo_pc_rb( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	// pc, a special-purpose register
	IARG_X( reg_pc, "" );
	
	IARG_ASSUME_COMMA
	
	// rB
	IARG_X( reg, "rb" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_pseudo_ra_sphidden( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	
	// sphidden
	{
		symbol* temp;
		if (!special_sym_tbl.find( temp, "sp" ))
		{
			we.error( "assembler::parse_instr_pseudo_ra_sphidden():  ",
				"Eek!\n" );
		}
		IARG_HIDDEN( temp->typ(), temp->val(), "sp" );
	}
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_pseudo_ra_r0hidden_abs( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_ASSUME_COMMA
	
	// r0hidden
	
	// 32-bit absolute
	IARG_X( abs, "imm" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_pseudo_r0hidden_r0hidden_abs( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	// r0hidden
	// r0hidden
	
	// 32-bit absolute
	IARG_X( abs, "imm" );
	
	return lex_match_end_of_line(just_test);
}
bool assembler::parse_instr_pseudo_ra_rahidden_abs( bool just_test,
	std::vector<real_iarg>& iarg_vec )
{
	// rA
	IARG_X( reg, "ra" );
	
	IARG_SAME( "ra", "rb" );
	
	IARG_ASSUME_COMMA
	
	// 32-bit absolute
	IARG_X( abs, "imm" );
	
	return lex_match_end_of_line(just_test);
}


#undef IARG_X
#undef IARG_HIDDEN
#undef IARG_SAME
#undef IARG_ASSUME_COMMA


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
	//const bool old_did_init = did_init;
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
		&& ( lex.special_nextsym()->typ() == cast_typ(typ) ) )
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
	// I'm not sure this is correct!
	//const s32 temp_0 = expr( false, just_test, did_fail, false )
	//	- ( lc() + 4 );
	const s32 temp_0 = expr( false, just_test, did_fail, false )
		- lc();
	
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


void assembler::line()
{
	// Process labels
	bool found_label = false;
	
	if ( isspace(lex.nextt()) )
	{
		lex_regular();
		return;
	}
	
	//auto find_non_ws = [ this ]( bool just_test ) -> void
	//{
	//	while ( isspace(lex.nextt()) )
	//	{
	//		lex(just_test);
	//	}
	//};
	
	
	if ( lex.nextt() == cast_typ(tok_defn::ident) )
	{
		symbol* sym = lex.nextsym();
		
		
		const auto temp_nextc = lex.nextc();
		
		const auto temp_nextt = lex.nextt();
		const auto temp_nextval = lex.nextval();
		const auto temp_nextsym = lex.nextsym();
		
		const auto temp_special_nextt = lex.special_nextt();
		const auto temp_special_nextval = lex.special_nextval();
		const auto temp_special_nextsym = lex.special_nextsym();
		
		
		//printout( "good:  ", lex.nextc(), " ", lex.nextt(), " ",
		//	( lex.nextsym() ? lex.nextsym()->name() : "" ), "\n" );
		
		{
			const long orig_pos = std::ftell(infile);
			lex_keep_lineno();
			std::fseek( infile, orig_pos, SEEK_SET );
		}
		//printout( "asdf:  ", lex.nextc(), " ", lex.nextt(), " ",
		//	( lex.nextsym() ? lex.nextsym()->name() : "" ), "\n" );
		
		
		if ( lex.nextt() == ':' )
		{
			//printout("AAAAA\n");
			lex_regular();
			//printout( lex.nextt(), "\n" );
			lex_regular();
			
			if ( sym->val() != lc() )
			{
				set_changed(true);
				sym->set_val(lc());
			}
			
			found_label = true;
		}
		else
		{
			lex.set_nextc(temp_nextc);
			
			lex.set_nextt(temp_nextt);
			lex.set_nextval(temp_nextval);
			lex.set_nextsym(temp_nextsym);
			
			lex.set_special_nextt(temp_special_nextt);
			lex.set_special_nextval(temp_special_nextval);
			lex.set_special_nextsym(temp_special_nextsym);
		}
		
	}
	
	//printout( "gggg:  ", found_label, " ", lex.nextc(), " ", 
	//	lex.nextt(), " ", ( lex.nextsym() ? lex.nextsym()->name() : "" ), 
	//	"\n" );
	
	const instruction* some_instr = determine_instr();
	
	if ( !found_label && ( some_instr == nullptr ) )
	{
		we.expected("instruction or identifier");
	}
	
	if (found_label)
	{
		
	}
	
	
	if ( some_instr != nullptr )
	{
		std::vector<real_iarg> iarg_vec;
		
		lex_regular();
		if (!parse_iargs( *some_instr, false, iarg_vec ))
		{
			we.error("assembler::line():  Eek!\n");
		}
		
		if ( some_instr->real_instr() != nullptr )
		{
			some_instr = some_instr->real_instr();
		}
		
		gen_any_instruction( some_instr->grp(), 
			some_instr->sym()->has_dot_f(), some_instr->opcode(),
			iarg_vec );
	}
	
	//while ( !lex.match( '\n', false ) )
	//{
	//	lex_regular();
	//}
}


}
