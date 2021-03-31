#include<iostream>
#include"Matrix.h"

int main()
{
	Matrix<int, 3, 2> matrix = {1,2,3,4,5,6};

	std::cout << matrix;
	return 0;
}