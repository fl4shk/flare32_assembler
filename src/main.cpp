#include "misc_includes.hpp"
#include "assembler_class.hpp"




int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printerr("Usage:  ", argv[0], " input_file\n");
		exit(1);
	}
	Assembler assembler(argv[1]);
	return assembler();
}
