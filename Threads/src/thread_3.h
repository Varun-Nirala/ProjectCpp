#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <limits>
#include <numeric>

using namespace std;

template<typename Iterator, typename T>
struct accumulate_block
{
	void operator()(Iterator first, Iterator last, T& result)
	{
		result = accumulate(first, last, result);
	}
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init, T MAX_THREAD)
{
	unsigned long const length = distance(first, last);

	if (!length)
	{
		return init;
	}

	unsigned long const hardware_threads = thread::hardware_concurrency();	// Get number of h/w threads

	unsigned long const num_threads = min(hardware_threads != 0 ? hardware_threads : 2, MAX_THREAD);	// get min of h/w thread or the passed number of threads

	cout << "Number of thread is : " << num_threads << endl;

	unsigned long const block_size = length / num_threads;

	vector<T> results(num_threads, 0);
	vector<thread> v_threads(num_threads - 1);		// one less than the num_thread as one we already have, which is main thread

	Iterator block_start = first;
	for (unsigned long i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		advance(block_end, block_size);

		v_threads[i] = thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));	// ref is required here, as it will first be copied to the thread object
		block_start = block_end;
	}

	accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);	// we don't require ref here as not passing it a thread object

	// join all thread
	for_each(v_threads.begin(), v_threads.end(), mem_fn(&thread::join));

	// accumulate the final result from all threads
	return accumulate(results.begin(), results.end(), init);
}

int main()
{
	const int MAX_TRHEAD = 25;

	vector<unsigned long> myVec(100000000000000);

	generate(myVec.begin(), myVec.end(), [](){ static int i = 0; return i++; });

	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	unsigned long ans = parallel_accumulate<vector<unsigned long>::iterator, unsigned long>(myVec.begin(), myVec.end(), 0, MAX_TRHEAD);
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

	cout << "Parallel_Accumulate -> Got answer in time = " << duration << endl;

	t1 = chrono::high_resolution_clock::now();
	ans = accumulate(myVec.begin(), myVec.end(), 0);
	t2 = chrono::high_resolution_clock::now();

	duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

	cout << "Serial_Accumulate -> Got answer in time = " << duration << endl;

	system("PAUSE");
	return 0;
}