#ifndef options_class_hpp
#define options_class_hpp


#include "misc_includes.hpp"


#include "symbol_table_class.hpp"
#include "define_table_class.hpp"

#include "parse_node_class.hpp"
#include "lexer_class.hpp"
#include "code_generator_class.hpp"

namespace flare32
{

enum class OutType
{
	Orig,
	//Binary,
};


class Options
{
public:		// variables
	OutType out_type;

};

}


#endif		// options_class_hpp
