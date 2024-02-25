#include <iostream>
using namespace std;

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}


int arr[5] = {};

int main(void)
{
    cout << "elements of array" << endl;
    int element = 0, n = 5;
    for (int p = 0; p < 5; p++)
    {
        cin >> element;
        arr[p] = element;
    }
    bool flag;
    for (int i = 0; i < 5; i++)
    {
        flag = true;
        for (int j = 1; j < n; j++)
        {
            if (arr[j - 1] > arr[j])
            {
                swap(arr[j - 1], arr[j]);
                flag = false;
            }

        }
        n = n - 1;
        if (flag == true)
            break;
    }

    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << ' ';
    }
    return 0;
}