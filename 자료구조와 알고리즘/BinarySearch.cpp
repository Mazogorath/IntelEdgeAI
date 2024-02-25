#include <iostream>
using namespace std;

int binarySearch(int arr[], int left, int right, int x)
{
	while (left <= right)
	{
		int mid = right - left / 2;
		if (arr[mid] == x)
		{
			return mid;
		}
		else if (arr[mid] < x)
		{
			left = mid + 1;
		}
		else if (arr[mid] > x)
		{
			right = mid - 1;
		}
	}
	return -1;
}

int main(void)
{
	cout << "10 크기 배열의 원소를 작은 것부터 입력" << endl;
	int arr[10];
	for (int i = 0; i < 10; i++)
	{
		int num;
		cin >> num;
		arr[i] = num;
	}

	cout << "배열에서 찾고자 하는 숫자 입력" << endl;
	int num;
	cin >> num;
	
	int result = binarySearch(arr, 0, 9, num);

	if (result >= 0)
		cout << result + 1 << "번째 자리에 해당 숫자가 있습니다" << endl;
	else if (result == -1)
		cout << "배열에 해당 숫자가 없습니다" << endl;

}