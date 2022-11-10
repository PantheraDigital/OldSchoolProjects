#pragma once
#include <conio.h>
#include <stdlib.h>

#include "Vec2.h"

/////////////////////////////
//takes user input to determin output
//////////////////////////////
Vec2 UserInput()
{
	char input = _getch();
	Vec2 result(0, 0);

	switch (input)
	{

	case 'w':
	{
		result = Vec2(0, -1);
		break;
	}

	case 'a':
	{
		result = Vec2(-1, 0);
		break;
	}

	case 's':
	{
		result = Vec2(0, 1);
		break;
	}

	case 'd':
	{
		result = Vec2(1, 0);
		break;
	}

	default:
		break;

	}

	return result;
}


//////////////////////////////////
//randomly picks output
////////////////////////////////////
Vec2 AiRandomInput()
{
	Vec2 result(0, 0);

	int input = rand() % 5;//0-3 move  4 stationary

	switch (input)
	{

	case 0:
	{
		result = Vec2(0, -1);
		break;
	}

	case 1:
	{
		result = Vec2(-1, 0);
		break;
	}

	case 2:
	{
		result = Vec2(0, 1);
		break;
	}

	case 3:
	{
		result = Vec2(1, 0);
		break;
	}

	default:
		break;

	}

	return result;
}


//////////////////////////////////
//randomly picks output
////////////////////////////////////
Vec2 AiCircleInput()
{
	static int stage = 0;

	if (stage == 4)
		stage = 0;

	Vec2 result(0, 0);

	switch (stage)
	{

	case 0:
	{
		result = Vec2(0, -1);
		break;
	}

	case 1:
	{
		result = Vec2(-1, 0);
		break;
	}

	case 2:
	{
		result = Vec2(0, 1);
		break;
	}

	case 3:
	{
		result = Vec2(1, 0);
		break;
	}

	default:
		break;

	}

	++stage;
	return result;
}
