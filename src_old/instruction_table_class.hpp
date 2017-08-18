#ifndef instruction_table_class_hpp
#define instruction_table_class_hpp

#include "token_stuff_etc.hpp"

namespace navichip32
{

class symbol;

class instruction
{
private:		// variables
	std::string internal_name;
	
	// Opcode
	size_t internal_opcode = -1;
	
	// Instruction encoding group
	size_t internal_grp = -1;
	
	// Instruction arguments
	instr_args internal_iargs = instr_args::noargs;
	
	
	// If this instruction is a pseudo instruction, then encode using a
	// different instruction
	std::string internal_real_instr_name;
	size_t internal_real_instr_index = 0;
	
	
private:		// functions
	gen_setter_by_con_ref(name);
	gen_setter_by_rval_ref(name);
	gen_setter_by_val(opcode);
	gen_setter_by_val(grp);
	gen_setter_by_val(iargs);
	gen_setter_by_con_ref(real_instr_name);
	gen_setter_by_rval_ref(real_instr_name);
	gen_setter_by_val(real_instr_index);
	
	
public:		// functions
	inline instruction()
	{
		set_opcode(-1);
		set_grp(-1);
		set_iargs(instr_args::noargs);
		set_real_instr_index(0);
	}
	inline instruction( const instruction& to_copy ) = default;
	inline instruction( instruction&& to_move ) = default;
	inline instruction( const std::string& s_name, size_t s_opcode, 
		size_t s_grp, instr_args s_iargs, 
		const std::string& s_real_instr_name, size_t s_real_instr_index )
	{
		set_name(s_name);
		set_opcode(s_opcode);
		set_grp(s_grp);
		set_iargs(s_iargs);
		set_real_instr_name(s_real_instr_name);
		set_real_instr_index(s_real_instr_index);
	}
	inline instruction( std::string&& s_name, size_t s_opcode, 
		size_t s_grp, instr_args s_iargs, 
		std::string&& s_real_instr_name, size_t s_real_instr_index )
	{
		set_name(std::move(s_name));
		set_opcode(s_opcode);
		set_grp(s_grp);
		set_iargs(s_iargs);
		set_real_instr_name(std::move(s_real_instr_name));
		set_real_instr_index(s_real_instr_index);
	}
	
	inline ~instruction()
	{
	}
	
	inline instruction& operator = ( const instruction& to_copy ) 
		= default;
	inline instruction& operator = ( instruction&& to_copy ) = default;
	
	
	gen_getter_by_con_ref(name);
	gen_getter_by_val(opcode);
	gen_getter_by_val(grp);
	gen_getter_by_val(iargs);
	gen_getter_by_con_ref(real_instr_name);
	gen_getter_by_val(real_instr_index);
	
};

inline std::ostream& operator << ( std::ostream& os, 
	const instruction& to_print )
{
	//os << std::hex << reinterpret_cast<uintptr_t>(to_print.sym()) << ", "
	//	<< std::dec 
	//	<< to_print.opcode() << ", "
	//	<< to_print.grp() << ", "
	//	<< cast_typ(to_print.iargs()) << ", "
	//	<< std::hex << reinterpret_cast<uintptr_t>(to_print.real_instr())
	//	<< std::dec;
	
	//os << std::hex 
	//	<< reinterpret_cast<uintptr_t>(to_print.sym()) << ", "
	//	<< to_print.opcode() << ", "
	//	<< to_print.grp() << ", "
	//	<< cast_typ(to_print.iargs()) << ", "
	//	<< reinterpret_cast<uintptr_t>(to_print.real_instr())
	//	<< std::dec;
	
	os << std::hex 
		<< to_print.name() << ", "
		<< to_print.opcode() << ", "
		<< to_print.grp() << ", "
		<< cast_typ(to_print.iargs()) << ", "
		<< to_print.real_instr_name() << ", "
		<< to_print.real_instr_index() << ", "
		<< std::dec;
	
	return os;
}


class instruction_table
{
private:		// variables
	std::unordered_map< std::string, std::vector<instruction> > 
		internal_table;
	
	
private:		// functions
	gen_getter_by_ref(table);
	
public:		// functions
	inline instruction_table()
	{
	}
	inline instruction_table( const instruction_table& to_copy ) = delete;
	inline ~instruction_table()
	{
	}
	
	inline instruction_table& operator = 
		( const instruction_table& to_copy ) = delete;
	
	void enter( const std::string& name, size_t opcode, size_t grp, 
		instr_args iargs, const std::string& real_instr_name="",
		size_t real_instr_index=0 );
	
	inline const std::vector<instruction>& at( const std::string& where )
	{
		return table().at(where);
	}
	
	gen_getter_by_con_ref(table);
	
};

}

#endif		// instruction_table_class_hpp
