#include "instruction_table_class.hpp"

namespace flare32
{

#define INSTR_STUFF(enc_group, args, varname, value) \
InstructionTable::varname##_##args##_##enc_group(value, 0, \
	InstrArgs::args, enc_group),



const Instruction 
	LIST_OF_INSTRUCTIONS(INSTR_STUFF)
	InstructionTable::Dummy;

#undef INSTR_STUFF


#define INSTR_STUFF(enc_group, args, varname, value) \
	&InstructionTable::varname##_##args##_##enc_group,

const std::vector<PInstr> InstructionTable::instr_g0_vec
({
	LIST_OF_GROUP_0_INSTRUCTIONS(INSTR_STUFF)

});

const std::vector<PInstr> InstructionTable::instr_g1_vec
({
	LIST_OF_GROUP_1_INSTRUCTIONS(INSTR_STUFF)

});


const std::vector<PInstr> InstructionTable::instr_g2_vec
({
	LIST_OF_GROUP_2_INSTRUCTIONS(INSTR_STUFF)

});

const std::vector<PInstr> InstructionTable::instr_g3_vec
({
	LIST_OF_GROUP_3_INSTRUCTIONS(INSTR_STUFF)

});



#undef INSTR_STUFF

const std::vector<const std::vector<PInstr>*> InstructionTable::instr_vec
({
	&InstructionTable::instr_g0_vec,
	&InstructionTable::instr_g1_vec,
	&InstructionTable::instr_g2_vec,
	&InstructionTable::instr_g3_vec
});

InstructionTable::InstructionTable()
{
	std::set<std::string> instr_names;

	for (const auto& outer_iter : instr_vec)
	{
		for (const auto& instr : *outer_iter)
		{
			instr_names.insert(instr->str());
		}
	}

	for (const auto& name : instr_names)
	{
		std::vector<PInstr> to_insert;

		for (const auto& outer_iter : instr_vec)
		{
			for (const auto& instr : *outer_iter)
			{
				if (instr->str() == name)
				{
					to_insert.push_back(instr);
				}
			}
		}

		__table[name] = std::move(to_insert);
	}


}

}
