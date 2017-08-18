#include "symbol_table_class.hpp"

namespace navichip32
{

bool symbol_table::sym_name_has_dot_f( const std::string& name ) const
{
	if ( name.size() >= 2 )
	{
		return ( ( *( name.cend() - 2 ) == '.' ) 
			&& ( *( name.cend() - 1 ) == 'f' ) );
	}
	
	return false;
}

//string_view symbol_table::get_name( std::string&& name )
//{
//	return string_view(*str_set().insert(std::move(name)).first);
//}
//const std::string* symbol_table::get_name( const std::string& name )
//{
//	return &(*str_set().insert(name).first);
//}


symbol& symbol_table::enter( const std::string& name, tok typ, int val, 
	bool is_special )
{
	return table().insert( { name, symbol( name, typ, val, is_special,
		sym_name_has_dot_f(name) ) } ).first->second;
}
symbol& symbol_table::enter( std::string&& name, tok typ, int val, 
	bool is_special )
{
	const std::string temp = name;
	return table().insert( { std::move(name), symbol( temp, typ, val, 
		is_special, sym_name_has_dot_f(temp) ) } ).first->second;
}
bool symbol_table::find( symbol*& ret, const std::string& name )
{
	//auto temp = table().find(string_view(name));
	auto temp = table().find(name);
	
	if ( temp == table().end() )
	{
		ret = nullptr;
		return false;
	}
	
	ret = &(temp->second);
	return true;
}

void symbol_table::erase( const std::string& name )
{
	//str_set().erase(name);
	table().erase(name);
}


}
