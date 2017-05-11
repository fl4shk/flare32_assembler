#ifndef assembler_class_hpp
#define assembler_class_hpp

#include "lexer_class.hpp"
#include "instruction_table_class.hpp"


namespace navichip32
{


class assembler
{
private:		// types
	class real_iarg
	{
	public:		// variables
		tok nextt;
		s32 nextval;
		symbol* nextsym;
		
	public:		// functions
		inline real_iarg()
		{
		}
		inline real_iarg( const real_iarg& to_copy ) = default;
		inline real_iarg( const lexer& lex, bool use_special )
		{
			init( lex, use_special );
		}
		
		
		inline real_iarg& operator = ( const real_iarg& to_copy ) 
			= default;
		
		inline bool comp_nextt( tok_defn td ) const
		{
			return ( nextt == static_cast<tok>(td) );
		}
		
		inline void init( const lexer& lex, bool use_special )
		{
			if (!use_special)
			{
				nextt = lex.nextt();
				nextval = lex.nextval();
				nextsym = lex.nextsym();
			}
			else // if (use_special)
			{
				nextt = lex.special_nextt();
				nextval = lex.special_nextval();
				nextsym = lex.special_nextsym();
			}
		}
	};
	
private:		// variables
	std::vector<string_view> internal_args_vec;
	size_t internal_pass = 0;
	
	// Code generator stuff
	unsigned int internal_lc = 0;
	unsigned int internal_last_lc = -1;
	bool internal_changed = false;
	
	
	// Input file
	std::FILE* infile;
	
	// Class instances
	lexer lex;
	warn_error we;
	symbol_table user_sym_tbl;
	symbol_table special_sym_tbl;
	instruction_table instr_tbl;
	
	
	
private:		// functions
	gen_setter_by_val(pass);
	gen_setter_by_val(lc);
	gen_setter_by_val(last_lc);
	gen_setter_by_val(changed);
	
	// Constructor stuff
	void insert_grp_0_instructions();
	void insert_grp_1_instructions();
	void insert_grp_2_instructions();
	void insert_grp_3_instructions();
	
	// Code generator stuff
	void genb( s32 v );
	void gen( s32 v );
	
	
	// Parser stuff
	inline bool at_end_of_line() const
	{
		return ( !( ( lex.nextc() != '\n' ) && ( lex.nextc() != EOF )
			&& ( lex.nextt() != '\n' ) ) );
	}
	const instruction* determine_instr( std::vector<real_iarg>& iarg_vec );
	//bool instr_compat_with_iargs( const instruction& some_instr, 
	//	const std::vector<real_iarg>& iarg_vec );
	bool test_iargs( const instruction& iter, 
		std::vector<real_iarg>& iarg_vec );
	
	bool test_instr_noargs( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_ra( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_ra_rb( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_ra_imm16u( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_imm16u( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_imm16s( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_branchoffset( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_flags( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_ra_flags( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_flags_ra( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_ira( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_ira_ra( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_ra_ira( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_ra_pc( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_ra_rb_imm16u( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_ra_rb_imm16s( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_ra_rb_rc_imm12s( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_ra_rb_rc( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	bool test_instr_ra_rb_abs( const instruction& iter,
		std::vector<real_iarg>& iarg_vec );
	
	
	s32 unary( bool use_special, bool keep_lineno=false );
	s32 expr( bool use_special, bool keep_lineno=false );
	
	s32 mask_immed( s32 to_mask, size_t mask );
	
	s32 reg( bool keep_lineno=false, bool* did_fail=nullptr, 
		bool allow_fail=false );
	
	s32 braoffs( bool keep_lineno=false, bool* did_fail=nullptr, 
		bool allow_fail=false );
	s32 immed16( bool keep_lineno=false, bool* did_fail=nullptr, 
		bool allow_fail=false );
	s32 immed12( bool keep_lineno=false, bool* did_fail=nullptr, 
		bool allow_fail=false );
	inline s32 absolute( bool use_special, bool keep_lineno=false )
	{
		return expr( use_special, keep_lineno );
	}
	s32 line();
	
	inline void lex_keep_lineno()
	{
		lex(true);
	}
	
	inline bool lex_match_keep_lineno( tok typ )
	{
		return lex.match( typ, true );
	}
	
	
public:		// functions
	assembler( int argc, char** argv, std::FILE* s_infile );
	
	virtual ~assembler();
	
	int run();
	
	
	gen_getter_by_con_ref(args_vec);
	gen_getter_by_val(pass);
	gen_getter_by_val(lc);
	gen_getter_by_val(last_lc);
	gen_getter_by_val(changed);
	
};



}


#endif		// assembler_class_hpp
