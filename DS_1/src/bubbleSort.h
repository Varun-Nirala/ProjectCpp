#pragma once

#include "helper.h"		// To use printArray

using namespace std;

void bubbleSort(int *arr, int size)
{
	bool bStop = false;
	for (int i = 0; i < size - 1 && !bStop; ++i)
	{
		bStop = true;
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				bStop = false;
			}
		}
	}
}

void test_bubbleSort()
{
	cout << "\nBUBBLE SORT\n";
	int arr[] = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int size = sizeof(arr) / sizeof(arr[0]);

	printArray(arr, size);

	bubbleSort(arr, size);

	cout << "After Sorting\n";
	printArray(arr, size);
}