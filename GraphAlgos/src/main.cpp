#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;

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

int main()
{
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

	return 0;
}