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


symbol& symbol_table::enter( const string_view& name, tok typ, int val,
	size_t instr_grp )
{
	auto maybe_ret = table().find(name);
	
	if ( maybe_ret != table().end() )
	{
		return maybe_ret->second;
	}
	
	return( table()[name] = std::move(symbol( name, typ, val, instr_grp,
		sym_name_has_dot_f(name) )) );
}






}
