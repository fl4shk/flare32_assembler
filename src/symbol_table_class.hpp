#ifndef symbol_table_class_hpp
#define symbol_table_class_hpp

#include "misc_includes.hpp"
#include "tokens_and_stuff.hpp"
#include "instruction_table_class.hpp"

#include "user_ident_table_class.hpp"

namespace flare32
{

enum class SymType
{
	Other,
	EquateName,
	DefineName,
	MacroName,
};

class Symbol
{
private:		// variables
	std::string __name;
	PTok __token;

	s64 __value;

	SymType __type;


public:		// functions
	inline Symbol()
	{
	}
	inline Symbol(const std::string& s_name, PTok s_token, s64 s_value=0,
		SymType s_type=SymType::Other) 
		: __name(s_name), __token(s_token), __value(s_value),
		__type(s_type)
	{
	}
	inline Symbol(std::string&& s_name, PTok s_token, s64 s_value=0,
		SymType s_type=SymType::Other)
		: __name(std::move(s_name)), __token(s_token), __value(s_value),
		__type(s_type)
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
	gen_getter_and_setter_by_val(type)
};

typedef UserIdentTable<Symbol> SymbolTable;

}

#endif		// symbol_table_class_hpp
