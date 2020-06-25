#include <iostream>

//Searching
#include "binarySearch.h"

//Sorting
#include "bubbleSort.h"
#include "selectionSort.h"
#include "insertionSort.h"
#include "quickSort.h"
#include "mergeSort.h"
#include "heapSort.h"

using namespace std;

int main()
{
	test_binSearch();

	test_bubbleSort();
	test_selectionSort();
	test_insertionSort();
	test_quickSort();
	test_mergeSort();
	test_heapSort();

	return 0;
}