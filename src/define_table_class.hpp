#ifndef define_class_hpp
#define define_class_hpp


#include "misc_includes.hpp"
#include "tokens_and_stuff.hpp"
#include "instruction_table_class.hpp"

namespace flare32
{

class Define
{
private:		// variables
	std::string __name, __text;

	std::vector<std::string> __args;


public:		// functions
	inline Define()
	{
	}
	inline Define(const std::string& s_name, const std::string& s_text,
		const std::vector<std::string>& s_args)
		: __name(s_name), __text(s_text), __args(s_args)
	{
	}

	inline Define(const Define& to_copy) = default;
	inline Define(Define&& to_move) = default;

	inline Define& operator = (const Define& to_copy) = default;
	inline Define& operator = (Define&& to_move) = default;


	gen_getter_by_con_ref(name);
	gen_getter_by_con_ref(text);
	gen_getter_by_con_ref(args);

};

class DefineTable
{
private:		// variables
	std::map<std::string, Define> __table;

public:		// functions
	inline DefineTable()
	{
	}

	// Define accessors
	inline Define& at(const std::string& some_name)
	{
		return __table[some_name];
	}

	inline const Define& at(const std::string& some_name) const
	{
		return __table.at(some_name);
	}

	inline bool contains(const std::string& some_name) const
	{
		return (__table.count(some_name) == 1);
	}

	inline void insert_or_assign(const Define& to_insert_or_assign)
	{
		at(to_insert_or_assign.name()) = to_insert_or_assign;
	}
	inline void insert_or_assign(Define&& to_insert_or_assign)
	{
		at(to_insert_or_assign.name()) = std::move(to_insert_or_assign);
	}
};


}

#endif		// define_class_hpp
