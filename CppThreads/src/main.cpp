#include <iostream>
#include <thread>
#include "Counter.h"

using namespace std;

// Different way of initializing thread
void runExample1()
{
	thread t1(counterFunc, 1, 4);
	thread t2(counterFunc, 2, 6);

	// Using uniform initialization
	thread t3{ Counter{3, 20} };
	thread t4( Counter(4, 10) );

	Counter count(5, 20);
	thread t5(&Counter::Process, &count);

	int id = 6;
	int numIterations = 5;

	thread t6([id, numIterations] {
		for (int i = 0; i < numIterations; ++i)
		{
			cout << "Counter " << id << " has value ";
			cout << i << endl;
		}
	});

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
}

int main()
{

	return 0;
}