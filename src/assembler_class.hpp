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
	const instruction* determine_instr();
	bool test_iargs( const instruction& iter );
	
	inline bool test_iarg_reg()
	{
		bool did_fail;
		reg( true, &did_fail, true );
		return !did_fail;
	}
	bool test_iarg_immed16()
	{
		bool did_fail;
		immed16( true, &did_fail, true );
		return !did_fail;
	}
	
	bool test_instr_noargs();
	bool test_instr_ra();
	bool test_instr_ra_rb();
	bool test_instr_ra_imm16u();
	bool test_instr_imm16u();
	bool test_instr_imm16s();
	bool test_instr_branchoffset();
	bool test_instr_flags();
	bool test_instr_ra_flags();
	bool test_instr_flags_ra();
	bool test_instr_ira();
	bool test_instr_ira_ra();
	bool test_instr_ra_ira();
	bool test_instr_ra_pc();
	bool test_instr_ra_rb_imm16u();
	bool test_instr_ra_rb_imm16s();
	bool test_instr_ra_rb_rc_imm12s();
	bool test_instr_ra_rb_rc();
	bool test_instr_ra_rb_abs();
	
	
	s32 unary( bool use_special, bool keep_lineno, bool* did_fail, 
		bool allow_fail );
	s32 expr( bool use_special, bool keep_lineno, bool* did_fail, 
		bool allow_fail, bool did_init=true );
	
	s32 mask_immed( s32 to_mask, size_t mask );
	
	s32 reg( bool keep_lineno=false, bool* did_fail=nullptr, 
		bool allow_fail=false );
	
	s32 braoffs( bool keep_lineno=false, bool* did_fail=nullptr, 
		bool allow_fail=false );
	s32 immed16( bool keep_lineno=false, bool* did_fail=nullptr, 
		bool allow_fail=false );
	s32 immed12( bool keep_lineno=false, bool* did_fail=nullptr, 
		bool allow_fail=false );
	inline s32 absolute( bool use_special, bool keep_lineno=false,
		bool* did_fail=nullptr, bool allow_fail=false )
	{
		return expr( use_special, keep_lineno, did_fail, allow_fail );
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
	inline void lex_assume_keep_lineno( tok typ )
	{
		lex.assume( typ, true );
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
