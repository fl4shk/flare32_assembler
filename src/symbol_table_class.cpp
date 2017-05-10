#include "symbol_table_class.hpp"

namespace navichip32
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


symbol& symbol_table::enter( std::string&& name_as_str, tok typ, int val,
	bool is_special )
{
	string_view name = get_name(std::move(name_as_str));
	
	return table().insert( { name, symbol( name, typ, val, is_special,
		sym_name_has_dot_f(name) ) } ).first->second;
}
bool symbol_table::find( symbol*& ret, const std::string& name_as_str )
{
	auto temp = table().find(string_view(name_as_str));
	
	if ( temp == table().end() )
	{
		ret = nullptr;
		return false;
	}
	
	ret = &(temp->second);
	return true;
}

void symbol_table::erase( const std::string& name_as_str )
{
	str_set().erase(name_as_str);
	table().erase(string_view(name_as_str));
}


}
