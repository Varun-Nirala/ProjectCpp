#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;

template<typename T>
void testAndPrint(Graph<T> &mGraph, const T &src, const T &dst);

void test_1_NormalWorkingOfGraph();
void test_2_BFS_DFS_Traversal();

int main()
{
	test_1_NormalWorkingOfGraph();

	test_2_BFS_DFS_Traversal();
	return 0;
}



// TESTING FUNCTIONS
void test_2_BFS_DFS_Traversal()
{
	cout << "\n\nRunning Test 2 :: FunctionName " << __FUNCTION__ << endl;
	Graph<string> g;
	g.addEdge("0", "1");
	g.addEdge("0", "2");
	g.addEdge("1", "2");
	g.addEdge("2", "3");
	g.addEdge("2", "0");

	g.addEdge("3", "3");

	string src = "2";

	cout << "BFS traversal SRC as :: " << src << endl;
	g.BFS(src);


	cout << "DFS traversal SRC as :: " << src << endl;
	g.DFS(src);
}

template<typename T>
void testAndPrint(Graph<T> &mGraph, const T &src, const T &dst)
{
	int weight = -1;
	if (mGraph.isConnected(src, dst))
	{
		mGraph.getWeight(src, dst, weight);
		cout << src << " --- " << weight << " ---> " << dst << endl;
	}
	else
	{
		cout << src << " --- X ---> " << dst << "       Not Connected" << endl;
	}
}

void test_1_NormalWorkingOfGraph()
{
	cout << "Running Test 1 :: FunctionName " << __FUNCTION__ << endl;
	Graph<string> mGraph;

	mGraph.addEdge("A", "B", 1);

	mGraph.addEdge("B", "A", 0);
	mGraph.addEdge("B", "D", 2);

	mGraph.addEdge("C", "A", 3);
	mGraph.addEdge("C", "E", 2);

	mGraph.addEdge("E", "D", 5);

	testAndPrint<string>(mGraph, "A", "B");
	testAndPrint<string>(mGraph, "B", "A");
	testAndPrint<string>(mGraph, "B", "D");
	testAndPrint<string>(mGraph, "C", "A");
	testAndPrint<string>(mGraph, "C", "E");
	testAndPrint<string>(mGraph, "E", "D");

	cout << "Removing A to B edge from A" << endl;
	mGraph.removeEdge("A", "B");

	testAndPrint<string>(mGraph, "A", "B");

	testAndPrint<string>(mGraph, "A", "E");
}