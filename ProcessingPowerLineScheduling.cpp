#include <bits/stdc++.h>

using namespace std;


char Schedule[1000];

int ArraySum(int* Arr, int size, int i)
{
    int sum = 0;
    for (; i <= size; i++)
        sum += Arr[i];
    return sum;
}

void RandomArrayGenerator(int* Arr, int size, int lim)
{
    srand(time(0));
    Arr[0] = INT_MIN;
    for (int i = 1; i <= size; i++)
        Arr[i] = (rand() % lim) + 1;
}

void PrintArray(int* Arr, int size)
{
    for (int i = 1; i <= size; i++)
        cout << Arr[i] << " ";
}

void PrintSchedule(char* Arr, int size)
{
    for (int i = 1; i <= size; i++)
    {
        if (Arr[i] == 'm')
            cout << "move ";
        else
            cout << Arr[i] << " ";
    }
}

int ScheduleTimeProcessingPower(int* A, int* B, int n)
{
    int a = 1, b = 1, ka = 0, kb = 0;
    int X[1000], Y[1000];
    char ScheduleA[1000], ScheduleB[1000];
    for (int i = 0; i <= n; i++)
    {
        X[i] = A[i];
        Y[i] = B[i];
    }
    for (int i = 2; i <= n; i++)
    {
        if (X[i-1] >= Y[i-2])
        {
            ScheduleA[a++] = 65+ka;
            X[i] += X[i-1];
        }
        else if (X[i-1] < Y[i-2])
        {
            ScheduleA[a++] = 'm';
            ScheduleA[a++] = 66-ka;
            if (ka == 0) ka = 1;
            else         ka = 0;
            X[i] += Y[i-2];
        }
        if (Y[i-1] >= X[i-2])
        {
            ScheduleB[b++] = 66-kb;
            Y[i] += Y[i-1];
        }
        else if (Y[i-1] < X[i-2])
        {
            ScheduleB[b++] = 'm';
            ScheduleB[b++] = 65+kb;
            if (kb == 0) kb = 1;
            else         kb = 0;
            Y[i] += X[i-2];
        }

        //X[i] += max(X[i-1], Y[i-2]);
        //Y[i] += max(Y[i-1], X[i-2]);
    }

    cout << "\n\nRequired Time Flow Scheduling Plan with Machine Transfers: \n";
    if (X[n] >= Y[n])
        PrintSchedule(ScheduleA, n);
    else
        PrintSchedule(ScheduleB, n);

    return max(X[n], Y[n]);
}


int main()
{
system("CLS");

    srand(time(0));
    int A[1000], B[1000], n = 3, limA = 10, limB = 10;
    //int A[] = {4, 8, 3, 90, 65, 12, 0, 69, 89};
    //cout << sizeof(A);
    //int C[] = {-100, 3, 1, 1};
    //int D[] = {-100, 1, 1, 8};

    
    cout << "\nEnter Flow Schedule Time-span: "; cin >> n;
    cout << "\nEnter MAX_RANGE of Assembly Line Processing Powers for Machine A: "; cin >> limA;
    RandomArrayGenerator(A, n, limA);
    cout << "\nEnter MAX_RANGE of Assembly Line Processing Powers for Machine B: "; cin >> limB;
    RandomArrayGenerator(B, n, limB);
    
    cout << "\nGiven Processing Power Table at ith minute for machines A, B: ";
    cout << "\n\tA: "; PrintArray(A, n);
    cout << "\n\tB: "; PrintArray(B, n);
    
    int optimus = ScheduleTimeProcessingPower(A, B, n);
    //cout << "\n\nRequired Time Flow Scheduling Plan: \n";
    //PrintSchedule(Schedule, n);
    cout << "\nOptimal Plan Value: " << optimus << "\n\n";

system("PAUSE");
return 0;
}