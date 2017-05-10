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
	lex();
	
	const long orig_pos = std::ftell(infile);
	const symbol* instr_sym = lex.special_nextsym();
	
	if ( ( lex.special_nextsym() == nullptr )
		|| ( instr_sym->typ() != static_cast<tok>(tok_defn::instr) ) )
	{
		we.expected("instruction");
	}
	
	const std::vector<instruction>& instr_vec = instr_tbl.at(instr_sym);
	
	iarg_vec.clear();
	
	// Go to the end of the line
	while ( ( lex.nextc() != '\n' ) && ( lex.nextc() != EOF )
		&& ( lex.nextt() != '\n' ) )
	{
		//lex();
		
		if ( ( lex.nextc() != '\n' ) && ( lex.nextc() != EOF )
			&& ( lex.nextt() != '\n' ) )
		{
			////real_iarg to_push = { lex.nextt(), lex.nextval(),
			////	lex.nextsym(), lex.special_nextt(), lex.special_nextval(),
			////	lex.special_nextsym() };
			////iarg_vec.push_back(to_push);
			//real_iarg to_push = { lex.nextt(), lex.nextval(),
			//	lex.nextsym() };
		}
	}
	
	for ( size_t i=0; i<instr_vec.size(); ++i )
	{
		const instruction& iter = instr_vec.at(i);
		if ( instr_compat_with_iargs( iter, iarg_vec ) )
		{
			return &iter;
			break;
		}
	}
	
	
	return nullptr;
}
bool assembler::instr_compat_with_iargs( const instruction& some_instr,
	const std::vector<assembler::real_iarg>& iarg_vec )
{
	//switch ( some_instr.iargs() )
	//{
	//	case instr_args::noargs:
	//	{
	//		if ( iarg_vec.size() == 0 )
	//		{
	//			return true;
	//		}
	//	}
	//	break;
	//	
	//	case instr_args::ra:
	//	{
	//		if ( iarg_vec.size() == 1 )
	//		{
	//			return ( iarg_vec.front().comp_nextt(tok_defn::reg) );
	//		}
	//	}
	//	break;
	//	
	//	case instr_args::ra_rb:
	//	{
	//		if ( iarg_vec.size() == 2 )
	//		{
	//			return ( iarg_vec.front().comp_nextt(tok_defn::reg) 
	//				&& iarg_vec.back().comp_nextt(tok_defn::reg) );
	//		}
	//	}
	//	break;
	//	
	//	case instr_args::ra_imm16u:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::imm16u:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::imm16s:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::branchoffset:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::flags:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::ra_flags:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::flags_ra:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::ira:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::ira_ra:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::ra_ira:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::ra_pc:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::ra_rb_imm16u:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::ra_rb_imm16s:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::ra_rb_rc_imm12s:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::ra_rb_rc:
	//	{
	//		
	//	}
	//	break;
	//	
	//	case instr_args::ra_rb_abs:
	//	{
	//		
	//	}
	//	break;
	//	
	//	
	//	default:
	//	{
	//		we.unknown("instr_args!");
	//	}
	//	break;
	//}
	
	
	return false;
}

s32 assembler::unary( bool use_special, bool keep_lineno )
{
	s32 v;
	
	decltype(lex.nextt()) some_nextt;
	decltype(lex.nextval()) some_nextval;
	
	if (!use_special)
	{
		some_nextt = lex.nextt();
		some_nextval = lex.nextval();
	}
	else
	{
		some_nextt = lex.special_nextt();
		some_nextval = lex.special_nextval();
	}
	
	switch (some_nextt)
	{
		case static_cast<tok>(tok_defn::ident):
		case static_cast<tok>(tok_defn::number):
			v = some_nextval;
			lex(keep_lineno);
			break;
		
		case '-':
			lex(keep_lineno);
			return -unary( use_special, keep_lineno );
		
		case '(':
			lex(keep_lineno);
			v = expr( use_special, keep_lineno );
			
			if (!lex.match(')'))
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
	
	decltype(lex.nextt()) some_nextt;
	decltype(lex.nextval()) some_nextval;
	
	if (!use_special)
	{
		some_nextt = lex.nextt();
		some_nextval = lex.nextval();
	}
	else
	{
		some_nextt = lex.special_nextt();
		some_nextval = lex.special_nextval();
	}
	
	while ( ( some_nextt == '+' ) || ( some_nextt == '-' ) )
	{
		switch (some_nextt)
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

//s32 assembler::reg( bool use_special, bool keep_lineno )
//{
//	decltype(lex.nextsym()) some_nextsym;
//	
//	if ( lex.nextsym()->typ() == static_cast<tok>(tok_defn::reg) )
//	{
//		return lex.nextsym()->val();
//	}
//	
//	we.expected("register");
//	return -1;
//}

s32 assembler::braoffs( bool use_special, bool keep_lineno )
{
	const s32 temp_0 = expr( use_special, keep_lineno );
	const s32 temp_1 = mask_immed( temp_0, ( ( 1 << 16 ) - 1 ) );
	
	if ( temp_1 != temp_0 )
	{
		we.error("Branch offset out of range.");
	}
	
	return temp_1;
}
s32 assembler::immed16( bool use_special, bool keep_lineno )
{
	const s32 temp_0 = expr( use_special, keep_lineno );
	const s32 temp_1 = mask_immed( temp_0, ( ( 1 << 16 ) - 1 ) );
	
	if ( temp_1 != temp_0 )
	{
		we.warn("Immediate value (16-bit) out of range, has been masked.");
	}
	
	return temp_1;
}
s32 assembler::immed12( bool use_special, bool keep_lineno )
{
	const s32 temp_0 = expr( use_special, keep_lineno );
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
