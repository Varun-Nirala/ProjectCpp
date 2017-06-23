#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

mutex mutex_controller;

void function_add(int number)
{
	mutex_controller.lock();
	thread::id this_id = this_thread::get_id();
	cout << __func__ << " is called, with thread id = " << this_id << endl;
	mutex_controller.unlock();

	for(int i = 0; i < number; i++)
	{
		mutex_controller.lock();
		cout << __func__ << " : " << i << " + " << number << " = " << i + number << endl;
		mutex_controller.unlock();
	}
	cout << "Exiting.\n";
}

void function_mult(int number)
{
	mutex_controller.lock();
	thread::id this_id = this_thread::get_id();
	cout << __func__ << " is called, with thread id = " << this_id << endl;
	mutex_controller.unlock();

	for(int i = 0; i < number; i++)
	{
		mutex_controller.lock();
		cout << __func__ << " : " << i << " * " << number << " = " << i * number << endl;
		mutex_controller.unlock();
	}
	cout << "Exiting.\n";
}

int main(int argc, char const *argv[])
{
	int add = 4;
	int mult = 5;
	thread::id this_id = this_thread::get_id();

	cout << "Main thread id = " << this_id << endl;

	thread t_thread1(function_add, add);
	thread t_thread2(function_mult, mult);

	t_thread1.join();
	t_thread2.join();
	cin.get();
	return 0;
}