#include<iostream>
#include<climits>

using namespace std;

// This function displays the sizes of all the primitive data types and the max and min value of each data type
void DisplayUniqueTypeMemorySize()
{
	cout << "Size of int is :" << sizeof(int) << " with highest value of :" << INT_MAX << " and a lowest value of :" << INT_MIN << endl;
	cout << "Size of long int is :" << sizeof(long int) << endl;
	cout << "Size of long long int is :" << sizeof(long long int) << endl;
	cout << "Size of long is " << sizeof(long) << " with the highest value of :" << LONG_MAX << " and a lowest value of :" << LONG_MIN << endl;
	cout << "Size of char is :" << sizeof(char) << " with the highest value of :" << CHAR_MAX << " and the lowest value of :" << CHAR_MIN << endl;
	cout << "Size of char16_t is :" << sizeof(char16_t) << endl;
	cout << "Size of char32_t is :" << sizeof(char32_t) << endl;
	cout << "Size of wchar_t is :" << sizeof(wchar_t) << endl;
	cout << "Size of float is :" << sizeof(float) << endl;
	cout << "Size of double is :" << sizeof(double) << endl;
	cout << "Size of long double is :" << sizeof(long double) << endl;
}



// Different types of constants and shown below under the code fragment

int SquaringFunction(int A) { return (A * A); }
constexpr int ConstExprSquaringFunction(int A) { return (A * A); }

void ConstantIllustration(int A)
{
	// This type of constant ensures that the value given to it doesn't change even if it happens on runtime
	const int square = SquaringFunction(A);

	// However unlike the previous constant the values inside constexpr should be known at compile time
	// constexpr int anotherSquare = SquaringFunction(A);  // Error this statement is an error
	// constexpr int anotherSquare = SquaringFunction(square); // Error this statement is also an error since the value is still uknown during compile time
	constexpr int anotherSquare = ConstExprSquaringFunction(34); // This works since the function returns constexpr and also the values is known at compile time

	// Enumerators are another type of constants and there are two types of enumerators; strongly typed and loosely typed
	enum ColorA { black, white, red, blue, green }; // Integer type enum
	ColorA someColorA = blue; // It can be initialized like this
	someColorA = (ColorA)1; // It can also be initialized using explicit casting

	enum class ColorB { black, white, red, blue, green }; // Class type enum
	// ColorB color = blue; // Error the compiler doesn't know which type of enum it is looking for
	ColorB someColorB = ColorB::blue; // This works since this the default way of initializing this type of enum
	someColorB = (ColorB)1; // It can also be initialized using explicit casting

	ColorA someColorC = blue; // Note that the compiler doesn't have a problem initializing this since its not strongly typed

	//This is another type of constant and it shouldn't be used that much since all that it does is replace PI with that value
#define PI 3.14
	cout << PI; // Output will be 3.14
}



void Loops()
{
	int i = 0;
	while(i < 10) // While loop runs until this statement becomes false
	{
		cout << "Doing this for the " << i << " time" << endl;
		++i;
	}

	for(i = 0; i < 10; ++i) // For loop also runs until the middle statement becomes false
							 // the difference is that the conditions and incrementing and initialization are handled by for loop
	{
		cout << "Doing this for the " << i << " time" << endl;
	}

	do // Do-while loop runs at least one time before doing the condition check
	{
		cout << "Doing this for the " << i << " time" << endl;
		++i;
	} while(i < 10);
}



void TestConditions()
{
	if(true)
	{
		// Do this
	}
	else
	{
		// Do this
	}

	if(true)
	{
		// Do this
	}
	else if(true)
	{
		// Do this
	}
	else
	{
		// Do this
	}

	enum class example { value_1 = 0, value_2, value_3, value_4 };

	example ex = example::value_3;

	switch(ex)
	{
		case example::value_1:
			break;
		case example::value_2:
			break;
		case example::value_3:
			break;
		case example::value_4:
			break;
		default:
			// Do this by default
			break;
	}
}



void Initialization()
{
	// int a{1}; // Safest way of initialization
	// int a(2); // Constructor initialization
	// int a = 3; // Initialization using assignment operator
}



void PointerAndArrays()
{
	// Pointers and array of pointers

	int* pntrA; // Means that a can only point to variables of type int
	int* pntrB[10]; // This is an array of pointers

	pntrA = new int[10]{}; // Allocating pointer with memory from heap storage which is dynamic memory allocation
	pntrB[0] = new int[10]{}; // Allocates memory for each element inside the array

	// Accessing the contents of the pointer

	cout << *(pntrA + 0); // Print the value this pointing to
	cout << pntrA[0]; // Same as the previous statement
	cout << *(pntrB[0] + 0); // Prints the value pointed by the first allocated memory inside b[0]
	cout << pntrB[0][0]; // Same statement as before
	cout << pntrA; // Prints the memory address of this pinter variable
	cout << &pntrA; // Same as the previous statement
	cout << pntrB; // Print the memory address of b[0]
	cout << &pntrB; // Same statement as before

	delete[] pntrA;
	for(int i = 0; i < 10; ++i)
		delete[] pntrB[i];

	// Arrays

	int someArray[10]{}; // Initialize the array with 10 element

	cout << someArray[0]; // Prints the value at the index 0
	cout << *(someArray + 0); // Same as the previous statement
}



void ErrorHandling()
{
	class Error // Custom error class to make custom error messages
	{
		string _msg;
	public:
		Error(const string& msg) : _msg{msg} {}

		string What() const { return _msg; }
	};


	// Try and catch block
	int i = 10;

	try // Try block where the error can potentially occur
	{
		if(i > 10)
			throw(new Error("i is greater that 10"));
	}
	catch(Error& er) // Catch block that catches the error
	{
		cout << "Found the error :" << er.What();
	}

	// Static assertions

	const bool flag = true; // Constant statement since static_assert run on compile time

	static_assert(flag, "Some error statement"); // Compile time error checker i.e, if flag is false then this statement would
												 // compilation error

}


void CppBasicsMain_()
{
	DisplayUniqueTypeMemorySize();
	system("pause");
	system("cls");
	ConstantIllustration(5);
	system("pause");
	system("cls");
	TestConditions();
	system("pause");
	system("cls");
	Loops();
	system("pause");
	system("cls");
	PointerAndArrays();
	system("pause");
	system("cls");
	ErrorHandling();
	system("pause");
	system("cls");
}