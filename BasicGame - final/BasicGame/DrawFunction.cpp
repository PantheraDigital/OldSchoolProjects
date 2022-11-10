#include "DrawFunction.h"

#include <iostream>
#include <io.h>//setmode
#include <fcntl.h>//_O_ codes

Draw::Draw()
	:m_yMax(0)
	, m_hOutput(GetStdHandle(STD_OUTPUT_HANDLE))
	, m_coord({0,0})
{
	UpdatePos();
}

void Draw::UpdatePos()
{
	POINT pos;
	if (GetCursorPos(&pos))
	{
		m_coord.X = static_cast<short>(pos.x);
		m_coord.Y = static_cast<short>(pos.y);
	}
}


////////////////////////////////////
//print char at location on screen
//////////////////////////////////
void Draw::operator()(char disp, int x, int y)
{
	m_coord = { (short)x, (short)y };
	SetConsoleCursorPosition(m_hOutput, m_coord);
	char buff[1]{ disp };

	//draw buff to consol
	WriteConsoleA(m_hOutput, buff, 1, NULL, NULL);

}
///////////////////////////
//loop through and display string starting at location
////////////////////////////
void Draw::operator()(std::string disp, int x, int y)
{
	for (unsigned int i = 0; i < disp.length(); ++i)
	{
		(*this)(disp[i], x + i, y);
	}
}
/////////////////////////////
//make int into string then print
///////////////////////////////
void Draw::operator()(int disp, int x, int y)
{
	std::string val = std::to_string(disp);
	(*this)(val, x, y);
}



void Draw::operator()(char disp)
{
	UpdatePos();
	(*this)(disp, m_coord.X, m_coord.Y);
}

void Draw::operator()(std::string disp)
{
	UpdatePos();
	(*this)(disp, m_coord.X, m_coord.Y);
}

void Draw::operator()(int disp)
{
	UpdatePos();
	(*this)(disp, m_coord.X, m_coord.Y);
}


////////////////////////////////
//print char with color
/////////////////////////////////
void Draw::operator()(char disp, int x, int y, int color)
{
	SetConsoleTextAttribute(m_hOutput, color);//set color
	(*this)(disp, x, y);
	SetConsoleTextAttribute(m_hOutput, LIGHTGREY);//set back to default color
}


/////////////////////////////
//print wide char at location
////////////////////////////////
void Draw::operator()(wchar_t disp, int x, int y)
{
	_setmode(_fileno(stdout), _O_WTEXT);

	m_coord = { (short)x, (short)y };
	SetConsoleCursorPosition(m_hOutput, m_coord);
	wchar_t buff[1]{ disp };

	WriteConsoleW(m_hOutput, buff, 1, NULL, NULL);

	_setmode(_fileno(stdout), _O_TEXT);
}

void Draw::operator()(wchar_t disp)
{
	UpdatePos();
	(*this)(disp, m_coord.X, m_coord.Y);
}

/////////////////////////////////
//print wide char with color
///////////////////////////////
void Draw::operator()(wchar_t disp, int x, int y, int color)
{
	SetConsoleTextAttribute(m_hOutput, color);
	(*this)(disp, x, y);
	SetConsoleTextAttribute(m_hOutput, LIGHTGREY);
}