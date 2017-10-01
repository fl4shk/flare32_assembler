#ifndef user_ident_table_class_hpp
#define user_ident_table_class_hpp


#include "misc_includes.hpp"
#include "tokens_and_stuff.hpp"
#include "instruction_table_class.hpp"


namespace flare32
{

template<typename Type>
class UserIdentTable
{
private:		// variables
	std::map<std::string, Type> __table;

public:		// functions
	inline UserIdentTable()
	{
	}

	// Type accessors
	inline Type& at(const std::string& some_name)
	{
		return __table[some_name];
	}

	inline const Type& at(const std::string& some_name) const
	{
		return __table.at(some_name);
	}

	inline bool contains(const std::string& some_name) const
	{
		return (__table.count(some_name) == 1);
	}

	inline void insert_or_assign(const Type& to_insert_or_assign)
	{
		at(to_insert_or_assign.name()) = to_insert_or_assign;
	}
	inline void insert_or_assign(Type&& to_insert_or_assign)
	{
		at(to_insert_or_assign.name()) = std::move(to_insert_or_assign);
	}

	gen_getter_by_con_ref(table);
};

}



#endif		// user_ident_table_class_hpp
