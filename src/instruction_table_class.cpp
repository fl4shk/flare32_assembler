#include "instruction_table_class.hpp"

namespace navichip32
{



void instruction_table::enter( symbol* sym, size_t opcode, size_t grp, 
	instr_args iargs, const instruction* real_instr )
{
	instruction to_push( sym, opcode, grp, iargs, real_instr );
	
	auto iter = table().find(sym);
	
	if ( iter == table().end() )
	{
		std::vector<instruction> to_insert;
		to_insert.push_back(to_push);
		
		table().insert( { sym, std::move(to_insert) } );
	}
	else
	{
		iter->second.push_back(to_push);
	}
	
}


}
