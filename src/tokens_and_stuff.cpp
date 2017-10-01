#include "tokens_and_stuff.hpp"


namespace flare32
{

//#define VARNAME(some_tok) Tok::some_tok
//#define VALUE(some_str) (some_str),

#define TOKEN_STUFF(varname, value) Tok::varname(value),

//const Tok LIST_OF_TOKENS(VARNAME, VALUE) Tok::Dummy;

const Tok LIST_OF_TOKENS(TOKEN_STUFF) Tok::Dummy;

#undef TOKEN_STUFF



//#define VARNAME(some_tok) &Tok::some_tok,
//#define VALUE(some_str)

#define TOKEN_STUFF(varname, value) &Tok::varname,

const std::vector<PTok> Tok::tok_vec
({
	//LIST_OF_TOKENS(VARNAME, VALUE)
	LIST_OF_TOKENS(TOKEN_STUFF)
});


#undef TOKEN_STUFF




}
