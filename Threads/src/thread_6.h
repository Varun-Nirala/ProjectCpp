#include <iostream>
#include <thread>
#include <future>
#include <string>
using namespace std;

int findTheAnswer()
{
	this_thread::sleep_for(chrono::milliseconds(1000));
	return 50;
}

class MyFunctor
{
public:
	void operator()(string msg)
	{
		cout << "Received msg is : " << msg << "\n";
	}

	string toUpper(string msg)
	{
		string ans;
		transform(msg.begin(), msg.end(), back_inserter(ans), ::toupper);
		return ans;
	}
};

int main()
{
#ifdef SIMPLE_USE
	cout << "Starting new thread.\n";
	future<int> f_answer = async(launch::async, findTheAnswer);
	cout << "Going into hybernation.\n";
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << "Awaked from slumber.\n";

	cout << "The answer i got is : " << f_answer.get() << endl;
#endif	//#ifdef SIMPLE_USE

	MyFunctor myF;
	future<void> f_operator = async(launch::deferred, ref(myF), "Hello");

	future<string> f_toUpper = async(launch::async, &MyFunctor::toUpper, &myF, "I am varun.");

	f_operator.get();

	string ans = f_toUpper.get();

	cout << "Received answer is :: " << ans << endl;

	system("PAUSE");
	return 0;
}