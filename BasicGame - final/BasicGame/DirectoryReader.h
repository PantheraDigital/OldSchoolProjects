#pragma once
#include <string>
#include <vector>

//gets the names of all levels in file and places them in a vector
class DirectoryReader
{
typedef std::vector<std::string> StringVec;

public:
	//places the names of files from path "name" to vector "v"
	void operator() (const std::string& name, StringVec& v);
};
