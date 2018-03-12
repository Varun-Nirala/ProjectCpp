#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

const int MAX_THREAD = thread::hardware_concurrency() * 2;
mutex g_mutex;

void threadFun(int id)
{
	lock_guard<mutex> lg(g_mutex);

	cout << "I am thread number :: " << id << "\n";
	cout << "My unique id is :: " << this_thread::get_id() << "\n";
}

int main()
{
	thread *threadArr = nullptr;
	threadArr = new thread[MAX_THREAD];

	cout << "Main thread's id is " << this_thread::get_id() << endl;

	for (int i = 0; i < MAX_THREAD; ++i)
	{
		threadArr[i] = thread(threadFun, i);
	}

	for (int i = 0; i < MAX_THREAD; ++i)
	{
		threadArr[i].join();
	}

	delete[]threadArr;

	system("PAUSE");
	return 0;
}