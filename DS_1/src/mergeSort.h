#pragma once
#include "helper.h"

void copyArray(int *srcArr, int low, int high, int *destArr)
{
	while (low < high)
	{
		destArr[low] = srcArr[low];
		low++;
	}
}

void merge(int *arr, int low, int mid, int high, int *copyArr)
{
	int start = low;
	int s1, s2;
	for (s1 = low, s2 = mid; s1 < mid && s2 < high; )
	{
		if (arr[s1] < arr[s2])
		{
			copyArr[start++] = arr[s1++];
		}
		else
		{
			copyArr[start++] = arr[s2++];
		}
	}

	if (s1 >= mid)
	{
		while (s2 < high)
		{
			copyArr[start++] = arr[s2++];
		}
	}
	else if (s2 >= high)
	{
		while (s1 < mid)
		{
			copyArr[start++] = arr[s1++];
		}
	}

	copyArray(copyArr, low, high , arr);
}

void mergeSplit(int *arr, int low, int high, int *copyArr)
{
	if (high - low < 2)                       // if run size == 1
			return;

	int mid = (low + high) / 2;

	mergeSplit(arr, low, mid, copyArr);
	mergeSplit(arr, mid, high, copyArr);
	merge(arr, low, mid, high, copyArr);
}

void mergeSort(int *arr, int low, int high)
{
	int *copyArr = new int[high];
	copyArray(arr, low, high, copyArr);

	mergeSplit(arr, low, high, copyArr);

	delete[] copyArr;
	copyArr = NULL;
}

void test_mergeSort()
{
	cout << "\nMERGE SORT\n";
	int arr[] = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	//int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	//int arr[] = { 1, 3, 2, 5, 4, 8, 6, 10, 9, 11, 7 };

	int size = sizeof(arr) / sizeof(arr[0]);

	printArray(arr, size);

	mergeSort(arr, 0, size);

	cout << "After Sorting\n";
	printArray(arr, size);
}