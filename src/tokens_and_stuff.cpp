#include "tokens_and_stuff.hpp"


namespace flare32
{

#define TOKEN_STUFF(varname, value) Tok::varname(value),

const Tok LIST_OF_TOKENS(TOKEN_STUFF) Tok::Dummy;

#undef TOKEN_STUFF



#define TOKEN_STUFF(varname, value) &Tok::varname,

const std::vector<PTok> Tok::tok_vec
({
	LIST_OF_TOKENS(TOKEN_STUFF)
});


#undef TOKEN_STUFF




}
