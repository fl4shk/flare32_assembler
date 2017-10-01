#ifndef warn_error_class_hpp
#define warn_error_class_hpp

#include "misc_includes.hpp"


#include "symbol_table_class.hpp"
#include "define_table_class.hpp"

#include "parse_node_class.hpp"

namespace flare32
{

class WarnError
{
private:		// variables
	size_t* __line_num = nullptr;


public:		// functions
	inline WarnError(size_t* s_line_num)
		: __line_num(s_line_num)
	{
	}
	template<typename... ArgTypes>
	void err_suffix(ArgTypes&&... args) const
	{
		printerr(", On line ", line_num(), ":  ", args..., "\n");
		exit(1);
	}
	template<typename... ArgTypes>
	void err(ArgTypes&&... args) const
	{
		printerr("Error");
		err_suffix(args...);
	}

	template<typename... ArgTypes>
	void expected(ArgTypes&&... args) const
	{
		err("Expected ", args...);
	}


	void __expected_tokens_innards() const
	{
	}
	template<typename... RemArgTypes>
	void __expected_tokens_innards(PTok tok, RemArgTypes&&... rem_args)
		const
	{
		printerr("\"", tok->str(), "\"");

		if (sizeof...(rem_args) > 0)
		{
			printerr(" or ");
			__expected_tokens_innards(rem_args...);
		}
	}
	
	template<typename... ArgTypes>
	void expected_tokens(ArgTypes&&... args) const
	{
		printerr("Error, On line ", line_num(), ":  ");
		printerr("Expected token of type ");
		__expected_tokens_innards(args...);
		printerr("!\n");
		exit(1);
	}


private:		// functions
	inline size_t line_num() const
	{
		return *__line_num;
	}

};
}


#endif		// warn_error_class_hpp
