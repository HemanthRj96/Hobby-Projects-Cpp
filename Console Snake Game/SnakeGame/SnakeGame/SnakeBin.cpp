#include<iostream>
#include<Windows.h>
#include<chrono>
#include<vector>

using namespace std;

enum class Direction { up, down, left, right };
enum class Orientation { x, y };
enum class HitType { defaultNull, wall, self, fruit };
enum class Levels { unboxed, boxed, maze };

class GameManager
{

private:

	// Constant attributes
	const short m_head = 0x2592;
	const short m_tail = 0x2588;
	const short m_fruit = '#';
	const int m_screenWidth = 120;
	const int m_screenHeight = 40;
	const float m_framDelay = 60;

	// Player details
	string m_playerName;
	int m_level = 1;
	int m_score = 0;

	// Screen itself
	wchar_t* m_screen = new wchar_t[m_screenWidth * m_screenHeight];

	// Stores the snake body and the recently discarded body
	int m_startingLength = 25;
	vector<pair<int, int>> m_snakeBody;
	pair<int, int> m_discardedBody;
	pair<int, int> m_fruitPosition;

	// To know the current direction of the snake
	Direction m_cachedDirection = Direction::right;

public:

	/// <summary>
	/// To load the player data
	/// </summary>
	bool GetPlayerData()
	{
		cout << "THIS IS THE SNAKE GAME PLEASE INPUT YOUR NAME : ";
		cin >> m_playerName;
	repeat:
		cout << "INPUT YOUR DESIRED SPEED OF LEVEL (1-10): ";
		cin >> m_level;
		if(!(m_level >= 1 && m_level <= 10))
			return true;
		else
			return false;
	}

	/// <summary>
	/// To initialize settings such as console and snake settings
	/// </summary>
	void InitializeSettings(pair<int, int> spawnPoint, Levels levelType, Orientation orientation = Orientation::x)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		// Setup the console
		cursorInfo.dwSize = 1;
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

		system("cls");

		// Fill the screen based on the type of the level
		switch(levelType)
		{
			case Levels::unboxed:
				break;
			case Levels::boxed:
				break;
			case Levels::maze:
				break;
		}

		for(int i = 0; i < (m_screenWidth * m_screenHeight); i++)
			m_screen[i] = ' ';

		// Set the snake's size
		m_snakeBody.resize(m_startingLength);

		switch(orientation)
		{
			case Orientation::x:
				for(int i = 0; i < m_startingLength; ++i)
				{
					m_snakeBody.at(i).first = spawnPoint.first - i;
					m_snakeBody.at(i).second = spawnPoint.second;
				}
				break;
			case Orientation::y:
				for(int i = 0; i < m_startingLength; ++i)
				{
					m_snakeBody.at(i).first = spawnPoint.first;
					m_snakeBody.at(i).second = spawnPoint.second - i;
				}
				break;
		}
	}

	/// <summary>
	/// Adds a fruit to screen and stores the value
	/// </summary>
	void AddFruit()
	{
		while(true)
		{
		repeat:
			srand(time(nullptr));
			m_fruitPosition.first = rand() % m_screenWidth;
			m_fruitPosition.second = rand() % m_screenHeight;
			for(int i = 0; i < m_startingLength; ++i)
				if(m_snakeBody.at(i) == m_fruitPosition)
					goto repeat;
			m_screen[m_screenWidth * m_fruitPosition.second + m_fruitPosition.first] = m_fruit;
			break;
		}
	}

	/// <summary>
	/// Return the target direction of the snake
	/// </summary>
	Direction GetInput()
	{
		if(GetAsyncKeyState((unsigned short)'A') & 0x8000)
			if(m_cachedDirection == Direction::down || m_cachedDirection == Direction::up)
			{
				m_cachedDirection = Direction::left;
				return m_cachedDirection;
			}
		if(GetAsyncKeyState((unsigned short)'D') & 0x8000)
			if(m_cachedDirection == Direction::down || m_cachedDirection == Direction::up)
			{
				m_cachedDirection = Direction::right;
				return m_cachedDirection;
			}
		if(GetAsyncKeyState((unsigned short)'S') & 0x8000)
			if(m_cachedDirection == Direction::right || m_cachedDirection == Direction::left)
			{
				m_cachedDirection = Direction::down;
				return m_cachedDirection;
			}
		if(GetAsyncKeyState((unsigned short)'W') & 0x8000)
			if(m_cachedDirection == Direction::right || m_cachedDirection == Direction::left)
			{
				m_cachedDirection = Direction::up;
				return m_cachedDirection;
			}
		return m_cachedDirection;
	}

	/// <summary>
	/// Method to update the snake body, screen and console
	/// </summary>
	/// <param name="direction">The target direction towards which the snake should move</param>
	void SnakeUpdate(Direction direction)
	{
		switch(m_cachedDirection)
		{
			case Direction::up:
			{
				m_discardedBody = m_snakeBody.at(m_startingLength - 1);
				for(int i = m_startingLength - 1; i >= 0; --i)
					if((i - 1) < 0)
					{
						if(m_snakeBody.at(i).second == 0)
							m_snakeBody.at(i).second = m_screenHeight - 1;
						else
							m_snakeBody.at(i).second -= 1;
					}
					else
						m_snakeBody.at(i) = m_snakeBody.at(i - 1);
			}
			break;
			case Direction::down:
			{
				m_discardedBody = m_snakeBody.at(m_startingLength - 1);
				for(int i = m_startingLength - 1; i >= 0; --i)
					if((i - 1) < 0)
					{
						if(m_snakeBody.at(i).second == m_screenHeight - 1)
							m_snakeBody.at(i).second = 0;
						else
							m_snakeBody.at(i).second += 1;
					}
					else
						m_snakeBody.at(i) = m_snakeBody.at(i - 1);
			}
			break;
			case Direction::left:
			{
				m_discardedBody = m_snakeBody.at(m_startingLength - 1);
				for(int i = m_startingLength - 1; i >= 0; --i)
					if((i - 1) < 0)
					{
						if(m_snakeBody.at(i).first == 0)
							m_snakeBody.at(i).first = m_screenWidth - 1;
						else
							m_snakeBody.at(i).first -= 1;
					}
					else
						m_snakeBody.at(i) = m_snakeBody.at(i - 1);
			}
			break;
			case Direction::right:
			{
				m_discardedBody = m_snakeBody.at(m_startingLength - 1);
				for(int i = m_startingLength - 1; i >= 0; --i)
					if((i - 1) < 0)
					{
						if(m_snakeBody.at(i).first == m_screenWidth - 1)
							m_snakeBody.at(i).first = 0;
						else
							m_snakeBody.at(i).first += 1;
					}
					else
						m_snakeBody.at(i) = m_snakeBody.at(i - 1);
			}
			break;
		}

		for(int i = 0; i < m_startingLength; i++)
			if(i == 0)
				m_screen[int(m_screenWidth * m_snakeBody.at(i).second + m_snakeBody.at(i).first)] = m_head;
			else
				m_screen[int(m_screenWidth * m_snakeBody.at(i).second + m_snakeBody.at(i).first)] = m_tail;
		m_screen[m_screenWidth * m_discardedBody.second + m_discardedBody.first] = ' ';

		DWORD dwByteSize = 0;
		WriteConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), m_screen, m_screenWidth * m_screenHeight, {0,0}, &dwByteSize);
		Sleep(m_framDelay / m_level);
	}

	/// <summary>
	/// Return a hit type based on what the snake head is currently on
	/// </summary>
	HitType GetHitType()
	{
		// Check for fruit hit
		if(m_snakeBody.at(0) == m_fruitPosition)
		{
			++m_startingLength;
			m_snakeBody.resize(m_startingLength);
			return HitType::fruit;
		}
		// Check for self hits
		for(int i = 1; i < m_startingLength; i++)
			if(m_snakeBody.at(i) == m_snakeBody.at(0))
				return HitType::self;

		return HitType::defaultNull;
	}

	/// <summary>
	/// Updates the score value
	/// </summary>
	void ScoreUpdate(int increement = 1)
	{
		m_score += increement;
	}

	/// <summary>
	/// Simple kill effect on the snake body
	/// </summary>
	void DoKillEffect()
	{
		DWORD dwByteSize = 0;
		//Create a blinking effect
		for(int i = 0; i < 6; ++i)
		{
			for(int j = 1; j < m_startingLength; ++j)
				if(i % 2)
					m_screen[m_screenWidth * m_snakeBody.at(j).second + m_snakeBody.at(j).first] = 0x2591;
				else
					m_screen[m_screenWidth * m_snakeBody.at(j).second + m_snakeBody.at(j).first] = 0x2593;

			WriteConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), m_screen, m_screenWidth * m_screenHeight, {0,0}, &dwByteSize);
			Sleep(1000);
		}
	}

	/// <summary>
	/// Prints the end screen
	/// </summary>
	void PrintEndScreen()
	{
		system("cls");

		cout << "SORRY THAT'S A GAME OVER!! \n";
		cout << "PLAYER NAME : " << m_playerName;
		cout << "FINAL SCORE IS : " << m_score;
	}
};


int main()
{

	// Initialize these two variables if you want
	pair<int, int> startingPosition(54, 20);
	Orientation orientation = Orientation::x;
	Levels levelType = Levels::unboxed;

	// State control variables
	bool fruitUnavailable = true;
	bool isHit = false;

	// Game manager object
	GameManager gameManager;

	// Get the player details and the difficulty level
	while(gameManager.GetPlayerData()) {}
	// Initialize settings for the console and the snake
	gameManager.InitializeSettings(startingPosition, levelType, orientation);
	// Add a fruit
	gameManager.AddFruit();
	fruitUnavailable = false;

	// Main game loop
	while(true)
	{
		// Check if the snake has made a hit
		if(!isHit)
		{
			// Add fruit if the fruit is eaten
			if(fruitUnavailable)
			{
				gameManager.AddFruit();
				fruitUnavailable = false;
			}

			// Update the snake by getting inputs
			gameManager.SnakeUpdate(gameManager.GetInput());

			// Check for hits
			switch(gameManager.GetHitType())
			{
				case HitType::fruit:
					gameManager.ScoreUpdate();
					fruitUnavailable = true;
					break;
				case HitType::self:
					isHit = true;
					break;
				default:
					break;
			}
		}
		else
		{
			// Do a kill effect
			gameManager.DoKillEffect();
			break;
		}
	}
	// Show the end screen
	gameManager.PrintEndScreen();
	return 0;
}