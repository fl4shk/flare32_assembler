#ifndef assembler_class_hpp
#define assembler_class_hpp


#include "misc_includes.hpp"


#include "symbol_table_class.hpp"
#include "define_table_class.hpp"

#include "parse_node_class.hpp"
#include "lexer_class.hpp"
#include "code_generator_class.hpp"


namespace flare32
{

class Assembler
{
private:		// variables
	// Arbitrary number
	static constexpr size_t define_expand_max_depth = 9001;
	//static constexpr size_t define_expand_max_depth = 256;
	//static constexpr size_t define_expand_max_depth = 4;
	static constexpr s32 last_pass = 2;
	WarnError __we;
	SymbolTable __builtin_sym_tbl, __user_sym_tbl;
	DefineTable __define_tbl;
	InstructionTable __instr_tbl;
	Lexer __lexer;
	CodeGenerator __codegen;

	std::vector<std::string> __lines;


	// Where are we in the generated binary?
	size_t __addr = 0, __last_addr = -1;

	// Where are we in the file?
	size_t __line_num = 0;

	int __next_char = ' ';
	PTok __prev_tok = nullptr, __next_tok = nullptr;
	std::string __next_sym_str;
	s64 __next_num = -1;

	bool __changed = false;
	s32 __pass = 0;

	char* __input_filename = nullptr;
	std::FILE* __infile = nullptr;

public:		// functions
	Assembler(char* s_input_filename);

	int operator () ();



private:		// functions
	gen_getter_by_ref(builtin_sym_tbl);
	gen_getter_by_ref(user_sym_tbl);
	gen_getter_by_ref(define_tbl);
	gen_getter_by_ref(instr_tbl);

	gen_getter_by_ref(we);

	gen_getter_and_setter_by_val(addr);
	gen_getter_and_setter_by_val(last_addr);
	gen_getter_and_setter_by_val(line_num);
	gen_getter_and_setter_by_val(next_char);
	//gen_getter_and_setter_by_val(next_tok);
	gen_getter_by_val(prev_tok)
	gen_getter_by_val(next_tok)
	gen_getter_and_setter_by_con_ref(next_sym_str);
	gen_getter_and_setter_by_val(next_num);
	gen_getter_and_setter_by_val(changed);
	gen_getter_and_setter_by_val(pass);
	gen_getter_and_setter_by_val(input_filename);
	gen_getter_and_setter_by_val(infile);


	void reinit();
	void fill_builtin_sym_tbl();


	PTok set_next_tok(PTok n_next_tok)
	{
		__prev_tok = next_tok();
		__next_tok = n_next_tok;
		return next_tok();
	}




	inline void advance(size_t& some_outer_index, size_t& some_inner_index,
		bool use_lines=false)
	{
		__lexer.__advance_innards(__next_char, __next_tok,
			__next_sym_str, __next_num, __line_num, 
			some_outer_index, some_inner_index,
			(use_lines ? &__lines : nullptr));
	}
	inline void lex(size_t& some_outer_index, size_t& some_inner_index,
		bool use_lines=false)
	{
		__lexer.__lex_innards(__next_char, __next_tok, __prev_tok,
			__next_sym_str, __next_num, __line_num, 
			some_outer_index, some_inner_index,
			(use_lines ? &__lines : nullptr));
	}
	//inline void lex(size_t& some_outer_index, size_t& some_inner_index,
	//	std::vector<std::string>& some_lines)
	//{
	//	__lex_innards(__next_char, __next_tok,
	//		__next_sym_str, __next_num, __line_num, 
	//		some_outer_index, some_inner_index, &some_lines);
	//}

	void line(size_t& some_outer_index, size_t& some_inner_index, 
		bool just_find_defines=false);
	void finish_line(const std::vector<ParseNode>& some_parse_vec);

	void fill_lines();
	void find_defines();
	void expand_defines();


	bool parse_instr(PInstr instr, 
		const std::vector<ParseNode>& some_parse_vec);

	bool __parse_instr_no_args
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_uimm16
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_simm16
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_imm32
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);

	bool __parse_instr_ra
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_uimm16
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_rb
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_rb_uimm16
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_rb_simm16
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_rb_rc
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_rb_rc_simm12
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);

	bool __parse_instr_ldst_ra_rb
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ldst_ra_rb_rc_simm12
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ldst_ra_rb_rc
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ldst_ra_rb_simm12
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);


	bool __parse_instr_branch
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);


	bool __parse_instr_ldst_ra_rb_imm32
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_rb_imm32
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);


	// Block moves (ldmia, stmia, stmdb) with number of {} args
	bool __parse_instr_ldst_block_1_to_4
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ldst_block_5_to_8
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);

	bool __parse_instr_ira
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_ira
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ira_ra
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);

	bool __parse_instr_ra_flags
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_flags
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_flags_ra
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);

	bool __parse_instr_ra_pc
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);


	s64 handle_term(const std::vector<ParseNode>& some_parse_vec, 
		size_t& index);
	s64 handle_factor(const std::vector<ParseNode>& some_parse_vec, 
		size_t& index);
	s64 handle_expr(const std::vector<ParseNode>& some_parse_vec, 
		size_t& index);

	bool tok_is_punct(PTok some_tok) const;
	bool tok_is_ident_ish(PTok some_tok) const;
	bool tok_is_comment(PTok some_tok) const;

	//inline bool next_tok_is_punct() const
	//{
	//	return tok_is_punct(next_tok());
	//}
	//inline bool next_tok_is_ident_ish() const
	//{
	//	return tok_is_ident_ish(next_tok());
	//}

	
	void split(std::vector<ParseNode>& ret, 
		std::vector<std::string>& to_split,
		std::vector<ParsePos>* pos_vec=nullptr);
	//void expand_single_define(std::string& iter, const Define& defn);




	bool __check_tokens_innards
		(const std::vector<ParseNode>& some_parse_vec, size_t index, 
		PTok tok) const
	{
		return (some_parse_vec.at(index).next_tok == tok);
	}

	inline bool check_tokens(const std::vector<ParseNode>& some_parse_vec,
		size_t& index) const
	{
		return true;
	}

	template<typename... RemArgTypes>
	bool check_tokens(const std::vector<ParseNode>& some_parse_vec,
		size_t& index, PTok tok, RemArgTypes&&... rem_args) const
	{
		if (__check_tokens_innards(some_parse_vec, index++, tok))
		{
			return check_tokens(some_parse_vec, index, rem_args...);
		}

		return false;
	}



};

}

#endif		// assembler_class_hpp
