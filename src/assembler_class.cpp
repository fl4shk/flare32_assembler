#include "assembler_class.hpp"

namespace navichip32
{


assembler::assembler( int argc, char** argv, std::FILE* s_infile )
	: infile(s_infile), lex( s_infile, &we, &internal_pass, &sym_tbl ),
	we(&lex)
{
	internal_args_vec.clear();
	
	for ( int i=0; i<argc; ++i )
	{
		internal_args_vec.push_back(string_view(argv[i]));
	}
	
	// General purpose registers
	sym_tbl.enter( "r0", static_cast<tok>(tok_defn::reg), 0 );
	sym_tbl.enter( "r1", static_cast<tok>(tok_defn::reg), 1 );
	sym_tbl.enter( "r2", static_cast<tok>(tok_defn::reg), 2 );
	sym_tbl.enter( "r3", static_cast<tok>(tok_defn::reg), 3 );
	sym_tbl.enter( "r4", static_cast<tok>(tok_defn::reg), 4 );
	sym_tbl.enter( "r5", static_cast<tok>(tok_defn::reg), 5 );
	sym_tbl.enter( "r6", static_cast<tok>(tok_defn::reg), 6 );
	sym_tbl.enter( "r7", static_cast<tok>(tok_defn::reg), 7 );
	sym_tbl.enter( "r8", static_cast<tok>(tok_defn::reg), 8 );
	sym_tbl.enter( "r9", static_cast<tok>(tok_defn::reg), 9 );
	sym_tbl.enter( "r10", static_cast<tok>(tok_defn::reg), 10 );
	sym_tbl.enter( "r11", static_cast<tok>(tok_defn::reg), 11 );
	sym_tbl.enter( "r12", static_cast<tok>(tok_defn::reg), 12 );
	sym_tbl.enter( "r13", static_cast<tok>(tok_defn::reg), 13 );
	sym_tbl.enter( "r14", static_cast<tok>(tok_defn::reg), 14 );
	sym_tbl.enter( "r15", static_cast<tok>(tok_defn::reg), 15 );
	sym_tbl.enter( "lr", static_cast<tok>(tok_defn::reg), 14 );
	sym_tbl.enter( "sp", static_cast<tok>(tok_defn::reg), 15 );
	
	// Special purpose registers
	sym_tbl.enter( "flags", static_cast<tok>(tok_defn::reg_flags), 0 );
	sym_tbl.enter( "ira", static_cast<tok>(tok_defn::reg_ira), 0 );
	sym_tbl.enter( "pc", static_cast<tok>(tok_defn::reg_pc), 0 );
	
	
	enter_grp_0_instructions();
	enter_grp_1_instructions();
	enter_grp_2_instructions();
	enter_grp_3_instructions();
	
}

assembler::~assembler()
{
}

int assembler::run()
{
	
	return 0;
}

// Constructor stuff
void assembler::enter_grp_0_instructions()
{
}
void assembler::enter_grp_1_instructions()
{
}
void assembler::enter_grp_2_instructions()
{
}
void assembler::enter_grp_3_instructions()
{
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
const instruction& assembler::determine_instr()
{
	
}

s32 assembler::unary()
{
	s32 v;
	
	switch (lex.nextt())
	{
		case static_cast<tok>(tok_defn::ident):
		case static_cast<tok>(tok_defn::number):
			v = lex.nextval();
			lex();
			break;
		
		case '-':
			lex();
			return -unary();
		
		case '(':
			lex();
			v = expr();
			
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

s32 assembler::expr()
{
	s32 v = unary();
	
	while ( ( lex.nextt() == '+' ) || ( lex.nextt() == '-' ) )
	{
		switch (lex.nextt())
		{
			case '+':
				lex();
				v += unary();
				break;
			case '-':
				lex();
				v -= unary();
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

s32 assembler::reg()
{
	if ( lex.nextsym()->typ() == static_cast<tok>(tok_defn::reg) )
	{
		return lex.nextsym()->val();
	}
	
	we.expected("register");
	return -1;
}

s32 assembler::braoffs()
{
	const s32 temp_0 = expr();
	const s32 temp_1 = mask_immed( temp_0, ( ( 1 << 16 ) - 1 ) );
	
	if ( temp_1 != temp_0 )
	{
		we.error("Branch offset out of range.");
	}
	
	return temp_1;
}
s32 assembler::immed16()
{
	const s32 temp_0 = expr();
	const s32 temp_1 = mask_immed( temp_0, ( ( 1 << 16 ) - 1 ) );
	
	if ( temp_1 != temp_0 )
	{
		we.warn("Immediate value (16-bit) out of range, has been masked.");
	}
	
	return temp_1;
}
s32 assembler::immed12()
{
	const s32 temp_0 = expr();
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
