#pragma once
#include <iostream>
#include <conio.h>

////////////////////////
//returns twice in school comp
class IntInput
{

public:
	///////////////////////////////
	//returns int between 0 and max
	unsigned int GetInput(unsigned int max)
	{
		unsigned int input;


		input = _getwch() - '0';

		if (input > max || input < 0)
		{
			std::cout << "Not an option\n";


			input = GetInput(max);
		}

		return input;
	}

	int Pause()
	{
		return _getwch() - '0';
	}

};

