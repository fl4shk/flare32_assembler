#ifndef assembler_class_hpp
#define assembler_class_hpp

#include "lexer_class.hpp"
#include "instruction_table_class.hpp"


namespace navichip32
{

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
	inline real_iarg( tok s_nextt, s32 s_nextval )
	{
		init( s_nextt, s_nextval );
	}
	
	
	inline real_iarg& operator = ( const real_iarg& to_copy ) 
		= default;
	
	inline bool comp_nextt( tok_defn typ ) const
	{
		return ( nextt == static_cast<tok>(typ) );
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
	
	inline void init( tok s_nextt, s32 s_nextval )
	{
		nextt = s_nextt;
		nextval = s_nextval;
		nextsym = nullptr;
	}
};

class assembler
{
private:		// variables
	std::vector<string_view> internal_args_vec;
	size_t internal_pass = 0;
	
	// Code generator stuff
	s32 internal_lc = 0;
	s32 internal_last_lc = -1;
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
	//inline bool at_end_of_line() const
	//{
	//	return ( !( ( lex.nextc() != '\n' ) && ( lex.nextc() != EOF )
	//		&& ( lex.nextt() != '\n' ) ) );
	//}
	const instruction* determine_instr();
	bool handle_iargs( const instruction& iter, bool just_test,
		std::vector<real_iarg>& iarg_vec );
	
	inline void set_did_fail( bool* did_fail, bool val )
	{
		if ( did_fail != nullptr )
		{
			*did_fail = val;
		}
	}
	
	bool handle_iarg_reg( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_iarg_reg_flags( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_iarg_reg_ira( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_iarg_reg_pc( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_iarg_braoffs( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_iarg_immed16( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_iarg_immed12( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_iarg_abs( bool just_test,
		std::vector<real_iarg>& iarg_vec );
	
	
	bool handle_instr_noargs( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_ra( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_ra_rb( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_ra_imm16u( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_imm16u( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_imm16s( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_branchoffset( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_flags( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_ra_flags( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_flags_ra( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_ira( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_ira_ra( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_ra_ira( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_ra_pc( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_ra_rb_imm16u( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_ra_rb_imm16s( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_ra_rb_rc_imm12s( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_ra_rb_rc( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	bool handle_instr_ra_rb_abs( bool just_test, 
		std::vector<real_iarg>& iarg_vec );
	
	
	s32 unary( bool use_special, bool just_test, bool* did_fail );
	s32 expr( bool use_special, bool just_test, bool* did_fail, 
		bool did_init=true );
	
	s32 mask_immed( s32 to_mask, size_t mask );
	
	s32 iarg_specific_reg( tok_defn typ, const string_view& fail_msg, 
		bool just_test=false, bool* did_fail=nullptr );
	inline s32 iarg_reg( bool just_test=false, bool* did_fail=nullptr )
	{
		return iarg_specific_reg( tok_defn::reg, "register", just_test,
			did_fail );
	}
	inline s32 iarg_reg_flags( bool just_test=false, 
		bool* did_fail=nullptr )
	{
		return iarg_specific_reg( tok_defn::reg_flags, "flags", just_test, 
			did_fail );
	}
	inline s32 iarg_reg_ira( bool just_test=false, 
		bool* did_fail=nullptr )
	{
		return iarg_specific_reg( tok_defn::reg_ira, "ira", just_test, 
			did_fail );
	}
	inline s32 iarg_reg_pc( bool just_test=false, 
		bool* did_fail=nullptr )
	{
		return iarg_specific_reg( tok_defn::reg_pc, "pc", just_test, 
			did_fail );
	}
	
	s32 iarg_braoffs( bool just_test=false, bool* did_fail=nullptr );
	s32 iarg_immed16( bool just_test=false, bool* did_fail=nullptr );
	s32 iarg_immed12( bool just_test=false, bool* did_fail=nullptr );
	inline s32 iarg_abs( bool just_test=false, bool* did_fail=nullptr )
	{
		return expr( false, just_test, did_fail );
	}
	
	inline tok cast_typ( tok_defn typ ) const
	{
		return static_cast<tok>(typ);
	}
	void line();
	
	inline void lex_regular()
	{
		lex(false);
	}
	inline void lex_keep_lineno()
	{
		lex(true);
	}
	inline bool lex_match_regular( tok typ )
	{
		return lex.match( typ, false );
	}
	//inline bool lex_match_just_test( tok typ )
	//{
	//	return lex.match( typ, true );
	//}
	inline void lex_assume_regular( tok typ )
	{
		lex.assume( typ, false );
	}
	//inline void lex_assume_keep_lineno( tok typ )
	//{
	//	lex.assume( typ, true );
	//}
	
	
	
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
