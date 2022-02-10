#include <iostream>
#include <exception>


// Task 1

class DivisionByZero : public std::exception
{
private:
	std::string message;
public:
	DivisionByZero(std::string msg) : message(msg) { }

	const char* what() const override
	{
		return message.c_str();
	}
};

template <class T>
T div (T num, T denum)
{
	if (denum == 0.0)
		throw DivisionByZero("Division by zero");
	return num / denum;

}

// Task 2



int main ()
{
	
	// Task 1
	try
	{
		std::cout << "Result of division: " << div(1.0, 0.0);
	}
	catch (DivisionByZero err)
	{
		std::cout << err.what() << std::endl;
	}

	// Task 2


	return 0;
}