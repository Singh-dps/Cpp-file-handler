#include <iostream>
#include <algorithm>
using namespace std;

bool evenFirst(int a, int b)
{
    if ((a % 2 == 0) && (b % 2 != 0)) return true;
    if ((a % 2 != 0) && (b % 2 == 0)) return false;

    return a < b;
}

int main()
{
    int arr[6] = {10, 15, 20, 25, 30, 35};

    sort(arr, arr + 6, evenFirst);

    cout << "Sorted (even first, then odd): ";

    for (int i = 0; i < 6; i++)
        cout << arr[i] << " ";

    return 0;
}