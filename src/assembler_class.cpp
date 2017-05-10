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
	std::vector<symbol*> sym_vec;
	
	
	// Instructions:
	// rA = rA + rB
	// This instruction can affect N, V, Z, and C flags.
	//add rA, rB
	sym = &sym_tbl.enter( "add", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// rA = rA + rB + carry_flag
	// Add with carry
	// This instruction can affect N, V, Z, and C flags.
	//adc rA, rB
	sym = &sym_tbl.enter( "adc", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// rA = rA - rB
	// This instruction can affect N, V, Z, and C flags.
	//sub rA, rB
	sym = &sym_tbl.enter( "sub", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// rA = rA + (~rB) + carry_flag
	// Subtract with borrow (6502 style)
	// This instruction can affect N, V, Z, and C flags.
	//sbc rA, rB
	sym = &sym_tbl.enter( "sbc", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	
	
	// rA = rB - rA
	// This instruction can affect N, V, Z, and C flags.
	//rsb rA, rB
	sym = &sym_tbl.enter( "rsb", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// rA = rA * rB
	//mul rA, rB
	sym = &sym_tbl.enter( "mul", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// rA = rA & rB
	// This instruction can affect the N and Z flags.
	//and rA, rB
	sym = &sym_tbl.enter( "and", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// rA = rA | rB
	// This instruction can affect the N and Z flags.
	//or rA, rB
	sym = &sym_tbl.enter( "or", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	
	
	// rA = rA ^ rB
	// This instruction can affect the N and Z flags.
	//xor rA, rB
	sym = &sym_tbl.enter( "xor", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// Logical shift left
	// rA = rA << rB
	//lsl rA, rB
	sym = &sym_tbl.enter( "lsl", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// Logical shift right
	//lsr rA, rB
	sym = &sym_tbl.enter( "lsr", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// Arithmetic shift right
	//asr rA, rB
	sym = &sym_tbl.enter( "asr", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	
	
	// Rotate rB left by rB bits, then store result in rA.
	//rol rA, rB
	sym = &sym_tbl.enter( "rol", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// Rotate rB right by rB bits, then store result in rA.
	//ror rA, rB
	sym = &sym_tbl.enter( "ror", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// Rotate rB left (THROUGH carry) by 1 bit, then store result in rA.
	// This instruction can only affect the C flag.
	//rlc rA, rB
	sym = &sym_tbl.enter( "rlc", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// Rotate rB right (THROUGH carry) by 1 bit, then store result in rA.
	// This instruction can only affect the C flag.
	//rrc rA, rB
	sym = &sym_tbl.enter( "rrc", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	
	
	// rA = Sign extend of low 16 bits in rB
	// Note that the high 16 bits of rB are ignored
	//seh rA, rB
	sym = &sym_tbl.enter( "seh", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// rA = Sign extend of low 8 bits in rB
	//seb rA, rB
	sym = &sym_tbl.enter( "seb", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// Push registers rA and rb (as a pair) onto the 
	// stack (in that order)
	//push rA, rB
	sym = &sym_tbl.enter( "push", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// Pop two 32-bit values off the stack, storing the first popped
	// value into rB and the second popped value into rA
	//pop rA, rB
	sym = &sym_tbl.enter( "pop", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	
	
	// Push flags as 8-bit value onto the stack (high 4 bits of pushed
	// value are set to zero before the push)
	//push flags
	sym = &sym_tbl.enter( "push", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::flags );
	sym_vec.push_back(sym);
	
	// Pop 8-bit value from the stack and store low 4 bits to flags
	//pop flags
	sym = &sym_tbl.enter( "pop", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::flags );
	sym_vec.push_back(sym);
	
	// Clear rA, then CoPY FRom Flags to rA
	//cpy rA, flags
	sym = &sym_tbl.enter( "cpy", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_flags );
	sym_vec.push_back(sym);
	
	// Copy to flags from rA
	// This instruction can affect N, V, Z, and C flags.
	//cpy flags, rA
	sym = &sym_tbl.enter( "cpy", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::flags_ra );
	sym_vec.push_back(sym);
	
	
	
	// ENable Interrupts
	//eni
	sym = &sym_tbl.enter( "en", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::noargs );
	sym_vec.push_back(sym);
	
	// DIsable Interrupts
	//dii
	sym = &sym_tbl.enter( "di", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::noargs );
	sym_vec.push_back(sym);
	
	// Set the PC to interrupt RETurn address and enable Interrupts
	//reti
	sym = &sym_tbl.enter( "ret", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::noargs );
	sym_vec.push_back(sym);
	
	// Set the PC to the Interrupt Return Address, but DON'T enable
	// interrupts
	//jump ira
	sym = &sym_tbl.enter( "jump", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ira );
	sym_vec.push_back(sym);
	
	
	
	// Copy rA to the Interrupt Return Address
	//cpy ira, rA
	sym = &sym_tbl.enter( "cpy", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ira_ra );
	sym_vec.push_back(sym);
	
	// Copy the Interrupt Return Address to rA
	//cpy rA, ira
	sym = &sym_tbl.enter( "cpy", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_ira );
	sym_vec.push_back(sym);
	
	// Subroutine call using (rA + rB) as destination address. 
	// The return address is stored in the link register (lr).
	//callx rA, rB
	sym = &sym_tbl.enter( "callx", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb );
	sym_vec.push_back(sym);
	
	// Copy pc to rA (this can be used for pc-relative loads
	// and stores)
	//cpy rA, pc
	sym = &sym_tbl.enter( "cpy", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_pc );
	sym_vec.push_back(sym);
	
	
	// Pseudo instruction:
	//// Subroutine call using rB as destination address. 
	//// Encoded like this:  callx r0, rB
	//call rB
	
	insert_dot_f_instructions(sym_vec);
}
void assembler::insert_grp_1_instructions()
{
	static constexpr size_t grp = 1;
	size_t opcode = 0;
	symbol* sym;
	std::vector<symbol*> sym_vec;
	
	
	// Instructions:
	// rA = rB + (zero-extended imm)
	// This instruction can affect N, V, Z, and C flags.
	//addi rA, rB, imm
	sym = &sym_tbl.enter( "addi", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	// rA = rB + (zero-extended imm) + carry_flag
	// Add with carry
	// This instruction can affect N, V, Z, and C flags.
	//adci rA, rB, imm
	sym = &sym_tbl.enter( "adci", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	// rA = rB - (zero-extended imm)
	// This instruction can affect N, V, Z, and C flags.
	//subi rA, rB, imm
	sym = &sym_tbl.enter( "subi", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	// rA = rB + (~(zero-extended imm)) + carry_flag
	// Subtract with borrow (6502 style)
	// This instruction can affect N, V, Z, and C flags.
	//sbci rA, rB, imm
	sym = &sym_tbl.enter( "sbci", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	
	
	// rA = (zero-extended imm) - rB
	// This instruction can affect N, V, Z, and C flags.
	//rsbi rA, rB, imm
	sym = &sym_tbl.enter( "rsbi", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	// rA = rB * (zero-extended imm)
	//muli rA, rB, imm
	sym = &sym_tbl.enter( "muli", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	// rA = rB & (zero-extended imm)
	// This instruction can affect the N and Z flags.
	//andi rA, rB, imm
	sym = &sym_tbl.enter( "andi", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	// rA = rB | (zero-extended imm)
	// This instruction can affect the N and Z flags.
	//ori rA, rB, imm
	sym = &sym_tbl.enter( "ori", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	
	
	// rA = rB ^ (zero-extended imm)
	// This instruction can affect the N and Z flags.
	//xori rA, rB, imm
	sym = &sym_tbl.enter( "xori", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	// Logical shift left
	// rA = rB << (zero-extended imm)
	//lsli rA, rB, imm
	sym = &sym_tbl.enter( "lsli", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	// Logical shift right
	//lsri rA, rB, imm
	sym = &sym_tbl.enter( "lsri", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	// Arithmetic shift right
	//asri rA, rB, imm
	sym = &sym_tbl.enter( "asri", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	
	
	// Rotate rB left by (zero-extended imm) bits, then store result in rA.
	//roli rA, rB, imm
	sym = &sym_tbl.enter( "roli", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	// Rotate rB right by (zero-extended imm) bits, then store result in rA.
	//rori rA, rB, imm
	sym = &sym_tbl.enter( "rori", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::ra_rb_imm16u );
	sym_vec.push_back(sym);
	
	// Branch always, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bra imm
	sym = &sym_tbl.enter( "bra", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	// Branch when Z == 0, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bne imm
	sym = &sym_tbl.enter( "bne", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	
	
	// Branch when Z == 1, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//beq imm
	sym = &sym_tbl.enter( "beq", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	// Branch when C == 0 [unsigned less than], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bcc imm
	sym = &sym_tbl.enter( "bcc", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	// Branch when C == 1 [unsigned greater than or equal], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bcs imm
	sym = &sym_tbl.enter( "bcs", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	// Branch when ( C == 0 or Z == 1 ) [unsigned less than or equal], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bls imm
	sym = &sym_tbl.enter( "bls", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	
	
	// Branch when ( C == 1 and Z == 0 ) [unsigned greater than], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bhi imm
	sym = &sym_tbl.enter( "bhi", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	// Branch when N == 0, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bpl imm
	sym = &sym_tbl.enter( "bpl", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	// Branch when N == 1, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bmi imm
	sym = &sym_tbl.enter( "bmi", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	// Branch when V == 0, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bvc imm
	sym = &sym_tbl.enter( "bvc", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	
	
	// Branch when V == 1, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bvs imm
	sym = &sym_tbl.enter( "bvs", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	// Branch when N == V [signed greater than or equal], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bge imm
	sym = &sym_tbl.enter( "bge", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	// Branch when N != V [signed less than], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//blt imm
	sym = &sym_tbl.enter( "blt", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	// Branch when ( N == V and Z == 0 ) [signed greater than], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bgt imm
	sym = &sym_tbl.enter( "bgt", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	
	
	// Branch when ( N != V or Z == 1 ) [signed less than or equal], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//ble imm
	sym = &sym_tbl.enter( "ble", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	// rA = rB & (sign-extended imm)
	// This instruction can affect the N and Z flags.
	//andsi rA, rB, imm
	sym = &sym_tbl.enter( "andsi", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	// rA = rB | (sign-extended imm)
	// This instruction can affect the N and Z flags.
	//orsi rA, rB, imm
	sym = &sym_tbl.enter( "orsi", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	// rA = rB ^ (sign-extended imm)
	// This instruction can affect the N and Z flags.
	//xorsi rA, rB, imm
	sym = &sym_tbl.enter( "xorsi", static_cast<tok>(tok_defn::instr), 0 );
	instr_tbl.enter( sym, opcode++, grp, instr_args::branchoffset );
	sym_vec.push_back(sym);
	
	
	
	// Pseudo instruction:
	//// Compare rB to (zero-extended imm)
	//// temp = rB - (zero-extended imm)
	//// Encoded like this:  subi.f r0, rB, imm
	//// This instruction can affect N, V, Z, and C flags.
	//cmpi rB, imm
	
	// Pseudo instruction:
	//// Compare rB to negated (zero-extended imm)
	//// temp = rB - (-(zero-extended imm))
	//// Encoded like this:  addi.f r0, rB, imm
	//// This instruction can affect N, V, Z, and C flags.
	//cmni rB, imm
	
	// Pseudo instruction:
	//// Compare reversed with immediate value
	//// temp = (zero-extended imm) - rB
	//// Encoded like this:  rsbi.f r0, rB, imm
	//// This instruction can affect N, V, Z, and C flags.
	//cmri rB, imm

	// Pseudo instruction:
	//// Copy Negated
	//// rA = -rB
	//// Encoded like this:  rsbi rA, rB, 0
	//cpn rA, rB
	
	// Pseudo instruction:
	//// Copy Complemented
	//// rA = ~rB
	//// Encoded like this:  xorsi rA, rB, -1
	//cpc rA, rB
	
	
	
	
	// Pseudo instruction:
	//// temp = rB & (zero-extended imm)
	//// Encoded like this:  andi r0, rB, imm
	//// This instruction can affect the N and Z flags.
	//tsti rB, imm
	
	insert_dot_f_instructions(sym_vec);
}
void assembler::insert_grp_2_instructions()
{
	static constexpr size_t grp = 2;
	size_t opcode = 0;
	symbol* sym;
	std::vector<symbol*> sym_vec;
	
	
	//// Instructions:
	//// Load 32-bit value from address (rB + rC + (sign-extended imm)) into
	//// rA.
	//ldr rA, rB, rC, imm
	//
	//// Load zero-extended 16-bit value from address 
	//// (rB + rC + (sign-extended imm)) into rA.
	//// This zero-extends the value.
	//ldh rA, rB, rC, imm
	//
	//// Load sign-extended 16-bit value from address 
	//// (rB + rC + (sign-extended imm)) into rA.
	//// This sign-extends the value.
	//ldsh rA, rB, rC, imm
	//
	//// Load zero-extended 8-bit value from address 
	//// (rB + rC + (sign-extended imm)) into rA.
	//// This zero-extends the value.
	//ldb rA, rB, rC, imm
	//
	//
	//
	//// Load sign-extended 8-bit value from address 
	//// (rB + rC + (sign-extended imm)) into rA.
	//// This sign-extends the value.
	//ldsb rA, rB, rC, imm
	//
	//// Store 32-bit value in rA to address (rB + rC + (sign-extended imm)).
	//str rA, rB, rC, imm
	//
	//// Store low 16 bits of rA to address (rB + rC + (sign-extended imm)).
	//sth rA, rB, rC, imm
	//
	//// Store low 8 bits of rA to address (rB + rC + (sign-extended imm)).
	//stb rA, rB, rC, imm
	//
	//
	//// rA = rB + rC
	//// This instruction can affect N, V, Z, and C flags.
	//add rA, rB, rC
	//
	//// rA = rB + rC + carry_flag
	//// Add with carry
	//// This instruction can affect N, V, Z, and C flags.
	//adc rA, rB, rC
	//
	//// rA = rB - rC
	//// This instruction can affect N, V, Z, and C flags.
	//sub rA, rB, rC
	//
	//// rA = rB + (~rC) + carry_flag
	//// Subtract with borrow (6502 style)
	//// This instruction can affect N, V, Z, and C flags.
	//sbc rA, rB, rC
	//
	//
	//
	//// rA = rC - rB
	//// This instruction can affect N, V, Z, and C flags.
	//rsb rA, rB, rC
	//
	//// rA = rB * rC
	//mul rA, rB, rC
	//
	//// rA = rB & rC
	//// This instruction can affect the N and Z flags.
	//and rA, rB, rC
	//
	//// rA = rB | rC
	//// This instruction can affect the N and Z flags.
	//or rA, rB, rC
	//
	//
	//
	//// rA = rB ^ rC
	//// This instruction can affect the N and Z flags.
	//xor rA, rB, rC
	//
	//// Logical shift left
	//// rA = rB << rC
	//lsl rA, rB, rC
	//
	//// Logical shift right
	//lsr rA, rB, rC
	//
	//// Arithmetic shift right
	//asr rA, rB, rC
	//
	//
	//
	//// Rotate rB left by rC bits, then store result in rA.
	//rol rA, rB, rC
	//
	//// Rotate rB right by rC bits, then store result in rA.
	//ror rA, rB, rC
	//
	//// Fused multiply-add
	//// rA = rA + (rB * rC)
	//fma rA, rB, rC
	//
	//// Copy rC to rA and to rB
	//// If rA is the same register as rB, then the 
	//// register will only be written once.
	//cpyp rA, rB, rC
	//
	//
	//
	//// Set pc to destination address in (rA + rB).
	//jumpx rA, rB
	//
	//// Add 4 to rB, then load from address in rB into
	//// rA
	//// LoaD Register, Add Before
	//ldrpb rA, rB
	//
	//// Store rA to address in rB, then subtract 4 from
	//// rB
	//// STore Register, Subtract After
	//strma rA, rB
	//
	//// Reserved for future expansion.
	//
	//
	//
	//// Reserved for future expansion.
	//// Reserved for future expansion.
	//// Reserved for future expansion.
	//// Reserved for future expansion.
	//
	//
	//
	//// Pseudo instruction:
	////// Load 32-bit value from address rB into rA.
	////// Encoded like this:  ldr rA, rB, r0, 0 
	////ldr rA, rB
	//
	//// Pseudo instruction:
	////// Load zero-extended 16-bit value from address rB into rA.
	////// This zero-extends the value.
	////// Encoded like this:  ldh rA, rB, r0, 0 
	////ldh rA, rB
	//
	//// Pseudo instruction:
	////// Load sign-extended 16-bit value from address rB into rA.
	////// This sign-extends the value.
	////// Encoded like this:  ldsh rA, rB, r0, 0 
	////ldsh rA, rB
	//
	//// Pseudo instruction:
	////// Load zero-extended 8-bit value from address rB into rA.
	////// This zero-extends the value.
	////// Encoded like this:  ldb rA, rB, r0, 0 
	////ldb rA, rB
	//
	//
	//
	//// Pseudo instruction:
	////// Load sign-extended 8-bit value from address rB into rA.
	////// This sign-extends the value.
	////// Encoded like this:  ldsb rA, rB, r0, 0 
	////ldsb rA, rB
	//
	//// Pseudo instruction:
	////// Store 32-bit value in rA to address rB.
	////// Encoded like this:  str rA, rB, r0, 0 
	////str rA, rB
	//
	//// Pseudo instruction:
	////// Store low 16 bits of rA to address rB.
	////// Encoded like this:  sth rA, rB, r0, 0 
	////sth rA, rB
	//
	//// Pseudo instruction:
	////// Store low 8 bits of rA to address rB.
	////// Encoded like this:  stb rA, rB, r0, 0 
	////stb rA, rB
	//
	//// Pseudo instruction:
	////// Load 32-bit value from address (rB + rC) into rA.
	////// Encoded like this:  ldr rA, rB, rC, 0 
	////ldr rA, rB, rC
	//
	//// Pseudo instruction:
	////// Load zero-extended 16-bit value from address (rB + rC) into rA.
	////// This zero-extends the value.
	////// Encoded like this:  ldh rA, rB, rC, 0 
	////ldh rA, rB, rC
	//
	//// Pseudo instruction:
	////// Load sign-extended 16-bit value from address (rB + rC) into rA.
	////// This sign-extends the value.
	////// Encoded like this:  ldsh rA, rB, rC, 0 
	////ldsh rA, rB, rC
	//
	//// Pseudo instruction:
	////// Load zero-extended 8-bit value from address (rB + rC) into rA.
	////// This zero-extends the value.
	////// Encoded like this:  ldb rA, rB, rC, 0 
	////ldb rA, rB, rC
	//
	//
	//
	//// Pseudo instruction:
	////// Load sign-extended 8-bit value from address (rB + rC) into rA.
	////// This sign-extends the value.
	////// Encoded like this:  ldsb rA, rB, rC, 0 
	////ldsb rA, rB, rC
	//
	//// Pseudo instruction:
	////// Store 32-bit value in rA to address (rB + rC).
	////// Encoded like this:  str rA, rB, rC, 0 
	////str rA, rB, rC
	//
	//// Pseudo instruction:
	////// Store low 16 bits of rA to address (rB + rC).
	////// Encoded like this:  sth rA, rB, rC, 0 
	////sth rA, rB, rC
	//
	//// Pseudo instruction:
	////// Store low 8 bits of rA to address (rB + rC).
	////// Encoded like this:  stb rA, rB, rC, 0 
	////stb rA, rB, rC
	//
	//// Pseudo instruction:
	////// Load 32-bit value from address (rB + (sign-extended imm)) into rA.
	////// Encoded like this:  ldr rA, rB, r0, imm 
	////ldr rA, rB, imm
	//
	//// Pseudo instruction:
	////// Load zero-extended 16-bit value from address (rB + (sign-extended imm)) into rA.
	////// This zero-extends the value.
	////// Encoded like this:  ldh rA, rB, r0, imm 
	////ldh rA, rB, imm
	//
	//// Pseudo instruction:
	////// Load sign-extended 16-bit value from address (rB + (sign-extended imm)) into rA.
	////// This sign-extends the value.
	////// Encoded like this:  ldsh rA, rB, r0, imm 
	////ldsh rA, rB, imm
	//
	//// Pseudo instruction:
	////// Load zero-extended 8-bit value from address (rB + (sign-extended imm)) into rA.
	////// This zero-extends the value.
	////// Encoded like this:  ldb rA, rB, r0, imm 
	////ldb rA, rB, imm
	//
	//
	//
	//// Pseudo instruction:
	////// Load sign-extended 8-bit value from address (rB + (sign-extended imm)) into rA.
	////// This sign-extends the value.
	////// Encoded like this:  ldsb rA, rB, r0, imm 
	////ldsb rA, rB, imm
	//
	//// Pseudo instruction:
	////// Store 32-bit value in rA to address (rB + (sign-extended imm)).
	////// Encoded like this:  str rA, rB, r0, imm 
	////str rA, rB, imm
	//
	//// Pseudo instruction:
	////// Store low 16 bits of rA to address (rB + (sign-extended imm)).
	////// Encoded like this:  sth rA, rB, r0, imm 
	////sth rA, rB, imm
	//
	//// Pseudo instruction:
	////// Store low 8 bits of rA to address (rB + (sign-extended imm)).
	////// Encoded like this:  stb rA, rB, r0, imm 
	////stb rA, rB, imm
	//
	//
	//
	//// Pseudo instruction:
	////// temp = rB - rC
	////// This instruction can affect N, V, Z, and C flags.
	////// Encoded like this:  sub.f r0, rB, rC
	////cmp rB, rC
	//
	//// Pseudo instruction:
	////// temp = rB - (-rC)
	////// This instruction can affect N, V, Z, and C flags.
	////// Encoded like this:  add.f r0, rB, rC
	////cmn rB, rC
	//
	//// Pseudo instruction:
	////// temp = rC - rB
	////// This instruction can affect N, V, Z, and C flags.
	////// Encoded like this:  rsb.f r0, rB, rC
	////cmr rB, rC
	//
	//// Pseudo instruction:
	////// temp = rB & rC
	////// Encoded like this:  and.f r0, rB, rC
	////// This instruction can affect the N and Z flags.
	////tst rB, rC
	//
	//
	//
	//// Pseudo instruction:
	////// Copy
	////// rA = rC
	////// Encoded like this:  cpyp rA, rA, rC
	////cpy rA, rC
	//
	//// Pseudo instruction:
	////// Set pc to destination address in rB.
	////// Encoded like this:  jumpx r0, rB
	////jump rB
	//
	//// Pseudo instruction:
	////// Set pc to destination address in rB.
	////// Encoded like this:  jumpx r0, rB
	////cpy pc, rB
	//
	//// Pseudo instruction:
	////// Push register rA onto the stack
	////// Encoded like this:  strma rA, sp
	////push rA
	//
	//
	//
	//// Pseudo instruction:
	////// Pop 32-bit value off the stack into register rA
	////// Encoded like this:  ldrpb rA, sp
	////pop rA
	
}
void assembler::insert_grp_3_instructions()
{
	static constexpr size_t grp = 3;
	size_t opcode = 0;
	symbol* sym;
}
void assembler::insert_dot_f_instructions
	( const std::vector<symbol*>& sym_vec )
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
