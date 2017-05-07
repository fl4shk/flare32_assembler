#include "get_copy_of_stdin.hpp"


namespace assembler
{

std::FILE* get_copy_of_stdin()
{
	std::FILE* copy_of_stdin = std::tmpfile();
	
	int c = ' ';
	
	while ( c != EOF )
	{
		c = std::getc(stdin);
		
		if ( c != EOF )
		{
			std::putc( c, copy_of_stdin );
		}
	}
	
	std::rewind(copy_of_stdin);
	
	
	return copy_of_stdin;
}


}
