#ifndef symbol_table_class_hpp
#define symbol_table_class_hpp

#include "misc_includes.hpp"
#include "tokens_and_stuff.hpp"
#include "instruction_table_class.hpp"

namespace flare32
{

class Symbol
{
private:		// variables
	std::string __name;
	PTok __token;

	// These are used for user symbols such as labels
	s64 __value;


public:		// functions
	inline Symbol()
	{
	}
	inline Symbol(const std::string& s_name, PTok s_token, s64 s_value=0) 
		: __name(s_name), __token(s_token), __value(s_value)
	{
	}
	inline Symbol(std::string&& s_name, PTok s_token, s64 s_value=0)
		: __name(std::move(s_name)), __token(s_token), __value(s_value)
	{
	}
	inline Symbol(const Symbol& to_copy) = default;
	inline Symbol(Symbol&& to_move) = default;

	inline Symbol& operator = (const Symbol& to_copy) = default;
	inline Symbol& operator = (Symbol&& to_move) = default;

	gen_getter_and_setter_by_con_ref(name)
	gen_setter_by_rval_ref(name)
	gen_getter_and_setter_by_con_ref(token)
	gen_getter_and_setter_by_val(value)
};

class SymbolTable
{
private:		// variables
	std::map<std::string, Symbol> __table;

public:		// functions
	inline SymbolTable()
	{
	}

	// Symbol accessors
	inline Symbol& at(const std::string& some_name)
	{
		return __table[some_name];
	}

	inline const Symbol& at(const std::string& some_name) const
	{
		return __table.at(some_name);
	}

	inline bool contains(const std::string& some_name) const
	{
		return (__table.count(some_name) == 1);
	}

	inline void insert(const Symbol& to_insert)
	{
		at(to_insert.name()) = to_insert;
	}
	inline void insert(Symbol&& to_insert)
	{
		at(to_insert.name()) = std::move(to_insert);
	}


private:		// functions


};

}

#endif		// symbol_table_class_hpp
