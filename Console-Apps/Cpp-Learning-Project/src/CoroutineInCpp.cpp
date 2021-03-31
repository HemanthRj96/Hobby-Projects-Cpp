#include<iostream>

// This is an example implementation of the coroutine in C++

char Coroutine(const std::string& someString)
{
	static int state = 0;
	static int iterator = 0;
	switch(state)
	{
		case 0:
		{
			state = 1;
			for(; someString[iterator] != '\0'; ++iterator)
			{
				return someString[iterator];
		case 1:; // Resumes from here

			}
		}
	}

	state = 0;
	return '\0';
}

void CoroutineMain_()
{
	char someChar;
	while(1)
	{
		someChar = Coroutine("Hey man how's it going?");
		if(someChar != '\0')
			std::cout << "The character is :" << someChar << " and the corresponding ASCII is :" << (int)someChar << std::endl;
		else
			break;
	}
}