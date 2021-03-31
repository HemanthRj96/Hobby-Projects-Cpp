#include"TetrisEngine.h"

std::ostream& operator<<(std::ostream& os, const BlockMatrix& obj)
{
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
			os << obj.matrix[i][j] << ' ';
		os << std::endl;
	}
	return os;
}

void Screen::InitScreen()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	// Setup the console
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	for(int i = 0; i < (m_ScreenWidth * m_ScreenHeight); i++)
		m_ScreenBuffer[i] = L' ';
}

wchar_t* Screen::GetScreenBuffer()
{
	return m_ScreenBuffer;
}

wchar_t& Screen::operator()(int x, int y)
{
	return m_ScreenBuffer[y * m_ScreenWidth + x];
}

void Screen::RefreshScreen()
{
	DWORD dwByteSize = 0;
	WriteConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), m_ScreenBuffer, m_ScreenWidth * m_ScreenHeight, { 0,0 }, &dwByteSize);
}

void Screen::DrawBoundary(const Coords& start, const Coords& end, const char* boundary, bool replaceCorner, const char* corner, bool shouldRefresh)
{
	Screen& m_Screen = *this;

	for(int i = 0; i < abs(start.x - end.x) + 1; ++i)
	{
		m_Screen(start.x + i, start.y) = *boundary;
		m_Screen(start.x + i, end.y) = *boundary;
	}
	for(int i = 0; i < abs(start.y - end.y) + 1; ++i)
	{
		m_Screen(start.x, start.y + i) = *boundary;
		m_Screen(end.x, start.y + i) = *boundary;
	}
	if(replaceCorner)
	{
		m_Screen(start.x, start.y) = *corner;
		m_Screen(start.x, end.y) = *corner;
		m_Screen(end.x, end.y) = *corner;
		m_Screen(end.x, start.y) = *corner;
	}

	if(shouldRefresh)
		m_Screen.RefreshScreen();
}

void Screen::DrawLine(const Coords& start, const Coords& end, const char* symbol)
{
	Screen& screen = *this;
	double slope;
	double denominator = (double)(start.x - end.x);
	double numerator = (double)(start.y - end.y);

	if(denominator == 0)
	{
		slope = 1;
		for(int i = 0; start.y + i != end.y; ++i)
			screen(start.x, start.y + i) = *symbol;
	}
	else
	{
		slope = numerator / denominator;
		for(int i = 0; i < abs(denominator); ++i)
		{
			int x = start.x + i;
			int y = ((x - start.x) * slope) + start.y;
			screen(x, y) = *symbol;
		}
	}

	

	screen.RefreshScreen();
}