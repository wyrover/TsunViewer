#include "common.hpp"

#include <sys/stat.h>

#include <fstream>
#include <stdexcept>
#include <streambuf>
#include <string>

std::string readFile(const std::string& path)
{
	std::ifstream in(path, std::ios::in | std::ios::binary);
	if (in) {
		return (std::string((std::istreambuf_iterator<char>(in)), 
			std::istreambuf_iterator<char>()));
	} else {
		throw std::runtime_error(
			"File read failed: " + path
		);
	}
}

void writeFile(const std::string& path, const std::string& contents)
{
	std::ofstream fout(path);
	fout << contents;
}

// by PherricOxide via http://stackoverflow.com/a/12774387
bool fileExists(const std::string& path)
{
	struct stat buffer;   
	return (stat(path.c_str(), &buffer) == 0); 
}
