#ifndef define_class_hpp
#define define_class_hpp


#include "misc_includes.hpp"
#include "tokens_and_stuff.hpp"
#include "instruction_table_class.hpp"

#include "user_ident_table_class.hpp"

namespace flare32
{

class Define
{
private:		// variables
	std::string __name;


	std::vector<std::string> __text, __args;


public:		// functions
	inline Define()
	{
	}
	inline Define(const std::string& s_name, 
		const std::vector<std::string>& s_text,
		const std::vector<std::string>& s_args)
		: __name(s_name), __text(s_text), __args(s_args)
	{
	}

	inline Define(const Define& to_copy) = default;
	inline Define(Define&& to_move) = default;

	inline Define& operator = (const Define& to_copy) = default;
	inline Define& operator = (Define&& to_move) = default;


	gen_getter_and_setter_by_con_ref(name);
	gen_getter_by_con_ref(text);
	gen_getter_by_ref(text);
	gen_getter_by_con_ref(args);
	gen_getter_by_ref(args);

};

typedef UserIdentTable<Define> DefineTable;



}

#endif		// define_class_hpp
