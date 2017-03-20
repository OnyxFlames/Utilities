#include <iostream>
#include <cstring>

#include "FileManager.hpp"

int main(int argc, char* argv[])
{
	FileManager fm;
	if (argc < 3)
	{
		std::cerr << "[Debug]Usage: " << argv[0] << " <backup/restore/find/delete/diff> <file>\n";
		return -1;
	}
	// Mode switching
	if (std::strcmp(argv[1], "backup") == 0)
	{
		fm.backup(argv[2]);
	}
	else if (std::strcmp(argv[1], "restore") == 0)
	{
		fm.restore(argv[2]);
	}
	else if (std::strcmp(argv[1], "find") == 0)
	{
		fm.find(argv[2]);
	}
	else if (std::strcmp(argv[1], "delete") == 0)
	{
		fm.del(argv[2]);
	}
	else if (std::strcmp(argv[1], "diff") == 0)
	{
		fm.diff(argv[2]);
	}
	else if (std::strcmp(argv[1], "-i") == 0)
	{
		//fm.interactive(argv[2]);
	}
	else
	{
		std::cerr << "Option \"" << argv[1] << "\" not recognized!\nRun \"" << argv[0] << "\" for usage.";
		return -1;
	}

	return 0;
}