/*
thread safe queue, example of producer consumer problem
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

template<typename T>
class threadSafe_queue
{
public:
	threadSafe_queue(){};
	threadSafe_queue(const threadSafe_queue&other)
	{
		lock_guard<mutex> lg(m_mutex);
		m_queue = other.m_queue;
	}
	threadSafe_queue& operator=(const threadSafe_queue &) = delete;

	void push(T new_value)
	{
		lock_guard<mutex>	lg(m_mutex);
		m_queue.push(new_value);
		m_cv.notify_one();
	}

	bool try_pop(T& value)
	{
		lock_guard<mutex> lg(m_mutex);
		if (m_queue.empty())
		{
			return false;
		}
		value = m_queue.front();
		m_queue.pop();
		return true;
	}

	std::shared_ptr<T> try_pop()
	{
		lock_guard<mutex> m_mutex;
		if (m_queue.empty())
		{
			return shared_ptr<T>();
		}
		shared_ptr<T> res(make_shared<T>(m_queue.front()));
		return res;
	}

	void wait_and_pop(T &value)
	{
		unique_lock<mutex>	ul(m_mutex);
		m_cv.wait(ul, [this](){ return !m_queue.empty(); });
		value = m_queue.front();
		m_queue.pop();
	}

	shared_ptr<T> wait_and_pop()
	{
		unique_lock<mutex>	ul(m_mutex);
		m_cv.wait(ul, [this](){ return !m_queue.empty(); });
		shared_ptr<T> res(make_shared<T>(m_queue.front()));
		m_queue.pop();
		return res;
	}

	bool empty() const
	{
		lock_guard<mutex>	lg(m_mutex);
		return m_queue.empty();
	}

private:
	mutable mutex		m_mutex;
	queue<T>			m_queue;
	condition_variable	m_cv;
};

/* PRODUCER CONSUMER EXAMPLE */

bool producerDone = false;
threadSafe_queue<int> g_myQueue;

const int MAX_RUN = 20;

bool more_data_to_prepare()
{
	static int count = 0;

	return count++ < MAX_RUN;
}

int prepare_data()
{
	return rand() % 100;
}

void producer()
{
	while (more_data_to_prepare())
	{
		int data = prepare_data();
		cout << "Prepared data is : " << data << "\n";
		g_myQueue.push(data);
	}

	producerDone = true;
}

void process(int data)
{
	cout << "Data to be processed is : " << data << "\n";
}

bool is_last_chunk(int data)
{
	return producerDone && g_myQueue.empty();
}

void consumer()
{
	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(1));
		int data = -1;
		g_myQueue.wait_and_pop(data);
		process(data);
		if (is_last_chunk(data))
			break;
	}
}

int main()
{
	thread producerT(producer), consumerT(consumer);

	producerT.join();
	consumerT.join();

	system("PAUSE");
	return 0;
}