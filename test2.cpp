#include <iostream>
#include <thread>
#include "omp.h"

using namespace std;

int main()
{
    const int processor_count = std::thread::hardware_concurrency();

   //������ 2
#pragma omp for
    for (int i = 0; i < processor_count; i++) {
        cout << "Hello world!" << endl;
    }

    //������ 3
    for (int i = 0; i < processor_count; i++) {
#pragma omp critical
        {
            cout << "I am " << i << " thread from " << processor_count << " threads!" << endl;
        }
    }
    
    //������ 4
    int k, rank; 
    cout << "Enter the number of threadsfrom 1 to " << processor_count << ":";
    cin >> k;

#pragma omp parallel num_threads(k) private(rank)
    {
#pragma omp critical
        {
            rank = omp_get_thread_num();
            cout << "I am " << rank << " thread" << endl;
        }
    }

    //������ 5
    int N;
        
    cout << "Enter the number of threads from 1 to " << processor_count << ":";
    cin >> k;

    cout << "Enter the number of numbers: ";
    cin >> N;

    int sum = 0;

#pragma omp parallel num_threads(k) reduction(+:sum)
    {
        int num = omp_get_thread_num();
        int part_sum = 0;

        for (int i = num + 1; i <= N; i += k) {
            part_sum += i;
        }
#pragma omp critical
        {
        cout << "[" << num << "] : Sum = " << part_sum << endl;
        }
        sum += part_sum;
    }

    cout << "Sum = " << sum << endl;

    return 0;
}
