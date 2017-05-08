#include "symbol_table_class.hpp"

namespace assembler
{

bool symbol_table::sym_name_has_dot_f( const string_view& name ) const
{
	if ( name.size() >= 2 )
	{
		return ( ( *( name.cend() - 2 ) == '.' ) 
			&& ( *( name.cend() - 1 ) == 'f' ) );
	}
	
	return false;
}

string_view symbol_table::get_name( std::string&& name_as_str )
{
	return string_view(*str_set().insert(std::move(name_as_str)).first);
}


symbol& symbol_table::enter( std::string&& name_as_str, tok typ, 
	int val, size_t instr_grp )
{
	string_view name = get_name(std::move(name_as_str));
	
	return table().insert( { name,
		symbol( name, typ, val, instr_grp, sym_name_has_dot_f(name) ) } )
		.first->second;
}


}
