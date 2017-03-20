#include <iostream>
#include <chrono>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << "<prog> <args..>\n";
		return -1;
	}
	std::string prog = argv[1];
	std::cout << "Running with args: " << prog.c_str() << "\n\n";
	std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now(), end;
	std::system(prog.c_str());
	end = std::chrono::steady_clock::now();
	std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds\n";
	return 0;
}