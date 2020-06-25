#pragma once

#include "helper.h"

void selectionSort(int *arr, int size)
{
	int minIdx = 0;
	for (int i = 0; i < size - 1; ++i)
	{
		minIdx = i;
		for (int j = i + 1; j < size; ++j)
		{
			if (arr[minIdx] > arr[j])
			{
				minIdx = j;
			}
		}
		if (minIdx == i)
		{
			break;
		}
		else
		{
			swap(arr[i], arr[minIdx]);
		}
	}
}

void test_selectionSort()
{
	cout << "\n\nSELECTION SORT\n";
	int arr[] = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int size = sizeof(arr) / sizeof(arr[0]);

	printArray(arr, size);

	selectionSort(arr, size);

	cout << "After Sorting\n";
	printArray(arr, size);
}
