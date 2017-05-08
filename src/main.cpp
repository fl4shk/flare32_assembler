//#include "lexer_class.hpp"
#include "parser_class.hpp"
#include "get_copy_of_stdin.hpp"


int main( int argc, char** argv )
{
	//std::FILE* copy_of_stdin = assembler::get_copy_of_stdin();
	assembler::parser the_parser( argc, argv,
		assembler::get_copy_of_stdin() );
	
	return the_parser.run();
}
