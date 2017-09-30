#ifndef tokens_and_stuff_hpp
#define tokens_and_stuff_hpp

#include "misc_includes.hpp"


#define LIST_OF_COMMENT_TOKENS(VARNAME, VALUE) \
VARNAME(Semicolon) VALUE(";") \
VARNAME(At) VALUE("@") \

#define LIST_OF_PUNCT_TOKENS(VARNAME, VALUE) \
/* "." */ \
VARNAME(Period) VALUE(".") \
\
/* "(", ")" */ \
VARNAME(LParen) VALUE("(") \
VARNAME(RParen) VALUE(")") \
\
/* "[", "]" */ \
VARNAME(LBracket) VALUE("[") \
VARNAME(RBracket) VALUE("]") \
\
/* "{", "}" */ \
VARNAME(LBrace) VALUE("{") \
VARNAME(RBrace) VALUE("}") \
\
/* "=", ";", ",", etc. */ \
VARNAME(Equals) VALUE("=") \
LIST_OF_COMMENT_TOKENS(VARNAME, VALUE) \
VARNAME(Comma) VALUE(",") \
VARNAME(Colon) VALUE(":") \




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
VARNAME(RegPc) VALUE("PC") \
VARNAME(RegIra) VALUE("IRA") \
VARNAME(RegFlags) VALUE("Flags") \
VARNAME(Ident) VALUE("Identifier")

#define LIST_OF_EXTRA_TOKENS(VARNAME, VALUE) \
/* "Number" */ \
VARNAME(NatNum) VALUE("NaturalNumber") \
\
LIST_OF_IDENT_ISH_TOKENS(VARNAME, VALUE) \
\
/* "Newline", "EOF", "Bad" */ \
VARNAME(Newline) VALUE("newline") \
VARNAME(Eof) VALUE("EOF") \
VARNAME(Bad) VALUE("Bad")


#define LIST_OF_DIRECTIVE_TOKENS(VARNAME, VALUE) \
VARNAME(DotOrg) VALUE(".org") \
VARNAME(DotB) VALUE(".db") \
VARNAME(DotW) VALUE(".dw") \
VARNAME(DotDefine) VALUE(".define") \
VARNAME(DotDefn) VALUE(".defn") \



#define LIST_OF_TOKENS(VARNAME, VALUE) \
LIST_OF_PUNCT_TOKENS(VARNAME, VALUE) \
LIST_OF_OPERATOR_TOKENS(VARNAME, VALUE) \
LIST_OF_EXTRA_TOKENS(VARNAME, VALUE) \
LIST_OF_DIRECTIVE_TOKENS(VARNAME, VALUE)


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
