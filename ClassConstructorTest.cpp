#include <iostream>


class TestClass 
{
private:

	int numbering;

public:
	TestClass() {
		std::cout << "constructor has called" << "\n";
	}

	TestClass(int num) : numbering(num)
	{
		std::cout << "constructor has called" << "\n";
	}

	int getNum() {
		return numbering;
	}
};

int main() {
	
	int a;

	TestClass tc(100);
	TestClass temp;

	a = tc.getNum();

	std::cout << "\n" << a << "\n";

	return 0;
}