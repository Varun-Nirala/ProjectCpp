#include <iostream>
#include "FinalClass.h"
#include "VirutalInheritance.h"
#include "Singleton.h"
#include "LinkList.h"
#include "MyFixedArray.h"
#include <vector>

using namespace std;

int* allocArray(int size)
{
	int *p = (int *)malloc(size);
	memset(p, 0, size);
	return p;
}

class Base
{
	public:
		void fun(){ cout << "Base::fun()" << endl; };
};

class Derived : public Base
{
	public:
		void fun(){ cout << "Derived::fun()" << endl; };
};

int main()
{

	Derived d;
	d.fun();
//#define __USE_FIXEDARRAY__

#ifdef __USE_FINAL__
	/* Start - FinalClass Usage Example */
	Final final(10);
	Derived d;
	/* End - FinalClass Usage Example */
#endif //__USE_FINAL__

#ifdef __USE_VIRTUAL__
	/* Start - Virutal Inheritance Diamond Issue VARIATION_1 */
	Derived_2_1 d;
	d.setMsg("i am 2_1");
	d.ChangeMsg("I am 2_1 New");
	/* End - Virutal Inheritance Diamond Issue VARIATION_1 */
#endif //__USE_VIRTIUAL

#ifdef __USE_FUNCTION_PTR__
	int *(*functPtr)(int) = &allocArray;
	int *m_Arr = functPtr(10);

	for (int i = 0; i < 10; ++i)
	{
		cout << m_Arr[i] << endl;
	}
	free(m_Arr);
#endif //__USE_FUNCTION_PTR__

#ifdef __USE_SINGLETON__
	Singleton *single = Singleton::getInstance();
#endif
	    
#ifdef __USE_LL__
	LinkList ll = { 0,1,2,3,4,5,6,7,8,9,10 };
	ll.Display();

	cout << "Is there a Lopp?? " << std::boolalpha << ll.DetectLoop() << endl;

	cout << "Creating loop to Data 4" << endl;
	Node *tail = ll.FindNode(10);
	tail->m_pNext = ll.FindNode(4);
	cout << "Loop created" << endl;

	if (ll.DetectLoop())
	{
		cout << "There is a loop." << endl;
	}

	cout << "Breaking the loop" << endl;
	ll.BreakLoop();
	if (ll.DetectLoop())
	{
		cout << "There is a loop." << endl;
	}
	ll.Display();
#endif

#ifdef __USE_FIXEDARRAY__
	FixedArray<int> myArray(10);

	for (FixedArray<int>::iterator it = myArray.begin(); it != myArray.end(); ++it)
	{
		*it = *it + 10;
	}

	/*for (FixedArray<int>::const_iterator it = myArray.begin(); it != myArray.end(); ++it)
	{

	}*/
#endif



	system("PAUSE");
	return 0;
}