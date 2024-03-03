#include <iostream>
using namespace std;

void merge(int arr[], int min, int m, int max)
{
	int i = min;
	int j = m + 1;
	int k = min;

	int temp[5];

	while (i <= m && j <= max)
	{
		if (arr[i] <= arr[j])
		{
			temp[k++] = arr[i++];
		}
		else
		{
			temp[k++] = arr[j++];
		}
	}

	while (i <= m)
	{
		temp[k++] = arr[i++];
	}
	while (j <= max)
	{
		temp[k++] = arr[j++];
	}

	for (int fori = min; fori <= max; fori++)
	{
		arr[fori] = temp[fori];
	}

}

void mergeSort(int arr[], int min, int max)
{
	if (min < max)
	{
		int m = (min + max) / 2;
		mergeSort(arr, min, m);
		mergeSort(arr, m+1, max);
		merge(arr, min, m, max);
	}
}


int main(void)
{
	int myarr[5];
	int number = 0;

	for (int i = 0; i < 5; i++)
	{
		cout << "숫자 입력" << endl;
		cin >> number;
		myarr[i] = number;
	}
	for (int i = 0; i < 5; i++)
	{
		cout << myarr[i] << ' ';
	}
	cout << endl;
	mergeSort(myarr, 0, 4);
	for (int fori = 0; fori < 5; fori++)
	{
		cout << myarr[fori] << ' ';
	}
	
}