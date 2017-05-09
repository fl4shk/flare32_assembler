#ifndef instruction_table_class_hpp
#define instruction_table_class_hpp

#include "token_stuff_etc.hpp"

namespace navichip32
{

class symbol;

class instruction
{
private:		// variables
	// Symbol table entry
	symbol* internal_sym = nullptr;
	
	// Instruction encoding group
	size_t internal_grp = -1;
	
	// Instruction arguments
	instr_args internal_iargs = instr_args::noargs;
	
	
private:		// functions
	gen_setter_by_val(sym);
	gen_setter_by_val(grp);
	gen_setter_by_val(iargs);
	
	
public:		// functions
	inline instruction()
	{
	}
	inline instruction( const instruction& to_copy ) = default;
	inline instruction( symbol* s_sym, size_t s_grp, instr_args s_iargs )
	{
		set_sym(s_sym);
		set_grp(s_grp);
		set_iargs(s_iargs);
	}
	
	virtual inline ~instruction()
	{
	}
	
	inline instruction& operator = ( const instruction& to_copy ) 
		= default;
	
	
	gen_getter_by_val(sym);
	gen_getter_by_val(grp);
	gen_getter_by_val(iargs);
	
};

class instruction_table
{
private:		// variables
	
	//std::unordered_set<instruction> internal_
	
public:		// functions
	
};



}

#endif		// instruction_table_class_hpp
