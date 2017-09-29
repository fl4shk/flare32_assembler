#include "instruction_table_class.hpp"

namespace flare32
{

#define INSTR_STUFF(enc_group, args, varname, value) \
Instruction::varname##_##args##_##enc_group(value, 0, InstrArgs::args, \
	enc_group),
#define INSTR_STUFF_AFFECTS_FLAGS(enc_group, args, varname, value) \
Instruction::varname##_##args##_##enc_group##_affects_flags(value ".f", \
	1, InstrArgs::args, enc_group),


const Instruction 
	LIST_OF_INSTRUCTIONS(INSTR_STUFF)
	LIST_OF_INSTRUCTIONS(INSTR_STUFF_AFFECTS_FLAGS) 
	Instruction::Dummy;

#undef INSTR_STUFF
#undef INSTR_STUFF_AFFECTS_FLAGS


#define INSTR_STUFF(enc_group, args, varname, value) \
	&Instruction::varname##_##args##_##enc_group,
#define INSTR_STUFF_AFFECTS_FLAGS(enc_group, args, varname, value) \
	&Instruction::varname##_##args##_##enc_group##_affects_flags,

const std::vector<PInstr> Instruction::instr_g0_vec
({
	LIST_OF_GROUP_0_INSTRUCTIONS(INSTR_STUFF)

	LIST_OF_GROUP_0_INSTRUCTIONS(INSTR_STUFF_AFFECTS_FLAGS)
});

const std::vector<PInstr> Instruction::instr_g1_vec
({
	LIST_OF_GROUP_1_INSTRUCTIONS(INSTR_STUFF)

	LIST_OF_GROUP_1_INSTRUCTIONS(INSTR_STUFF_AFFECTS_FLAGS)
});


const std::vector<PInstr> Instruction::instr_g2_vec
({
	LIST_OF_GROUP_2_INSTRUCTIONS(INSTR_STUFF)

	LIST_OF_GROUP_2_INSTRUCTIONS(INSTR_STUFF_AFFECTS_FLAGS)
});

const std::vector<PInstr> Instruction::instr_g3_vec
({
	LIST_OF_GROUP_3_INSTRUCTIONS(INSTR_STUFF)

	LIST_OF_GROUP_3_INSTRUCTIONS(INSTR_STUFF_AFFECTS_FLAGS)
});


//const std::vector<PInstr> Instruction::instr_vec
//({
//	LIST_OF_INSTRUCTIONS(INSTR_STUFF)
//
//	LIST_OF_INSTRUCTIONS(INSTR_STUFF_AFFECTS_FLAGS)
//});


#undef INSTR_STUFF
#undef INSTR_STUFF_AFFECTS_FLAGS

const std::vector<const std::vector<PInstr>*> Instruction::instr_vec
({
	&Instruction::instr_g0_vec,
	&Instruction::instr_g1_vec,
	&Instruction::instr_g2_vec,
	&Instruction::instr_g3_vec
});

}
