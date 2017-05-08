#include "parser_class.hpp"

namespace assembler
{


parser::parser( int argc, char** argv, std::FILE* s_infile )
	: infile(s_infile), lex( s_infile, &we, &internal_pass, &sym_tbl )
{
	internal_args_vec.clear();
	we.init(&lex);
	
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

}
