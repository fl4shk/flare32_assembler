//#include "lexer_class.hpp"
#include "assembler_class.hpp"
#include "get_copy_of_stdin.hpp"


int main( int argc, char** argv )
{
	//std::FILE* copy_of_stdin = navichip32::get_copy_of_stdin();
	navichip32::assembler the_assembler( argc, argv,
		navichip32::get_copy_of_stdin() );
	
	//std::FILE* copy_of_stdin = navichip32::get_copy_of_stdin();
	//navichip32::assembler the_assembler( argc, argv, stdin );
	
	return the_assembler.run();
}
