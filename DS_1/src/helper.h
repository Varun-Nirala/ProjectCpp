#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

void printArray(int *arr, int size)
{
	cout << "Array (size = " << size << " ) is : ";
	for (int i = 0; i < size; ++i)
	{
		cout << arr[i] << " , ";
	}
	cout << "\n\n";
}

void printArray(int *arr, int low, int high)
{
	cout << "Array (low = " << low << ", high = " << high << " ) is : ";
	for (int i = low; i < high; ++i)
	{
		cout << arr[i] << " , ";
	}
	cout << "\n\n";
}