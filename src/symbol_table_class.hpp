#ifndef symbol_table_class_hpp
#define symbol_table_class_hpp

#include "token_stuff_etc.hpp"
#include "instruction_table_class.hpp"

namespace navichip32
{

class symbol
{
private:		// variables
	std::string internal_name;
	tok internal_typ = 0;
	int internal_val = 0;
	
	
	bool internal_is_special = false;
	
	bool internal_has_dot_f = false;
	
private:		// functions
	gen_setter_by_con_ref(name);
	gen_setter_by_val(typ);
	gen_setter_by_val(is_special);
	gen_setter_by_val(has_dot_f);
	
public:		// functions
	inline symbol()
	{
	}
	inline symbol( const std::string& s_name, tok s_typ, int s_val, 
		bool s_is_special, bool s_has_dot_f )
	{
		set_name(s_name);
		set_typ(s_typ);
		set_val(s_val);
		set_is_special(s_is_special);
		set_has_dot_f(s_has_dot_f);
	}
	inline symbol( std::string&& s_name, tok s_typ, int s_val, 
		bool s_is_special, bool s_has_dot_f )
	{
		set_name(std::move(s_name));
		set_typ(s_typ);
		set_val(s_val);
		set_is_special(s_is_special);
		set_has_dot_f(s_has_dot_f);
	}
	inline symbol( const symbol& to_copy ) = default;
	inline symbol( symbol&& to_move ) = default;
	inline ~symbol()
	{
	}
	
	inline symbol& operator = ( const symbol& to_copy ) = default;
	inline symbol& operator = ( symbol&& to_move ) = default;
	
	gen_setter_by_val(val);
	gen_getter_by_con_ref(name);
	gen_getter_by_val(typ);
	gen_getter_by_val(val);
	gen_getter_by_val(is_special);
	gen_getter_by_val(has_dot_f);
	
	
};


class symbol_table
{
private:		// variables
	//// Prevent duplicate std::strings, should be okay, not the fastest
	//// thing I could ever do, though.
	std::unordered_map< std::string, symbol > internal_table;
	
	
private:		// functions
	//gen_getter_by_ref(str_set);
	gen_getter_by_ref(table);
	
	bool sym_name_has_dot_f( const std::string& name ) const;
	
	////string_view get_name( std::string&& name );
	//const std::string* get_name( const std::string& name );
	
public:		// functions
	inline symbol_table()
	{
	}
	inline symbol_table( const symbol_table& to_copy ) = delete;
	inline ~symbol_table()
	{
	}
	symbol_table& operator = ( const symbol_table& to_copy ) = delete;
	
	
	symbol& enter( const std::string& name, tok typ, int val, 
		bool is_special );
	symbol& enter( std::string&& name, tok typ, int val, bool is_special );
	bool find( symbol*& ret, const std::string& name );
	void erase( const std::string& name );
	
	inline auto cbegin() const
	{
		return table().cbegin();
	}
	inline auto cend() const
	{
		return table().cend();
	}
	
	//gen_getter_by_con_ref(str_set);
	gen_getter_by_con_ref(table);
	
};


}


#endif		// symbol_table_class_hpp
