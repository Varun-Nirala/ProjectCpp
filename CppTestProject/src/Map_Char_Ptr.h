#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
	map<char *, char *>	m_map;

	char *f = NULL, *l = NULL;

	f = new char[50];
	l = new char[50];

	strcpy(f, "Varun");
	strcpy(l, "Nirala");

	m_map.insert(make_pair(f, l));

	if (m_map.find(f) != m_map.end())
	{
		cout << "Found Varun" << endl;
	}

	system("PAUSE");
	return 0;
}