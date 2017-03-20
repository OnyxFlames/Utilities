#pragma once
#include <fstream>
#include <filesystem>
#include <string>

class FileManager
{
private:
	std::vector<std::string> list_backups(const std::string file);
public:
	FileManager();
	~FileManager();

	void backup(const std::string file);
	void restore(const std::string file);
	void find(const std::string file);
	void del(const std::string file);
	void diff(const std::string file);
	void interactive(const std::string file);
};

