#include "DirectoryReader.h"

#include <windows.h>


void DirectoryReader::operator() (const std::string& name, StringVec& vec)
{
	std::string pattern(name);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;

	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			vec.push_back(data.cFileName);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}

	//get rid of dots placed in vector
	vec.erase(vec.begin());
	vec.erase(vec.begin());
}