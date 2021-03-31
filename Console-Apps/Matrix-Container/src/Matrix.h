#pragma once
#include <iostream>


template<typename T, int _C, int _R>
class Matrix
{
private:

	const int m_columns = _C;
	const int m_rows = _R;
	T* m_Buffer;

public:

	Matrix()
		:m_Buffer{new T[_C * _R]{}}
	{
	}

	Matrix(std::initializer_list<T> list)
		:Matrix()
	{
		std::copy(list.begin(), list.end(), m_Buffer);
	}

	~Matrix()
	{
		delete[] m_Buffer;
	}

public:


	T& operator()(int row, int column) const
	{
		if(column >= _C || row >= _R)
			throw _Null_;
		else
			return *(m_Buffer + (row * _C) + column);
	}

	Matrix& operator+(const Matrix& other)
	{
		if(other.m_columns != this->m_columns || other.m_rows != this->m_rows)
			return *this;
		else
		{

			return *this;
		}
	}

	//Matrix& operator+=(const Matrix& other);

	//Matrix& operator-(const Matrix& other);

	//Matrix& operator-=(const Matrix& other);

	//Matrix& operator/(float constant);

	//Matrix& operator/=(float constant);

	//Matrix& operator*(float constant);

	//Matrix& operator*=(float constant);


	friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
	{
		for(int i = 0; i < _R; ++i)
		{
			for(int j = 0; j < _C; ++j)
				os << matrix(i, j) << ' ';
			os << std::endl;
		}
		return os;
	}



};
