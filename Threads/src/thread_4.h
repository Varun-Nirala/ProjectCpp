/*
thread safe singleton
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class SingletonUsingMutex
{
public:
	virtual ~SingletonUsingMutex() = default;

	static SingletonUsingMutex& getInstance()
	{
		if (!m_pInstance)
		{
			lock_guard<mutex> lg(m_mutex);
			if (!m_pInstance)
			{
				m_pInstance.reset(new SingletonUsingMutex);
			}
		}
		return *m_pInstance.get();
	}

private:
	SingletonUsingMutex() = default;
	SingletonUsingMutex(SingletonUsingMutex &) = delete;
	SingletonUsingMutex& operator=(const SingletonUsingMutex &) = delete;

	static unique_ptr<SingletonUsingMutex>	m_pInstance;
	static mutex							m_mutex;
};
unique_ptr<SingletonUsingMutex> SingletonUsingMutex::m_pInstance;
mutex SingletonUsingMutex::m_mutex;




class SingletonUsingOnce
{
public:
	virtual ~SingletonUsingOnce() = default;

	static SingletonUsingOnce* getInstance()
	{
		call_once(m_OnceFlag, [](){ m_pInstance = new SingletonUsingOnce(); });
		return m_pInstance;
	}

private:
	SingletonUsingOnce() = default;
	SingletonUsingOnce(SingletonUsingOnce &) = delete;
	SingletonUsingOnce& operator=(const SingletonUsingOnce &) = delete;

	static SingletonUsingOnce	*m_pInstance;
	static once_flag			m_OnceFlag;
};
SingletonUsingOnce* SingletonUsingOnce::m_pInstance = NULL;
once_flag SingletonUsingOnce::m_OnceFlag;

const int MAX_THREADS = 20;

int main(int argc, char **argv)
{
	vector<thread> v_thread;
	v_thread.reserve(MAX_THREADS);

	int i;
	for (i = 0; i < MAX_THREADS / 2; ++i)
	{
		v_thread.push_back(move(thread(SingletonUsingMutex::getInstance)));
	}

	for (i; i < MAX_THREADS; ++i)
	{
		v_thread.push_back(move(thread(SingletonUsingOnce::getInstance)));
	}

	for_each(v_thread.begin(), v_thread.end(), mem_fn(&thread::join));

	system("PAUSE");
	return 0;
}