#include <iostream>
#include "time.h"
#include "Days.h"

int main()
{
	srand((unsigned int)time(NULL));

	Days Loop;

	if (Loop.Intro() == true)
		while (Loop.PlayerHome() == true) //all the magic
		{
		};
	return 0;
}