#pragma once
#include <iostream>
#include <conio.h>

////////////////////////
//returns twice in school comp
class IntInput
{

public:
	
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
	/*
	unsigned int GetInput(unsigned int max)
	{
		bool keepGoing = true;
		unsigned int input;
		std::cin.clear();
		std::cin.ignore(0);
		while (keepGoing)
		{


			if (_kbhit())
			{
				input = _getwch() - '0';


				if (input > max || input < 0)
				{
					std::cout << "Not an option\n" << input;

					input = GetInput(max);
				}

				return input;
				keepGoing = false;
			}
		}

	}*/
};

