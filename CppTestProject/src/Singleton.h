#ifndef __SINGLETON__
#define __SINGLETON__
/*
	Description	: Thread safe singleton class
*/

#include <iostream>
#include <mutex>

std::mutex g_MyMutex;

class Singleton
{
	public:
		static Singleton *getInstance();

	private:
		Singleton() = default;
		Singleton(const Singleton &) = default;
		Singleton& operator=(const Singleton &) = default;

		static Singleton *m_pInstance;
};

Singleton* Singleton::m_pInstance = NULL;

Singleton* Singleton::getInstance()
{
	std::lock_guard<std::mutex> lockGuard(g_MyMutex);
	if (!m_pInstance)
	{
		m_pInstance = new Singleton();
	}
	return m_pInstance;
}

#endif