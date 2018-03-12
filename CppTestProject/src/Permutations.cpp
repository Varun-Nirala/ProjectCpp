#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Normal Recursive Method
void permuteRecursive(string str, int beg, int end);
void permuteRecursive(string str, int beg, int end, vector<string> &permutations);

// Heap's alogrithm
void permuteHeapRecursive(string str, int end);
void permuteHeapRecursive(string str, int end, vector<string> &permutations);
void permuteHeapIterative(string str, int end);
void permuteHeapIterative(string str, int end, vector<string> &permutations);

int main(int argc, char const *argv[])
{
	string str;
	vector<string> v_permutations;

	cout << "Enter the string : ";
	getline(cin, str);

	//permuteRecursive(str, 0, str.size()-1);
	//permuteRecursive(str, 0, str.size()-1, v_permutations);

	cin.get();
return 0;
}


/*************************************************************************
*	@Function	:	void permuteRecursive(string str, int beg, int end)
*	@breif		:	print all permutations of a string.
*	@Param1		:	string to permute
*	@Param2 	:	start position, 0 when called from main
*	@Param3		:	end position, size-1 of string
*	@return		:	void
*	
*	@NOTE		:	Print all permutations(n!) even if they repeat.
*************************************************************************/
void permuteRecursive(string str, int beg, int end)
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
			permuteRecursive(str, beg+1, end);
			swap(str[beg], str[i]);
		}
	}
}

/*************************************************************************
*	@Function	:	void permuteRecursive(string str, int beg, int end)
*	@breif		:	store all permutations of a string in a vector of string.
*	@Param1		:	string to permute
*	@Param2 	:	start position, 0 when called from main
*	@Param3		:	end position, size-1 of string
*	@Prama4		:	reference to vector<string>
*	@return		:	void
*	
*	@NOTE		:	stores all permutations(n!) even if they repeat, in
*					the @Param3
*************************************************************************/
void permuteRecursive(string str, int beg, int end, vector<string> &v_permutations)
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
			permuteRecursive(str, beg+1, end);
			swap(str[beg], str[i]);
		}
	}	
}

/*************************************************************************
*	@Function	:	void permuteHeapRecursive(string str, int end)
*	@breif		:	print all permutations of a string.
*	@Param1		:	string to permute
*	@Param2 	:	end position, size-1 of string
*	@return		:	void
*	
*	@NOTE		:	Print all permutations(n!) even if they repeat.
*************************************************************************/
void permuteHeapRecursive(string str, int end)
{
	if(end == 1)
	{
		cout << str << endl;
	}
	else
	{
		for(int i = 0; i < end; i++)
		{
			permuteHeapRecursive(str, end - 1);
			if(i%2 == 0)
			{
				swap(str[i], str[end - 1]);
			}
			else
			{
				swap(str[0], str[end - 1]);
			}
		}
		permuteHeapRecursive(str, end - 1);
	}
}

/*************************************************************************
*	@Function	:	void permuteHeapRecursive(string str, int end, vector<string> &permutations)
*	@breif		:	store all permutations of a string in a vector of string.
*	@Param1		:	string to permute
*	@Param2		:	end position, size-1 of string
*	@Prama3		:	reference to vector<string>
*	@return		:	void
*	
*	@NOTE		:	Print all permutations(n!) even if they repeat.
*************************************************************************/
void permuteHeapRecursive(string str, int end, vector<string> &v_permutations)
{
	if(end == 1)
	{
		v_permutations.push_back(str);
	}
	else
	{
		for(int i = 0; i < end; i++)
		{
			permuteHeapRecursive(str, end - 1);
			if(i%2 == 0)
			{
				swap(str[i], str[end - 1]);
			}
			else
			{
				swap(str[0], str[end - 1]);
			}
		}
		permuteHeapRecursive(str, end - 1);
	}
}

/*************************************************************************
*	@Function	:	void permuteHeapIterative(string str, int end)
*	@breif		:	print all permutations of a string.
*	@Param1		:	string to permute
*	@Param2 	:	end position, size-1 of string
*	@return		:	void
*	
*	@NOTE		:	Print all permutations(n!) even if they repeat.
*************************************************************************/
void permuteHeapIterative(string str, int end)
{
	int size  = end + 1;
	vector<int> vec_c(size, 0);

	cout << str << endl;

	for(int i = 0; i < size; i++)
	{
		if(vec_c[i] < i)
		{
			if(i%2 == 0)
			{
				swap(str[vec_c[i]], str[i]);
			}
			else
			{
				swap(str[0], str[i]);
			}
			cout << str << endl;
			vec_c[i] += 1;
			i = 0;
		}
		else
		{
			vec_c[i] = 0;
			i++;
		}
	}
}

/*************************************************************************
*	@Function	:	void permuteHeapIterative(string str, int end, vector<string> &v_permutations)
*	@breif		:	store all permutations of a string in a vector of string.
*	@Param1		:	string to permute
*	@Param2 	:	end position, size-1 of string
*	@Param3		:	reference to vector<string>
*	@return		:	void
*	
*	@NOTE		:	Print all permutations(n!) even if they repeat.
*************************************************************************/
void permuteHeapIterative(string str, int end, vector<string> &v_permutations)
{
	int size  = end + 1;
	vector<int> vec_c(size, 0);

	v_permutations.push_back(str);

	for(int i = 0; i < size; i++)
	{
		if(vec_c[i] < i)
		{
			if(i%2 == 0)
			{
				swap(str[vec_c[i]], str[i]);
			}
			else
			{
				swap(str[0], str[i]);
			}
			v_permutations.push_back(str);
			vec_c[i] += 1;
			i = 0;
		}
		else
		{
			vec_c[i] = 0;
			i++;
		}
	}
}