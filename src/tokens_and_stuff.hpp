#ifndef tokens_and_stuff_hpp
#define tokens_and_stuff_hpp

#include "misc_includes.hpp"


#define LIST_OF_COMMENT_TOKENS(TOKEN_STUFF) \
TOKEN_STUFF(Semicolon, ";") \

#define LIST_OF_PUNCT_TOKENS(TOKEN_STUFF) \
/* "." */ \
TOKEN_STUFF(Period, ".") \
\
/* "(", ")" */ \
TOKEN_STUFF(LParen, "(") \
TOKEN_STUFF(RParen, ")") \
\
/* "[", "]" */ \
TOKEN_STUFF(LBracket, "[") \
TOKEN_STUFF(RBracket, "]") \
\
/* "{", "}" */ \
TOKEN_STUFF(LBrace, "{") \
TOKEN_STUFF(RBrace, "}") \
\
/* "=", ";", ",", etc. */ \
TOKEN_STUFF(Equals, "=") \
LIST_OF_COMMENT_TOKENS(TOKEN_STUFF) \
TOKEN_STUFF(Comma, ",") \
TOKEN_STUFF(Colon, ":") \
TOKEN_STUFF(At, "@") \




#define LIST_OF_SINGLE_CHAR_OPERATOR_TOKENS(TOKEN_STUFF) \
/* "+", "-", etc */ \
TOKEN_STUFF(Plus, "+") \
TOKEN_STUFF(Minus, "-") \
TOKEN_STUFF(Mult, "*") \
TOKEN_STUFF(Div, "/") \
\
/* "&", "|", "^" */ \
TOKEN_STUFF(BitAnd, "&") \
TOKEN_STUFF(BitOr, "|") \
TOKEN_STUFF(BitXor, "^") \
TOKEN_STUFF(BitNot, "~") \

#define LIST_OF_MULTI_CHAR_OPERATOR_TOKESN(TOKEN_STUFF) \
/* Shift left, shift right */ \
TOKEN_STUFF(BitShL, "<<") \
TOKEN_STUFF(BitShR, ">>")

#define LIST_OF_OPERATOR_TOKENS(TOKEN_STUFF) \
LIST_OF_SINGLE_CHAR_OPERATOR_TOKENS(TOKEN_STUFF) \
LIST_OF_MULTI_CHAR_OPERATOR_TOKESN(TOKEN_STUFF)




#define LIST_OF_IDENT_ISH_TOKENS(TOKEN_STUFF) \
/* "Instruction", "Register", "Identifier" */ \
TOKEN_STUFF(Instr, "Instruction") \
TOKEN_STUFF(Reg, "Register") \
TOKEN_STUFF(RegPc, "PC") \
TOKEN_STUFF(RegIra, "IRA") \
TOKEN_STUFF(RegFlags, "Flags") \
TOKEN_STUFF(Ident, "Identifier")

#define LIST_OF_EXTRA_TOKENS(TOKEN_STUFF) \
/* "Number" */ \
TOKEN_STUFF(NatNum, "NaturalNumber") \
\
LIST_OF_IDENT_ISH_TOKENS(TOKEN_STUFF) \
\
/* "Newline", "EOF", "Bad" */ \
TOKEN_STUFF(Newline, "newline") \
TOKEN_STUFF(Eof, "EOF") \
TOKEN_STUFF(Bad, "Bad")



#define LIST_OF_EQUATE_DIRECTIVE_TOKENS(TOKEN_STUFF) \
TOKEN_STUFF(DotEquate, ".equate") \
TOKEN_STUFF(DotEqu, ".equ") \


#define LIST_OF_DIRECTIVE_TOKENS(TOKEN_STUFF) \
TOKEN_STUFF(DotOrg, ".org") \
TOKEN_STUFF(DotB, ".db") \
TOKEN_STUFF(DotW, ".dw") \
LIST_OF_EQUATE_DIRECTIVE_TOKENS(TOKEN_STUFF) \
TOKEN_STUFF(DotDef, ".def") \
TOKEN_STUFF(DotDefined, ".defined") \
TOKEN_STUFF(DotNot, ".not") \
TOKEN_STUFF(DotIf, ".if") \
TOKEN_STUFF(DotElseIf, ".elseif") \
TOKEN_STUFF(DotElse, ".else") \
TOKEN_STUFF(DotEndIf, ".endif") \



#define LIST_OF_TOKENS(TOKEN_STUFF) \
LIST_OF_PUNCT_TOKENS(TOKEN_STUFF) \
LIST_OF_OPERATOR_TOKENS(TOKEN_STUFF) \
LIST_OF_EXTRA_TOKENS(TOKEN_STUFF) \
LIST_OF_DIRECTIVE_TOKENS(TOKEN_STUFF)


namespace flare32
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
	//#define VARNAME(some_tok) some_tok,
	//#define VALUE(some_str) 

	//static const Tok LIST_OF_TOKENS(VARNAME, VALUE) Dummy;

	//#undef VARNAME
	//#undef VALUE

	#define TOKEN_STUFF(varname, value) varname, 

	static const Tok LIST_OF_TOKENS(TOKEN_STUFF) Dummy;

	#undef TOKEN_STUFF

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

	inline Tok(const Tok& to_copy) = default;
	inline Tok(Tok&& to_move) = default;
	inline Tok& operator = (const Tok& to_copy) = default;
	inline Tok& operator = (Tok&& to_move) = default;


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
