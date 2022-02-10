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

class Ex
{
private:
	double x;
public:
	Ex(double x): x(x) { }
	
	double what() { return x; }
};

class Bar
{
private:
	double y;
public:
	Bar(): y(0.0) { }
	
	void set(double a)
	{
		if ((y + a) > 100)
			throw (Ex(a * y));
		y = a;
	}
};

// Task 3

class OffTheField : public std::exception
{
private:
	int m_x;
	int m_y;
	std::string direction;
public:
	OffTheField(int x, int y, std::string dir): m_x(x), m_y(y), direction(dir) { }

	const char* what() const override
	{

	}
};

class IllegalCommand : public std::exception
{
private:
	int m_x;
	int m_y;
	int direction;
public:
	IllegalCommand(int x, int y, int dir) : m_x(x), m_y(y), direction(dir) { }

	const char* what() const override
	{

	}
};

class Robot
{
private:
	const int FIELD_LENGTH = 10;
	const int FIELD_HEIGHT = 10;

	int m_x;
	int m_y;

	bool checkfield(int x, int y, std::string direction)
	{
		if (x >= FIELD_LENGTH || x < 0 || y >= FIELD_HEIGHT || y < 0)
			return true;
		return false;
	}
public:
	Robot() : m_x(0), m_y(0) { }
	
	void move (int direction) // direction in degrees 0 - UP, 45 - UP+Right an so on
	{
		switch (direction)
		{
		case 0:
			if (checkfield(m_x, m_y + 1, "Up"))
			{
				throw(OffTheField(m_x, m_y, "Up"));
			}
			else { m_y++; }
			break;

		case 45:
			if (checkfield(m_x + 1, m_y + 1, "Up_Right"))
			{
				throw(OffTheField(m_x, m_y, "Up_Right"));
			}
			else { m_x++; m_y++; }
			break;
		
		case 90:
			if (checkfield(m_x + 1, m_y, "Right"))
			{
				throw(OffTheField(m_x, m_y, "Right"));
			}
			else { m_x++; }
			break;
		
		case 135:
			if (checkfield(m_x + 1, m_y - 1, "Down_Right"))
			{
				throw(OffTheField(m_x, m_y, "Down_Right"));
			}
			else { m_x++; m_y--; }
			break;
		
		case 180:
			if (checkfield(m_x, m_y - 1, "Down"))
			{
				throw(OffTheField(m_x, m_y, "Down"));
			}
			else { m_y--; }
			break;
		
		case 225:
			if (checkfield(m_x - 1, m_y - 1, "Down_Left"))
			{
				throw(OffTheField(m_x, m_y, "Down_Left"));
			}
			else { m_x--;  m_y--; }
			break;
		
		case 270:
			if (checkfield(m_x - 1, m_y, "Left"))
			{
				throw(OffTheField(m_x, m_y, "Left"));
			}
			else { m_x--; }
			break;
		
		case 315:
			if (checkfield(m_x - 1, m_y + 1, "Up_Left"))
			{
				throw(OffTheField(m_x, m_y, "Up_Left"));
			}
			else { m_x--;  m_y++; }
			break;
		
		default:
			throw (IllegalCommand(m_x, m_y, direction));
		}
	}
};

int main ()
{
	
	// Task 1
	try
	{
		std::cout << "Result of division: " << div(1.0, 0.0);
	}
	catch (DivisionByZero &err)
	{
		std::cout << err.what() << std::endl;
	}

	// Task 2
	Bar taskTwo;
	
	try
	{
		int n = 0;
		while(true)
		{
			taskTwo.set(n++);
		}
	}
	catch(Ex &err)
	{
		std::cout << "An error occured with: " << err.what() << std::endl;
	}

	// Task 3
	Robot taskThree;

	try
	{
		taskThree.move(40);
	}
	catch(OffTheField &err)
	{
		std::cout << "Moving off the field" << err.what() << std::endl;
	}
	catch(IllegalCommand &err)
	{
		std::cout << "Illegal command: " << err.what() << std::endl;
	}

	return 0;
}