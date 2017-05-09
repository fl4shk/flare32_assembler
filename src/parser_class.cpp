#include "parser_class.hpp"

namespace navichip32
{


parser::parser( int argc, char** argv, std::FILE* s_infile )
	: infile(s_infile), lex( s_infile, &we, &internal_pass, &sym_tbl ),
	we(&lex)
{
	internal_args_vec.clear();
	
	for ( int i=0; i<argc; ++i )
	{
		internal_args_vec.push_back(string_view(argv[i]));
	}
}

parser::~parser()
{
}

int parser::run()
{
	
	return 0;
}

s32 parser::expr()
{
	
}

s32 parser::unary()
{
	
}


s32 parser::reg()
{
}
s32 parser::immed16u()
{
}
s32 parser::immed16s()
{
}
s32 parser::immed12s()
{
}
s32 parser::absolute()
{
}
s32 parser::line()
{
}


}
