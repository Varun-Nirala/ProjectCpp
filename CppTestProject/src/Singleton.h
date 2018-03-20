#include <iostream>
#include <string>

class Singleton
{
	private:
		Singleton(){}
		Singleton(Singleton &);
		Singleton(Singleton &&);

	public:
		static Singleton* getInstance()
		{
			if(m_bIsInitialized)
			{
				printf("INFO::Returning existing object\n");
				return m_pSingleton;
			}
			else
			{
				printf("INFO::Creating new object\n");
				m_pSingleton = new Singleton();
				m_bIsInitialized = true;
				return m_pSingleton;
			}
		}

		~Singleton()
		{
			printf("INFO::Deleting singleton with address = %d\n", m_pSingleton);
			m_bIsInitialized = false;
			m_pSingleton = NULL;
		}

	private:
		static Singleton 	*m_pSingleton;

	public:
		static bool 		m_bIsInitialized;
};

bool Singleton::m_bIsInitialized = false;
Singleton* Singleton::m_pSingleton = NULL;

int main()
{
	Singleton *obj1 = Singleton::getInstance();
	printf("Address1 = %d\n", obj1);
	Singleton *obj2 = Singleton::getInstance();
	printf("Address2 = %d\n", obj2);
	getchar();
	return 0;
}