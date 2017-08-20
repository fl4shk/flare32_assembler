#ifndef tokens_and_stuff_hpp
#define tokens_and_stuff_hpp

#include "misc_includes.hpp"


#define LIST_OF_PUNCT_TOKENS(VARNAME, VALUE) \
/* "(", ")" */ \
VARNAME(LParen) VALUE("(") \
VARNAME(RParen) VALUE(")") \
\
/* "[", "]" */ \
VARNAME(LBracket) VALUE("[") \
VARNAME(RBracket) VALUE("]") \
\
/* "=", ";", "," */ \
VARNAME(Equals) VALUE("=") \
VARNAME(Semicolon) VALUE(";") \
VARNAME(Comma) VALUE(",") \


#define LIST_OF_SINGLE_CHAR_OPERATOR_TOKENS(VARNAME, VALUE) \
/* "+", "-", etc */ \
VARNAME(Plus) VALUE("+") \
VARNAME(Minus) VALUE("-") \
VARNAME(Mult) VALUE("*") \
VARNAME(Div) VALUE("/") \
\
/* "&", "|", "^" */ \
VARNAME(BitAnd) VALUE("&") \
VARNAME(BitOr) VALUE("|") \
VARNAME(BitXor) VALUE("^") \
VARNAME(BitNot) VALUE("~") \

#define LIST_OF_MULTI_CHAR_OPERATOR_TOKESN(VARNAME, VALUE) \
/* Shift left, shift right */ \
VARNAME(BitShL) VALUE("<<") \
VARNAME(BitShR) VALUE(">>")

#define LIST_OF_OPERATOR_TOKENS(VARNAME, VALUE) \
LIST_OF_SINGLE_CHAR_OPERATOR_TOKENS(VARNAME, VALUE) \
LIST_OF_MULTI_CHAR_OPERATOR_TOKESN(VARNAME, VALUE)




#define LIST_OF_IDENT_ISH_TOKENS(VARNAME, VALUE) \
/* "Instruction", "Register", "Identifier" */ \
VARNAME(Instr) VALUE("Instruction") \
VARNAME(Reg) VALUE("Register") \
VARNAME(Ident) VALUE("Identifier")

#define LIST_OF_EXTRA_TOKENS(VARNAME, VALUE) \
/* "Number" */ \
VARNAME(NatNum) VALUE("NaturalNumber") \
\
LIST_OF_IDENT_ISH_TOKENS(VARNAME, VALUE) \
\
/* "Blank" */ \
VARNAME(Blank) VALUE("Blank")




#define LIST_OF_TOKENS(VARNAME, VALUE) \
LIST_OF_PUNCT_TOKENS(VARNAME, VALUE) \
LIST_OF_OPERATOR_TOKENS(VARNAME, VALUE) \
LIST_OF_EXTRA_TOKENS(VARNAME, VALUE)


namespace gigachip32
{


class Tok;
typedef const Tok* PTok;

// Why is this class holding all the instances of itself?  Jeez.  It works
// fine; don't get me wrong.  It's just a little weird.
class Tok
{
private:		// variables
	std::string __str;

public:		// constants
	#define VARNAME(some_tok) \
		some_tok,
	#define VALUE(some_str) 

	static const Tok LIST_OF_TOKENS(VARNAME, VALUE) Dummy;

	#undef VARNAME
	#undef VALUE

	static const std::vector<PTok> tok_vec;

public:		// functions
	inline Tok()
	{
	}
	inline Tok(const std::string& s_str) : __str(s_str)
	{
	}
	inline Tok(std::string&& s_str) : __str(std::move(s_str))
	{
	}
	inline Tok(const Tok& to_copy)
	{
		*this = to_copy;
	}
	inline Tok(Tok&& to_move)
	{
		*this = std::move(to_move);
	}

	inline Tok& operator = (const Tok& to_copy)
	{
		__str = to_copy.__str;
		return *this;
	}

	inline Tok& operator = (Tok&& to_move)
	{
		__str = std::move(to_move.__str);
		return *this;
	}

	inline bool operator == (const Tok& to_cmp) const
	{
		return (str() == to_cmp.str());
	}
	inline bool operator != (const Tok& to_cmp) const
	{
		return (str() != to_cmp.str());
	}

	inline bool operator < (const Tok& to_cmp) const
	{
		return (str() < to_cmp.str());
	}

	gen_getter_by_con_ref(str)

	gen_setter_by_con_ref(str)
	gen_setter_by_rval_ref(str)

};

}


#endif		// tokens_and_stuff_hpp
