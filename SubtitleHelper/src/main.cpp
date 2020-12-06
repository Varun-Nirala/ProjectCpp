#include <iostream>
#include <algorithm>
#include <conio.h>
#include "SubtitleUtil.h"

using namespace std;
/*
"hours:minutes:seconds,milliseconds".
1
00:01:31,120 --> 00:01:32,485
McCabe.

2
00:01:33,520 --> 00:01:34,521
Let's go.
*/
void StartWork(const string &fileName)
{
	SubtitleUtil subs(fileName);
	subs.start();

	char key;
	bool bKeepGoing = true;

	while (bKeepGoing)
	{
		while (_kbhit())
		{
			key = _getch();
			if (key == 'e' || key == 'E')
			{
				bKeepGoing = false;
				break;
			}
			subs.record();
		}
	}
}

int main()
{
	string fileName;
	cout << "Enter File Name : ";
	cin >> fileName;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	bool isValid = all_of(fileName.begin(), fileName.end(), [](const auto ch)
								{	return isalnum(ch);	});

	if (!isValid)
	{
		cout << "FileName not valid\n";
	}
	else
	{
		fileName += ".txt";
		cout << "\nFile name will be : " << fileName << '\n';

		cout << "\nEnter to 'e' or 'E' to end.\n";
		cout << "\nPress Enter to start and end the timing.\n";

		char ch;
		cout << "Press 's' or 'S' to start recording : ";
		cin >> ch;

		if (ch == 's' || ch == 'S')
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			StartWork(fileName);
		}
	}
	return 0;
}