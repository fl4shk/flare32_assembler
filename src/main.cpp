#include "misc_includes.hpp"
#include "assembler_class.hpp"

flare32::Assembler assembler;


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printerr("Usage:  ", argv[0], " input_file\n");
		exit(1);
	}

	assembler.init(argv[1]);
	return assembler();
}
