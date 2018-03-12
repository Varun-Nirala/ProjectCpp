#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

using namespace std;
static const int MAX_THREAD = thread::hardware_concurrency();

mutex g_mutex;

void threadFunc(int id)
{
	lock_guard<mutex> lg(g_mutex);
	cout << "threadFunc(): my arg is : " << id << endl;
}

void  bindFunc(int id, string msg)
{
	lock_guard<mutex> lg(g_mutex);
	cout << "bindFunc(): my arg are : id " << id << ", msg = " << msg << endl;
}

int main(int argc, char *argv)
{
	vector<thread> v_thread;
	v_thread.reserve(MAX_THREAD);

	int i;
	for (i = 0; i < MAX_THREAD / 2; ++i)
	{
		v_thread.push_back(thread(threadFunc, i));
	}

	// void (*funcPtr)(int i, string) = &bindFunc;	// functiom pointer example

	function<void(string, int)> func = bind(bindFunc, placeholders::_2, placeholders::_1);

	for (i; i < MAX_THREAD; ++i)
	{
		string msg = "I am number " + to_string(i);
		v_thread.push_back(move(thread(func, msg, i)));
	}

	for_each(v_thread.begin(), v_thread.end(), mem_fn(&thread::join));

	system("PAUSE");
	return 0;
}