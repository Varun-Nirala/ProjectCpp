#pragma once

#include "helper.h"

int parent(int i)
{
	return (i - 1) / 2;		// 0 based index
	//return i / 2;			// 1 based index
}

int leftChild(int i)
{
	return 2 * i + 1;		// 0 based index
	//return 2*i;			// 1 based index
}

int rightChild(int i)
{
	return 2 * i + 2;		// 0 based index
	//return 2*i + 1;		// 1 based index
}

void MaxHeapify(int *arr, int size, int i)
{
	int left = leftChild(i);
	int right = rightChild(i);
	int largest = i;

	if (left < size && arr[left] > arr[largest])
	{
		largest = left;
	}
	if (right < size && arr[right] > arr[largest])
	{
		largest = right;
	}

	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		MaxHeapify(arr, size, largest);
	}
}

void MinHeapify(int *arr, int size, int i)
{
	int left = leftChild(i);
	int right = rightChild(i);
	int largest = i;

	if (left < size && arr[left] < arr[largest])
	{
		largest = left;
	}
	if (right < size && arr[right] < arr[largest])
	{
		largest = right;
	}

	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		MinHeapify(arr, size, largest);
	}
}

void minHeapSort(int *arr, int size)
{
	for (int last = (size/2) - 1; last > 0; --last)
	{
		MinHeapify(arr, size, last);
	}
}

void maxHeapSort(int *arr, int size)
{
	for (int last = (size/2) - 1; last > 0; --last)
	{
		MaxHeapify(arr, size, last);
	}
}

void test_heapSort()
{
	cout << "\n\nHEAP SORT\n";
	//int arr[] = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	//int arr[] = { 1, 3, 2, 5, 4, 8, 6, 10, 9, 11, 7 };

	int size = sizeof(arr) / sizeof(arr[0]);

	printArray(arr, size);
	maxHeapSort(arr, size);
	cout << "After MaxHeap Sorting\n";
	printArray(arr, size);

	int arr1[] = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	printArray(arr1, size);
	minHeapSort(arr1, size);
	cout << "After MinHeap Sorting\n";
	printArray(arr1, size);
}
