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
	
	return 0;
}

// Constructor stuff
void assembler::insert_grp_0_instructions()
{
	static constexpr size_t grp = 0;
	size_t opcode = 0;
	symbol* sym;
	
	//sym = sym_tbl.enter(
	
	// Instructions:
	// rA = rA + rB
	// This instruction can affect N, V, Z, and C flags.
	//add rA, rB
	sym = &sym_tbl.enter( "add", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// rA = rA + rB + carry_flag
	// Add with carry
	// This instruction can affect N, V, Z, and C flags.
	//adc rA, rB
	sym = &sym_tbl.enter( "adc", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// rA = rA - rB
	// This instruction can affect N, V, Z, and C flags.
	//sub rA, rB
	sym = &sym_tbl.enter( "sub", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// rA = rA + (~rB) + carry_flag
	// Subtract with borrow (6502 style)
	// This instruction can affect N, V, Z, and C flags.
	//sbc rA, rB
	sym = &sym_tbl.enter( "sbc", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	
	
	// rA = rB - rA
	// This instruction can affect N, V, Z, and C flags.
	//rsb rA, rB
	sym = &sym_tbl.enter( "rsb", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// rA = rA * rB
	//mul rA, rB
	sym = &sym_tbl.enter( "mul", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// rA = rA & rB
	// This instruction can affect the N and Z flags.
	//and rA, rB
	sym = &sym_tbl.enter( "and", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// rA = rA | rB
	// This instruction can affect the N and Z flags.
	//or rA, rB
	sym = &sym_tbl.enter( "or", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	
	
	// rA = rA ^ rB
	// This instruction can affect the N and Z flags.
	//xor rA, rB
	sym = &sym_tbl.enter( "xor", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// Logical shift left
	// rA = rA << rB
	//lsl rA, rB
	sym = &sym_tbl.enter( "lsl", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// Logical shift right
	//lsr rA, rB
	sym = &sym_tbl.enter( "lsr", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// Arithmetic shift right
	//asr rA, rB
	sym = &sym_tbl.enter( "asr", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	
	
	// Rotate rB left by rB bits, then store result in rA.
	//rol rA, rB
	sym = &sym_tbl.enter( "rol", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// Rotate rB right by rB bits, then store result in rA.
	//ror rA, rB
	sym = &sym_tbl.enter( "ror", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// Rotate rB left (THROUGH carry) by 1 bit, then store result in rA.
	// This instruction can only affect the C flag.
	//rlc rA, rB
	sym = &sym_tbl.enter( "rlc", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// Rotate rB right (THROUGH carry) by 1 bit, then store result in rA.
	// This instruction can only affect the C flag.
	//rrc rA, rB
	sym = &sym_tbl.enter( "rrc", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	
	
	// rA = Sign extend of low 16 bits in rB
	// Note that the high 16 bits of rB are ignored
	//seh rA, rB
	sym = &sym_tbl.enter( "seh", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// rA = Sign extend of low 8 bits in rB
	//seb rA, rB
	sym = &sym_tbl.enter( "seb", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// Push registers rA and rb (as a pair) onto the 
	// stack (in that order)
	//push rA, rB
	sym = &sym_tbl.enter( "push", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// Pop two 32-bit values off the stack, storing the first popped
	// value into rB and the second popped value into rA
	//pop rA, rB
	sym = &sym_tbl.enter( "pop", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	
	
	// Push flags as 8-bit value onto the stack (high 4 bits of pushed
	// value are set to zero before the push)
	//push flags
	sym = &sym_tbl.enter( "push", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::flags );
	
	// Pop 8-bit value from the stack and store low 4 bits to flags
	//pop flags
	sym = &sym_tbl.enter( "pop", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::flags );
	
	// Clear rA, then CoPY FRom Flags to rA
	//cpy rA, flags
	sym = &sym_tbl.enter( "cpy", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_flags );
	
	// Copy to flags from rA
	// This instruction can affect N, V, Z, and C flags.
	//cpy flags, rA
	sym = &sym_tbl.enter( "cpy", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::flags_ra );
	
	
	
	// ENable Interrupts
	//eni
	sym = &sym_tbl.enter( "en", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::noargs );
	
	// DIsable Interrupts
	//dii
	sym = &sym_tbl.enter( "di", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::noargs );
	
	// Set the PC to interrupt RETurn address and enable Interrupts
	//reti
	sym = &sym_tbl.enter( "ret", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::noargs );
	
	// Set the PC to the Interrupt Return Address, but DON'T enable
	// interrupts
	//jump ira
	sym = &sym_tbl.enter( "jump", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ira );
	
	
	
	// Copy rA to the Interrupt Return Address
	//cpy ira, rA
	sym = &sym_tbl.enter( "cpy", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ira_ra );
	
	// Copy the Interrupt Return Address to rA
	//cpy rA, ira
	sym = &sym_tbl.enter( "cpy", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_ira );
	
	// Subroutine call using (rA + rB) as destination address. 
	// The return address is stored in the link register (lr).
	//callx rA, rB
	sym = &sym_tbl.enter( "callx", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	
	// Copy pc to rA (this can be used for pc-relative loads
	// and stores)
	//cpy rA, pc
	sym = &sym_tbl.enter( "cpy", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_pc );
	
	
	// Pseudo instruction:
	//// Subroutine call using rB as destination address. 
	//// Encoded like this:  callx r0, rB
	//call rB
}
void assembler::insert_grp_1_instructions()
{
	static constexpr size_t grp = 1;
	size_t opcode = 0;
}
void assembler::insert_grp_2_instructions()
{
	static constexpr size_t grp = 2;
	size_t opcode = 0;
}
void assembler::insert_grp_3_instructions()
{
	static constexpr size_t grp = 3;
	size_t opcode = 0;
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
