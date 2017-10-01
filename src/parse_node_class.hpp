#ifndef parse_node_class_hpp
#define parse_node_class_hpp



#include "misc_includes.hpp"


#include "symbol_table_class.hpp"
#include "define_table_class.hpp"


namespace flare32
{
class ParsePos
{
public:		// variables
	s64 outer_index = 0;
	s64 inner_index = 0;
};
class ParseNode
{
public:		// variables
	PTok next_tok = nullptr;
	std::string next_sym_str;
	s64 next_num = -1;

public:		// functions
	inline ParseNode()
	{
	}


	inline ParseNode(PTok s_next_tok, 
		const std::string& s_next_sym_str, s64 s_next_num)
		: next_tok(s_next_tok), next_sym_str(s_next_sym_str),
		next_num(s_next_num)
	{
	}

	inline ParseNode(const ParseNode& to_copy) = default;
	inline ParseNode(ParseNode&& to_move) = default;
	inline ParseNode& operator = (const ParseNode& to_copy) = default;
	inline ParseNode& operator = (ParseNode&& to_move) = default;
};

}

#endif		// parse_node_class_hpp
