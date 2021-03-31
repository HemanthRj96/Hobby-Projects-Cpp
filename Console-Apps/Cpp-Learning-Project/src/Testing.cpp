#include<iostream>

struct SomeStruct
{

	long long int x, y, z;
	bool a, b, c;
};



void ExampleMain_()
{
	int offset = (int)&((SomeStruct*)nullptr)->a;
	std::cout << offset << std::endl;
	std::cin.get();
}