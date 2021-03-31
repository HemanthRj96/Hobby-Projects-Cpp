#include<iostream>

using namespace std;

// Adapter tutorial code

/*/// PROBLEM ///
Imagine that you’re creating a stock market monitoring app. The app downloads the stock data from multiple sources in XML format and
then displays nice-looking charts and diagrams for the user. At some point, you decide to improve the app by integrating a smart
3rd-party analytics library. But there's a catch: the analytics library only works with data in JSON format. You could change the
library to work with XML. However, this might break some existing code that relies on the library. And worse, you might not have access
to the library's source code in the first place, making this approach impossible.
*/

// https://refactoring.guru/design-patterns/adapter


// This is the client code that returns "SomeStuff"
class ClientInterface
{
public:
	virtual ~ClientInterface() {}
	virtual string InterfaceFunction() { return "Client Interface Output"; }
};

// This is the service code that returns an int pointer that converts the string to an ASCII code
class Service
{
public:
	short* ServiceMethod(const string& someString)
	{
		short* pntr = new short[someString.length()];
		int  i = 0;
		for(auto temp : someString)
		{
			*(pntr + i) = temp;
			++i;
		}
		return pntr;
	}
};

// This is the adapter class that allows ClientInterface to interact with Service and return a string
class Adapter : public ClientInterface
{
	// Wrapped adaptee class
	Service* service_{nullptr};
public:

	// An adapter class can be recognized when you see a wrapped object
	Adapter(Service* service) : service_{service} {}

	// Returns string after converting the ASCII code from Service which takes the input from the ClientInterface
	virtual string InterfaceFunction() override
	{
		string someString = "Adapter Output";
		short* pntr = service_->ServiceMethod(someString);
		string newString;

		for(int i = 0; someString[i] != '\0'; ++i)
			newString.push_back((int)pntr[i]);

		return newString;
	}

	~Adapter() { delete service_; }
};


void AdapterMain_()
{
	string someString = "Sample Input";

	// ClientInterface returns a string
	ClientInterface* _interface = new ClientInterface();
	cout << _interface->InterfaceFunction() << endl;

	// Service takes a string in this case someString ans returns a pointer
	Service* _service = new Service;
	// The output for this code will be the address of the pointer
	cout << _service->ServiceMethod(someString) << endl;

	// Interface gets initialized with an Adapter and now when I print the output, adapter uses the wrapped object to create a string
	_interface = new Adapter(_service);
	cout << _interface->InterfaceFunction() << endl;


	delete _interface;
	delete _service;
}