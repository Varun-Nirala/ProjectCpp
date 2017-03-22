#include <iostream>
#include <string>

#include "BigInt.h"

using namespace std;
using namespace PersonalInt;

int Menu()
{
	int choice = 0;

	while (1)
	{
		cout << "Enter the operation u wana perform : \n";
		cout << "1. Assign Var A a number.\n";
		cout << "2. Assign Var B a number.\n";
		cout << "3. A + B.\n";
		cout << "4. A - B.\n";
		cout << "5. A * B.\n";
		cout << "6. Compare A < B.\n";
		cout << "7. Compare A > B.\n";
		cout << "8. Compare A <= B.\n";
		cout << "9. Compare A >= B.\n";
		cout << "10. Display both number.\n";
		cout << "0. Exit\n";
		cin >> choice;
		if (cin.fail())
		{
			cout << "Please enter only number\n";
			cin.ignore(1000,'\n');
			cin.clear();
		}
		else
		{
			break;
		}
	}
	return choice;
}

int main(int argc, char *argv[])
{
	BigInt num_c, num_d;
	BigInt num_a, num_b;

	int choice = Menu();
	string str;

	while (choice != 0)
	{
		switch (choice)
		{
			case 1:
				cin >> str;
				cin.ignore(10000, '\n');
				cin.clear();
				try
				{
					num_a = str;
				}
				catch (...)
				{
					cout << __FUNCTION__ << ":" << __LINE__ << ":: Unknown Exception while creating BigInt.\n";
				}
				cout << "Num_A = " << num_a << endl;
				break;

			case 2:
				cin >> str;
				cin.ignore(10000, '\n');
				cin.clear();
				try
				{
					num_b = str;
				}
				catch (...)
				{
					cout << __FUNCTION__ << ":" << __LINE__ << ":: Unknown Exception while creating BigInt.\n";
				}
				cout << "Num_B = " << num_b << endl;
				break;

			case 3:
				cout << "Num_A = " << num_a << ", Num_B = " << num_b << endl;
				cout << "Num_A + Num_B = " << num_a + num_b << endl;
				break;

			case 4:
				cout << "Num_A = " << num_a << ", Num_B = " << num_b << endl;
				cout << "Num_A - Num_B = " << num_a - num_b << endl;
				break;

			case 5:
				cout << "Num_A = " << num_a << ", Num_B = " << num_b << endl;
				cout << "Num_A * Num_B = " << num_a * num_b << endl;
				break;

			case 6:
				cout << "Num_A = " << num_a << ", Num_B = " << num_b << endl;
				cout << boolalpha << "Num_A < Num_B ? : " << (num_a < num_b) << endl;
				break;

			case 7:
				cout << "Num_A = " << num_a << ", Num_B = " << num_b << endl;
				cout << boolalpha << "Num_A > Num_B ? : " << (num_a > num_b) << endl;
				break;

			case 8:
				cout << "Num_A = " << num_a << ", Num_B = " << num_b << endl;
				cout << boolalpha << "Num_A <= Num_B ? : " << (num_a <= num_b) << endl;
				break;

			case 9:
				cout << "Num_A = " << num_a << ", Num_B = " << num_b << endl;
				cout << boolalpha << "Num_A >= Num_B ? : " << (num_a >= num_b) << endl;
				break;

			case 10:
				cout << "Num_A = " << num_a << ", Num_B = " << num_b << endl;
				break;

			default:
				cout << "Not a valid option.\n";
				break;
		}
		system("PAUSE");
		choice = Menu();
	}
	return 0;
}