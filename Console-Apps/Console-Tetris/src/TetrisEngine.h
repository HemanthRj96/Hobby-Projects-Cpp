#include<iostream>
#include<windows.h>
#include<vector>

struct Coords
{
	int x, y;
};


struct BlockMatrix
{

	bool matrix[3][3];

	BlockMatrix(std::initializer_list<bool> list)
	{
		auto temp = list.begin();

		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j)
				matrix[i][j] = *(temp + (i * 3 + j));
	}

	bool& operator()(int first, int second) { return matrix[first][second]; }

	friend std::ostream& operator<<(std::ostream& os, const BlockMatrix& obj);
};


class Screen
{
	wchar_t* m_ScreenBuffer;
	const int m_ScreenWidth;
	const int m_ScreenHeight;
	std::vector<Coords> m_boundaries;

public:
	Screen(const int& screenHeight, const int& screenWidth) 
		:m_ScreenBuffer{ new wchar_t[screenHeight * screenWidth] }, m_ScreenWidth{ screenWidth }, m_ScreenHeight{ screenHeight } 
	{  
		//Initialize screen
		InitScreen();
	}

	~Screen() { delete[] m_ScreenBuffer; }

	void InitScreen();

	wchar_t* GetScreenBuffer();

	wchar_t& operator()(int x, int y);

	void RefreshScreen();

	void DrawBoundary(const Coords& start, const Coords& end, const char* boundary, bool replaceCorner = false, const char* corner = new const char{ '*' }, bool shouldRefresh = true);

	void DrawLine(const Coords& start, const Coords& end, const char* symbol);
};


class TetrisEngine
{
private:

	Screen m_Screen;
	int m_Score;
	std::string m_PlayerName;
	const BlockMatrix m_Blocks[8] = {{1,0,0,0,1,0,0,0,1},
									 {1,0,0,0,1,0,0,0,1},
									 {1,0,0,0,1,0,0,0,1},
									 {1,0,0,0,1,0,0,0,1},
									 {1,0,0,0,1,0,0,0,1},
									 {1,0,0,0,1,0,0,0,1},
									 {1,0,0,0,1,0,0,0,1},
									 {1,0,0,0,1,0,0,0,1}};

public:

	TetrisEngine(int screenHeight, int screenWidth, std::string playerName)
		:m_Screen{ Screen(screenHeight, screenWidth) }, m_Score{}, m_PlayerName{ playerName } { }

	

};