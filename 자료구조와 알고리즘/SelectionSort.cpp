#include <iostream>
using namespace std;

void search(int arr[])
{
    for (int i = 0; i < 4; i++)
    {
        int min = i;
        for (int j = i + 1; j < 5; j++)
        {
            if (arr[i] > arr[j])
                min = j;
        }
        if (i != min)
        {
            int num = arr[i];
            arr[i] = arr[min];
            arr[min] = num;
        }
    }
}

int main(void)
{
    cout << "배열을 생성합니다." << endl;
    int arr[5];
    for (int i = 0; i < 5; i++)
    {
        cout << i << "번째 원소를 입력해주세요" << endl;
        cin >> arr[i];
    }
    cout << "현재 배열입니다" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " ";
    }
    search(arr);
    cout << "\n정렬된 배열입니다" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " ";
    }
}

