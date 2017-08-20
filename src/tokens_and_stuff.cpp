#include "tokens_and_stuff.hpp"


namespace gigachip32
{

#define VARNAME(some_tok) Tok::some_tok
#define VALUE(some_str) (some_str),

const Tok LIST_OF_TOKENS(VARNAME, VALUE) Tok::Dummy;

#undef VARNAME
#undef VALUE



#define VARNAME(some_tok) &Tok::some_tok,
#define VALUE(some_str)


const std::vector<PTok> Tok::tok_vec
({
	LIST_OF_TOKENS(VARNAME, VALUE)
});


#undef VARNAME
#undef VALUE

}
