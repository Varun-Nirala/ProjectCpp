#include <iostream>
#include <string>

using namespace std;

class FinalClass;

class Final
{
	public:
		virtual void display()
		{
			printf("Hello");
		}

	private:
		Final();

	friend FinalClass;
};

class FinalClass
{
	
};

int main()
{
	return 0;
}