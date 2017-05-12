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
	
	// Opcode
	size_t internal_opcode = -1;
	
	// Instruction encoding group
	size_t internal_grp = -1;
	
	// Instruction arguments
	instr_args internal_iargs = instr_args::noargs;
	
	// If this instruction is a pseudo instruction, then encode using
	// internal_real_instr
	const instruction* internal_real_instr = nullptr;
	
	
private:		// functions
	gen_setter_by_val(real_instr);
	gen_setter_by_val(sym);
	gen_setter_by_val(opcode);
	gen_setter_by_val(grp);
	gen_setter_by_val(iargs);
	
	
public:		// functions
	inline instruction()
	{
	}
	inline instruction( const instruction& to_copy ) = default;
	inline instruction( symbol* s_sym, size_t s_opcode, size_t s_grp, 
		instr_args s_iargs, const instruction* s_real_instr )
	{
		set_sym(s_sym);
		set_opcode(s_opcode);
		set_grp(s_grp);
		set_iargs(s_iargs);
		set_real_instr(s_real_instr);
	}
	
	virtual inline ~instruction()
	{
	}
	
	inline instruction& operator = ( const instruction& to_copy ) 
		= default;
	
	
	gen_getter_by_val(sym);
	gen_getter_by_val(opcode);
	gen_getter_by_val(grp);
	gen_getter_by_val(iargs);
	gen_getter_by_val(real_instr);
	
};


class instruction_table
{
private:		// variables
	std::unordered_map< symbol*, std::vector<instruction> > 
		internal_table;
	
	
private:		// functions
	gen_getter_by_ref(table);
	
public:		// functions
	inline instruction_table()
	{
	}
	inline instruction_table( const instruction_table& to_copy ) = delete;
	virtual inline ~instruction_table()
	{
	}
	
	inline instruction_table& operator = 
		( const instruction_table& to_copy ) = delete;
	
	void enter( symbol* sym, size_t opcode, size_t grp, instr_args iargs,
		const instruction* real_instr=nullptr );
	
	inline const std::vector<instruction>& at( const symbol* where )
	{
		return table().at(const_cast<symbol*>(where));
	}
	
	gen_getter_by_con_ref(table);
	
};

}

#endif		// instruction_table_class_hpp
