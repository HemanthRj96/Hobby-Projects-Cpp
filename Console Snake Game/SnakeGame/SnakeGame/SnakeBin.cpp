#include<iostream>
#include<Windows.h>
#include<chrono>
#include<vector>

using namespace std;

enum class Direction
{
	up,
	down,
	left,
	right
};


const short head = 0x2592;
const short tail = 0x2588;
const short fruit = '#';
const int screenWidth = 120;
const int screenHeight = 40;
const float framDelay = 30;

pair<int, int> startingPosition(54, 20);
bool xOrientation = false;

int main()
{
	DWORD dwByteSize = 0;
	CONSOLE_CURSOR_INFO cursorInfo;

	// Player details
	string playerName;
	int level = 1;
	int score = 0;

	// Screen itself
	wchar_t* screen = new wchar_t[screenWidth * screenHeight];

	// Stores the snake body and the recently discarded body
	int startingLength = 25;
	vector<pair<int, int>> snakeBody;
	pair<int, int> discarded;
	pair<int, int> fruitPosition;

	// To know the direction of the snkae
	Direction direction = Direction::right;

	// State control variables
	bool fruitAvailable = false;
	bool isHit = false;

	// Get the player details and the difficulty level
	cout << "THIS IS THE SNAKE GAME PLEASE INPUT YOUR NAME : ";
	cin >> playerName;
	repeat:
	cout << "INPUT YOUR DESIRED SPEED OF LEVEL (1-10): ";
	cin >> level;
	if(!(level >= 1 && level <= 10))
		goto repeat;

	// Setup the console
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	// Fill the screen
	for(int i = 0; i < (screenWidth * screenHeight); i++)
		screen[i] = ' ';

	// Set the snake's size
	snakeBody.resize(startingLength);
	// Set the starting position of snake
	if(xOrientation)
		for(int i = 0; i < startingLength; ++i)
		{
			snakeBody.at(i).first = startingPosition.first - i;
			snakeBody.at(i).second = startingPosition.second;
		}
	else
		for(int i = 0; i < startingLength; ++i)
		{
			snakeBody.at(i).first = startingPosition.first;
			snakeBody.at(i).second = startingPosition.second - i;
		}

	// Get fruit location
	while(true)
	{
		bool flag = false;
		srand(time(nullptr));
		fruitPosition.first = rand() % screenWidth;
		fruitPosition.second = rand() % screenHeight;
		for(int i = 0; i < startingLength; ++i)
			if(snakeBody.at(i) == fruitPosition)
				flag = true;
		if(!flag)
		{
			fruitAvailable = true;
			screen[screenWidth * fruitPosition.second + fruitPosition.first] = fruit;
			break;
		}
	}

	// Main game loop
	while(true)
	{
		// Check if the snake has made a hit
		if(!isHit)
		{
			//Check if the fruit has been eaten
			if(!fruitAvailable)
			{
				// Get fruit location
				while(true)
				{
					bool flag = false;
					srand(time(nullptr));
					fruitPosition.first = rand() % screenWidth;
					fruitPosition.second = rand() % screenHeight;
					for(int i = 0; i < startingLength; ++i)
						if(snakeBody.at(i) == fruitPosition)
							flag = true;
					if(!flag)
					{
						fruitAvailable = true;
						screen[screenWidth * fruitPosition.second + fruitPosition.first] = fruit;
						break;
					}
				}
			}

			//Update the direction
			if(GetAsyncKeyState((unsigned short)'A') & 0x8000)
				if(direction == Direction::down || direction == Direction::up)
					direction = Direction::left;
			if(GetAsyncKeyState((unsigned short)'D') & 0x8000)
				if(direction == Direction::down || direction == Direction::up)
					direction = Direction::right;
			if(GetAsyncKeyState((unsigned short)'S') & 0x8000)
				if(direction == Direction::right || direction == Direction::left)
					direction = Direction::down;
			if(GetAsyncKeyState((unsigned short)'W') & 0x8000)
				if(direction == Direction::right || direction == Direction::left)
					direction = Direction::up;

			// Update the snake body
			switch(direction)
			{
				case Direction::up:
				{
					discarded = snakeBody.at(startingLength - 1);
					for(int i = startingLength - 1; i >= 0; --i)
						if((i - 1) < 0)
						{
							if(snakeBody.at(i).second == 0)
								snakeBody.at(i).second = screenHeight - 1;
							else
								snakeBody.at(i).second -= 1;
						}
						else
							snakeBody.at(i) = snakeBody.at(i - 1);
				}
				break;
				case Direction::down:
				{
					discarded = snakeBody.at(startingLength - 1);
					for(int i = startingLength - 1; i >= 0; --i)
						if((i - 1) < 0)
						{
							if(snakeBody.at(i).second == screenHeight - 1)
								snakeBody.at(i).second = 0;
							else
								snakeBody.at(i).second += 1;
						}
						else
							snakeBody.at(i) = snakeBody.at(i - 1);
				}
				break;
				case Direction::left:
				{
					discarded = snakeBody.at(startingLength - 1);
					for(int i = startingLength - 1; i >= 0; --i)
						if((i - 1) < 0)
						{
							if(snakeBody.at(i).first == 0)
								snakeBody.at(i).first = screenWidth - 1;
							else
								snakeBody.at(i).first -= 1;
						}
						else
							snakeBody.at(i) = snakeBody.at(i - 1);
				}
				break;
				case Direction::right:
				{
					discarded = snakeBody.at(startingLength - 1);
					for(int i = startingLength - 1; i >= 0; --i)
						if((i - 1) < 0)
						{
							if(snakeBody.at(i).first == screenWidth - 1)
								snakeBody.at(i).first = 0;
							else
								snakeBody.at(i).first += 1;
						}
						else
							snakeBody.at(i) = snakeBody.at(i - 1);
				}
				break;
				default:
					break;
			}

			// Update the screen itself
			for(int i = 0; i < startingLength; i++)
				if(i == 0)
					screen[int(screenWidth * snakeBody.at(i).second + snakeBody.at(i).first)] = head;
				else
					screen[int(screenWidth * snakeBody.at(i).second + snakeBody.at(i).first)] = tail;
			screen[screenWidth * discarded.second + discarded.first] = ' ';

			WriteConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), screen, screenWidth * screenHeight, {0,0}, &dwByteSize);

			Sleep(framDelay / level);

			// Check if the snake ate a fruit
			if(snakeBody.at(0) == fruitPosition)
			{
				++startingLength;
				snakeBody.resize(startingLength);
				fruitAvailable = false;
			}

			//Check if snake has made a hit to itself or a wall
			for(int i = 1; i < startingLength; i++)
				if(snakeBody.at(i) == snakeBody.at(0))
					isHit = true;
		}
		else
		{
			//Create a blinking effect
			for(int i = 0; i < 6; ++i)
			{
				for(int j = 1; j < startingLength; ++j)
					if(i % 2)
						screen[screenWidth * snakeBody.at(j).second + snakeBody.at(j).first] = 0x2591;
					else
						screen[screenWidth * snakeBody.at(j).second + snakeBody.at(j).first] = 0x2593;

				WriteConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), screen, screenWidth * screenHeight, {0,0}, &dwByteSize);
				Sleep(1000);
			}
			break;
		}
	}

	system("cls");

	cout << "SORRY THAT'S A GAME OVER!! \n";
	cout << "PLAYER NAME : " << playerName;
	cout << "FINAL SCORE IS : " << score;

	// Show the ending screen
	// Optional save the scores in the highscore file and preview it

	return 0;
}