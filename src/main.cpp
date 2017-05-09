//#include "lexer_class.hpp"
#include "parser_class.hpp"
#include "get_copy_of_stdin.hpp"


int main( int argc, char** argv )
{
	//std::FILE* copy_of_stdin = navichip32::get_copy_of_stdin();
	navichip32::parser the_parser( argc, argv,
		navichip32::get_copy_of_stdin() );
	
	return the_parser.run();
}
