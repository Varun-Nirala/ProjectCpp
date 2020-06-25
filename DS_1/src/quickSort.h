#pragma once
#include "helper.h"

using namespace std;

int getPivot(int start, int end)
{
	return ( start + end ) / 2;
}

int partition(int *arr, int low, int high)
{
	int pivot = arr[getPivot(low, high)];
	int startIndex = low;

	while (low < high)
	{
		while (arr[low] < pivot)
		{
			low++;
		}

		while (arr[high] > pivot)
		{
			high--;
		}

		if (low > high)
			return high;

		std::swap(arr[low], arr[high]);
		low++;
		high--;
	}
}

void quickSort(int *arr, int low, int high)
{
	if (low < high)
	{
		int partIndex = partition(arr, low, high);
		quickSort(arr, low, partIndex - 1);
		quickSort(arr, partIndex + 1, high);
	}
}

void test_quickSort()
{
	cout << "\nQUICK SORT\n";
	//int arr[] = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	//int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	//int arr[] = { 1, 3, 2, 5, 4, 8, 6, 10, 9, 11, 7 };

	int arr[] = { 1, 2 };

	int size = sizeof(arr) / sizeof(arr[0]);

	printArray(arr, size);

	quickSort(arr, 0, size - 1);

	cout << "After Sorting\n";
	printArray(arr, size);
}