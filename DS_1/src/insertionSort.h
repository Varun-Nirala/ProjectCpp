#pragma once

#include "helper.h"

void insertionSort(int *arr, int size)
{
	int key;

	for (int i = 1; i < size; ++i)
	{
		key = arr[i];

		int j = i - 1;
		for (j = i - 1; j >= 0; --j)
		{
			if (arr[j] > key)
			{
				arr[j + 1] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j + 1] = key;
	}
}

void test_insertionSort()
{
	cout << "\nINSERTION SORT\n";
	int arr[] = { 11, 10, 9, 8, 6, 7, 5, 4, 3, 2, 1 };
	int size = sizeof(arr) / sizeof(arr[0]);

	printArray(arr, size);

	insertionSort(arr, size);

	cout << "After Sorting\n";
	printArray(arr, size);
}
