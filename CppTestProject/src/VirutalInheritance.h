#ifndef __VERTUALINHERITANCE__
#define __VERTUALINHERITANCE__

#include <iostream>
#include <string>

using namespace std;
/*Start - Describes the Diamond prblem and it's solution
*/
class Base
{
	public:
		Base()
		{
			cout << "Base Ctor" << endl;
		}

		string getMsg() { return m_sMsg; }
		void setMsg(const string &msg) { m_sMsg = msg; }
			
	protected:
		string	m_sMsg;
};

class Derived_1_1 : public virtual Base
{
	public:
		Derived_1_1()
		{
			cout << "Derived_1_1 Ctor" << endl;
		}
};

class Derived_1_2 : public virtual Base
{
	public:
		Derived_1_2()
		{
			cout << "Derived_1_2 Ctor" << endl;
		}
};

class Derived_2_1 : public Derived_1_1, public Derived_1_2
{
	public:
		Derived_2_1()
		{
			cout << "Derived_2_1 Ctor" << endl;
		}

		void ChangeMsg(string newMsg)
		{
			m_sMsg = newMsg;
		}
};
/*End - Variation 1*/
#endif