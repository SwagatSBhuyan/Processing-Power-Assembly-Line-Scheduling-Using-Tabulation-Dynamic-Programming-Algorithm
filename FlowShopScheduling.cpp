#include <bits/stdc++.h>

using namespace std;


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

int ScheduleTimeProcessingPower(int* A, int* B, char* Schedule, int n)
{
    int optimus = 0, i = 0, track = -1;

    while (i < n-1)
    {
        
        if (track == -1)
        {
            
            if (A[i+1] + A[i+2] > B[i+1] + B[i+2])
            {
                //cout << "\n1\n";
                i++;
                optimus += A[i];
                Schedule[i] = 'A';
                track = 0;
            }
            else if (A[i+1] + A[i+2] < B[i+1] + B[i+2])
            {
                //cout << "\n2\n";
                i++;
                optimus += B[i];
                Schedule[i] = 'B';
                track = 1;
            }
            else
            {
                if (ArraySum(A, n, i+1) >= ArraySum(B, n, i+1))
                {
                    //cout << "\n1\n";
                    i++;
                    optimus += A[i];
                    Schedule[i] = 'A';
                    track = 0;
                }
                else if (ArraySum(A, n, i+1) <= ArraySum(B, n, i+1))
                {
                    //cout << "\n2\n";
                    i++;
                    optimus += B[i];
                    Schedule[i] = 'B';
                    track = 1;
                }
                else
                {                
                    for (int k = 1; k <= n; k++)
                        Schedule[k] = 'A';
                    return ArraySum(A, n, i+1);
                }
            }

        }

        else if (track == 0)
        {
            if (ArraySum(A, n, i+1) >= ArraySum(B, n, i+2))
            {
                //cout << "\n3\n";
                optimus += A[i+1];
                Schedule[i+1] = 'A';
                i++;
                track = 0;
            }
            else
            {
                //cout << "\n4\n";
                optimus += B[i+2];
                Schedule[i+1] = 'm';
                Schedule[i+2] = 'B';
                i += 2;
                track = 1;
            }
        }

        else if (track == 1)
        {
            if (ArraySum(A, n, i+2) > ArraySum(B, n, i+1))
            {
                //cout << "\n5\n";
                optimus += A[i+2];
                Schedule[i+1] = 'm';
                Schedule[i+2] = 'A';
                i += 2;
                track = 0;
            }
            else
            {
                //cout << "\n6\n";
                optimus += B[i+1];
                Schedule[i+1] = 'B';
                i++;
                track = 1;
            }   
        }

    }

    if (i == n - 1)
    {
        if (track == 0)
        {
            optimus += A[i+1];
            Schedule[i] = 'A';
            Schedule[i+1] = 'A';
            return optimus;
        }
        if (track == 1)
        {
            optimus += B[i+1];
            Schedule[i] = 'B';
            Schedule[i+1] = 'B';
            return optimus;
        }
    }
    if (i == n)
        return optimus;

}


int main()
{
system("CLS");

    srand(time(0));
    int A[1000], B[1000], n = 6, limA = 10, limB = 10;
    char Schedule[1000];
    //int A[] = {4, 8, 3, 90, 65, 12, 0, 69, 89};
    //cout << sizeof(A);
    int C[] = {0, 2, 8, 2, 1, 1, 1};
    int D[] = {0, 3, 2, 1, 8, 8, 8};

    /*
    cout << "\nEnter Flow Schedule Time-span: "; cin >> n;
    cout << "\nEnter A Content MAX_RANGE: "; cin >> limA;
    RandomArrayGenerator(A, n, limA);
    cout << "\nEnter B Content MAX_RANGE: "; cin >> limB;
    RandomArrayGenerator(B, n, limB);
    */
    cout << "\nGiven Processing Power Table at ith minute for machines A, B: ";
    cout << "\n\tA: "; PrintArray(C, n);
    cout << "\n\tB: "; PrintArray(D, n);


    int optimus = ScheduleTimeProcessingPower(C, D, Schedule, n);
    cout << "\n\nRequired Time Flow Scheduling Plan: \n";
    PrintSchedule(Schedule, n);
    cout << "\nOptimal Plan Value: " << optimus << "\n\n";

system("PAUSE");
return 0;
}