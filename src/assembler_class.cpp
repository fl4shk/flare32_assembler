#include "assembler_class.hpp"

namespace navichip32
{


assembler::assembler( int argc, char** argv, std::FILE* s_infile )
	: infile(s_infile), lex( s_infile, &we, &internal_pass, &sym_tbl ),
	we(&lex)
{
	internal_args_vec.clear();
	
	for ( int i=0; i<argc; ++i )
	{
		internal_args_vec.push_back(string_view(argv[i]));
	}
}

assembler::~assembler()
{
}

int assembler::run()
{
	
	return 0;
}

s32 assembler::expr()
{
	
}

s32 assembler::unary()
{
	
}


s32 assembler::reg()
{
}
s32 assembler::immed16u()
{
}
s32 assembler::immed16s()
{
}
s32 assembler::immed12s()
{
}
s32 assembler::absolute()
{
}
s32 assembler::line()
{
}


}
