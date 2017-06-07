#include <iostream>
#include <string>
#include <vector>

using namespace std;

void permute(string str, int beg, int end);
void permute(string str, int beg, int end, vector<string> &permutations);

int main(int argc, char const *argv[])
{
	string str;
	vector<string> v_permutations;

	cout << "Enter the string : ";
	getline(cin, str);

	//permute(str, 0, str.size()-1);
	//permute(str, 0, str.size()-1, v_permutations);

	vec
	cin.get();
return 0;
}


/*************************************************************************
*	@Function	:	void permute(string str, int beg, int end)
*	@breif		:	print all permutations of a string.
*	@Param1		:	string to permute
*	@Param2 	:	start position, 0 when called from main
*	@return		:	void
*	
*	@NOTE		:	Print all permutations(n!) even if they repeat.
*************************************************************************/
void permute(string str, int beg, int end)
{
	if(beg == end)
	{
		cout << str << endl;
	}
	else
	{
		for(int i = beg; i <= end; i++)
		{
			swap(str[beg], str[i]);
			permute(str, beg+1, end);
			swap(str[beg], str[i]);
		}
	}
}

/*************************************************************************
*	@Function	:	void permute(string str, int beg, int end)
*	@breif		:	print all permutations of a string.
*	@Param1		:	string to permute
*	@Param2 	:	start position, 0 when called from main
*	@Prama3		:	reference to vector<string>
*	@return		:	void
*	
*	@NOTE		:	stores all permutations(n!) even if they repeat, in
*					the @Param3
*************************************************************************/
void permute(string str, int beg, int end, vector<string> &v_permutations)
{
	if(beg == end)
	{
		v_permutations.push_back(str);
	}
	else
	{
		for(int i = beg; i <= end; i++)
		{
			swap(str[beg], str[i]);
			permute(str, beg+1, end);
			swap(str[beg], str[i]);
		}
	}	
}