#ifndef warn_error_stuff_hpp
#define warn_error_stuff_hpp

#include "misc_includes.hpp"

namespace assembler
{

class warn_error
{
private:		// variables
	size_t* internal_pass;
	
	
private:		// functions
	gen_setter_by_val(pass);
	
	inline size_t pass() const
	{
		return *internal_pass;
	}
	
public:		// functions
	inline warn_error( auto s_pass )
	{
		set_pass(s_pass);
	}
	virtual inline ~warn_error()
	{
	}
	
	void warn( const std::string& msg );
	
	inline void warn1( const std::string& msg )
	{
		if ( pass() == 1 )
		{
			warn(msg);
		}
	}
	
	void error( const std::string& msg );
}



}

#endif		// warn_error_stuff_hpp
