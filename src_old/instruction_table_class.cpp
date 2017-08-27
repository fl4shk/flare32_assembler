#include "instruction_table_class.hpp"

namespace flare32
{

void instruction_table::enter( const std::string& name, size_t opcode, 
	size_t grp, instr_args iargs, const std::string& real_instr_name,
	size_t real_instr_index )
{
	instruction to_push( name, opcode, grp, iargs, real_instr_name,
		real_instr_index );
	
	auto iter = table().find(name);
	
	if ( iter == table().end() )
	{
		std::vector<instruction> to_insert;
		to_insert.push_back(to_push);
		
		table().insert( { name, std::move(to_insert) } );
	}
	else
	{
		iter->second.push_back(to_push);
	}
	
}


}
