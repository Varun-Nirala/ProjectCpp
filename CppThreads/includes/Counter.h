#pragma once

#include <iostream>
#include <thread>

using namespace std;

/************************ Example 1 START ************************/
void counterFunc(int id, int numIterations)
{
	for (int i = 0; i < numIterations; ++i)
	{
		cout << "Counter " << id << " has value ";
		cout << i << endl;
	}
}

class Counter
{
	public:
		Counter(int id, int numIterations)
			: mId(id)
			, mNumIterations(numIterations)
		{
		}

		void operator() () const
		{
			Process();
		}

		void Process() const
		{
			for (int i = 0; i < mNumIterations; ++i)
			{
				cout << "Counter " << mId << " has value ";
				cout << i << endl;
			}
		}

	private:
		int mId;
		int mNumIterations;
};

// Different way of initializing thread
void runExample1()
{
	thread t1(counterFunc, 1, 4);
	thread t2(counterFunc, 2, 6);

	// Using uniform initialization
	thread t3{ Counter{3, 20} };
	thread t4(Counter(4, 10));

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
/************************ Example 1 END ************************/



/************************ Example 2 START ************************/
// exception handling in threads, passing exception from one thread to another thread
// Every thread can throw its own exceptions, but they need t be caught within their own thread.
// Exception thrown in one thread cannot be caught in another thread

void doSomeWork()
{
	for (int i = 0; i < 5; ++i)
	{
		cout << i << endl;
	}
	cout << "Thread throwing a runtine_error exception..." << endl;
	throw runtime_error("Exception from thread");
}

void threadFunc(exception_ptr &error)
{
	try
	{
		doSomeWork();
	}
	catch (...)
	{
		cout << "Thread caught exception, returning exception..." << endl;
		error = current_exception();
	}
}

void doWorkInThread()
{
	exception_ptr error;

	thread t(threadFunc, ref(error));

	t.join();

	if (error)
	{
		cout << "Main thread received exception, rethrowing it..." << endl;
		rethrow_exception(error);
	}
	else
	{
		cout << "Main thread did not received any exception." << endl;
	}
}

void runExample2()
{
	try
	{
		doWorkInThread();
	}
	catch (const exception &e)
	{
		cout << "Main function caught: '" << e.what() << "'" << endl;
	}
}
/************************ Example 2 END ************************/



/************************ Example 3 START ************************/
// Use of atomic class for creating variable which is thread-safe and race condition free
template <typename T>
void func(T &inCounter)
{
	for (int i = 0; i < 100; ++i)
	{
		++inCounter;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

template<typename T>
void runExample3()
{
	T counter = 0;
	vector<thread> threads;

	for (int i = 0; i < 10; ++i)
	{
		threads.push_back(thread(func<T>, std::ref(counter)));
	}

	for (auto &t : threads)
	{
		t.join();
	}

	if (std::is_same<T, atomic_int>::value)
	{
		cout << "Result Example 3 with atomic counter = " << counter << endl;
	}
	else
	{
		cout << "Result Example 3 without atomic counter = " << counter << endl;
	}
}
/************************ Example 3 END ************************/