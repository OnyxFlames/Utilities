#include "FileManager.hpp"
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>

const std::string backup_location = "C:\\ProgramUtils\\Fileman\\";

FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}


std::vector<std::string> FileManager::list_backups(const std::string file)
{
	namespace fs = std::experimental::filesystem;
	if (fs::exists(backup_location + file + ".store"))
	{
		std::ifstream store(backup_location + file + ".store");
		std::string buffer = "";
		std::vector<std::string> versions;
		while (std::getline(store, buffer))
		{
			versions.push_back(buffer);
		}
		store.close();
		std::cout << "Found (" << versions.size() << ") back up file(s).\n";
		uintmax_t total_size = 0;
		for (auto &v : versions)
		{
			std::cout << v << " | Size: " << fs::file_size(backup_location + v) << " bytes\n";
			total_size += fs::file_size(backup_location + v);
		}
		std::cout << "\nTotal size on disk: " << total_size << " bytes.\n";
		return versions;
	}
	return std::vector<std::string>();
}
void FileManager::backup(const std::string file)
{
	namespace fs = std::experimental::filesystem;
	// If the .store file doesn't exist
	if (!fs::exists(backup_location + file + ".store"))
	{
		// Create .store file
		std::ofstream store(backup_location + file + ".store");
		store.close();
	}
	if (!fs::exists(file))
	{
		std::cerr << "Error: \"" << file << "\" does not exist! Exiting.\n";
		std::exit(-1);
	}
	std::ifstream store(backup_location + file + ".store", std::ios::app);
	std::string buffer = "";
	std::vector<std::string> versions;
	// Count versions stored
	while (std::getline(store, buffer))
	{
		versions.push_back(buffer);
	}
	std::string backup_name = file + "." + std::to_string(versions.size()) + ".bak";
	fs::copy_file(file, backup_location + backup_name);
		
	store.close();
	std::ofstream store_w(backup_location + file + ".store", std::ios::app);
	store_w << backup_name << "\n";
	store_w.close();
	std::cout << "Backed up \"" << file << "\" as \"" << backup_name << "\" successfully.\n";
}


void FileManager::restore(const std::string file)
{
	namespace fs = std::experimental::filesystem;

	if (fs::exists(backup_location + file + ".store"))
	{
		std::ifstream store(backup_location + file + ".store");
		std::string buffer;
		std::vector<std::string> versions;
		while (std::getline(store, buffer))
		{
			versions.push_back(buffer);
		}

		// If there's only one version, just restore
		if (versions.size() == 1)
		{
			fs::copy_file(backup_location + versions.at(0), file);
		}
		else if (versions.size() > 1)
		{
			std::cout << "Select a version #: \n";
			for (uint16_t v = 0; v < versions.size(); v++)
			{
				std::cout << v << ": " << versions.at(v) << "\n";
			}
			uint16_t vernum = 0;
			std::cin >> vernum;
			if (vernum <= versions.size())
			{
				if (fs::exists(file))
				{
					char c = ' ';
					while (c != 'y' && c != 'n')
					{
						std::cout << "\"" << file << "\" already exists. Overwrite with restore? (y/n)\n";
						
						std::cin >> c;
						
						c = tolower(c);
						if (c == 'y')
							fs::remove(file);
						else if (c == 'n')
						{
							std::cout << "Restore canceled.\n";
							return;
						}
					}
				}
				fs::copy_file(backup_location + versions.at(vernum), file);
				std::cout << "Restored!\n";
			}
		}
		else
		{
			std::cerr << "Error: no back up files found. Exiting.\n";
			std::exit(-1);
		}
	}
	else
	{
		std::cerr << "Error: backup data for \"" << file << "\" wasn't found. Exiting.\n";
		std::exit(-1);
	}
}

void FileManager::find(const std::string file)
{
	namespace fs = std::experimental::filesystem;
	if (fs::exists(backup_location + file + ".store"))
	{
		std::ifstream store(backup_location + file + ".store");
		std::string buffer = "";
		std::vector<std::string> versions;
		while (std::getline(store, buffer))
		{
			versions.push_back(buffer);
		}
		std::cout << "Found (" << versions.size() << ") back up file(s).\n";
		uintmax_t total_size = 0;
		for (auto &v : versions)
		{
			std::cout << v << " | Size: " << fs::file_size(backup_location + v) << " bytes\n";
			total_size += fs::file_size(backup_location + v);
		}
		std::cout << "\nTotal size on disk: " << total_size << " bytes.\n";
	}
	else
	{
		std::cout << "No backup data found.\n";
		std::exit(-1);
	}
}

void FileManager::del(const std::string file)
{
	namespace fs = std::experimental::filesystem;
	if (fs::exists(backup_location + file + ".store"))
	{
		std::ifstream store(backup_location + file + ".store");
		std::string buffer = "";
		std::vector<std::string> versions;
		while (std::getline(store, buffer))
		{
			versions.push_back(buffer);
		}
		store.close();
		std::cout << "Found (" << versions.size() << ") back up file(s).\n";
		uintmax_t total_size = 0;
		for (auto &v : versions)
		{
			std::cout << v << " | Size: " << fs::file_size(backup_location + v) << " bytes\n";
			total_size += fs::file_size(backup_location + v);
		}
		std::cout << "\nTotal size on disk: " << total_size << " bytes.\n";
		char c = ' ';
		while (c != 'y' && c != 'n')
		{
			std::cout << "\nDelete all of these backups?(The original file will remain untouched)\ny/n\n";
			std::cin >> c;

			c = tolower(c);
			if (c == 'y')
			{
				for (const auto &v : versions)
				{
					std::cout << "Deleting " << v << "\n";
					fs::remove(backup_location + v);
				}
				fs::remove(backup_location + file + ".store");
				std::cout << "Deleting " << file + ".store" << "\n";
			}
			else if (c == 'n')
			{
				std::cout << "Delete canceled.\n";
				return;
			}
		}
	}
}

void FileManager::diff(const std::string file)
{
	namespace fs = std::experimental::filesystem;
	bool diff_found = false;
	if (fs::exists(backup_location + file + ".store"))
	{
		std::ifstream store(backup_location + file + ".store");
		std::string buffer = "";
		std::vector<std::string> versions;
		while (std::getline(store, buffer))
		{
			versions.push_back(buffer);
		}
		store.close();
		std::cout << "Found (" << versions.size() << ") back up file(s).\n";
		uintmax_t total_size = 0;
		for (auto &v : versions)
		{
			std::cout << v << " | Size: " << fs::file_size(backup_location + v) << " bytes\n";
			total_size += fs::file_size(backup_location + v);
		}
		std::cout << "\nTotal size on disk: " << total_size << " bytes.\n";
		std::cout << "\nDiff version #: \n";
		for (uint16_t v = 0; v < versions.size(); v++)
		{
			std::cout << v << ": " << versions.at(v) << "\n";
		}
		uint16_t vernum = 0;
		std::cin >> vernum;
		if (vernum <= versions.size())
		{
			std::ifstream origin, compare;
			origin.open(file);
			compare.open(backup_location + versions.at(vernum));
			int org(0), com(0);
			while (origin.good() && compare.good())
			{
				org = origin.get();
				com = compare.get();
				if (org != com)
				{
					diff_found = true;
					std::cout << std::hex << "0x" << ((origin.tellg() + compare.tellg()) / 2) << ": " << org << " | " << com << std::dec << "\n";
				}
			}
			while (origin.good())
			{
				org = origin.get();
				std::cout << std::hex << "0x" << origin.tellg() << ": " << org << " | " << "EOF" << std::dec << "\n";
			}
			while (compare.good())
			{
				com = compare.get();
				std::cout << std::hex << "0x" << compare.tellg() << ": " << "EOF" << " | " << com << std::dec << "\n";
			}

			if (!diff_found) std::cout << "No diff's found.\n";
		}
	}
	else
	{
		std::cerr << "Error: no files to diff. Exiting\n";
		std::exit(-1);
	}
}