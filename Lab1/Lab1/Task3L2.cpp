#include "pch.h"
#include "Task3L2.h"
#include <math.h>
#include <stdio.h> 
void Task3L2::DoTaskSerial(ArrayInfo arrayInfo)
{

	double * arr = ConvertToODArr(arrayInfo);
	int n = arrayInfo.rows * arrayInfo.cols;

	int j;
	StartClock();
	for (j = 1; j < n; j++) {
			arr[j] = arr[j] + arr[j - 1];
	}
	ShowTime();
	fprintf(OutputFile, "\nResult Array: \n");
	for (int i = 0; i < n; i++)
			fprintf(OutputFile, "%.0f ", arr[i]);
	PrintText(("\nPrefix sum: " + to_string(arr[n - 1])).c_str());
}

void Task3L2::DoTaskParallel(ArrayInfo arrayInfo)
{
	double * arr = ConvertToODArr(arrayInfo);
	int n = arrayInfo.GetLength(), i;
	double *partial, *temp;
	StartClock();

#pragma omp parallel default(none) private(i) shared(arr, partial, temp, n)
	{
		int num_threads = omp_get_num_threads();
		int threadNum = omp_get_thread_num();
		const int start = threadNum * n / num_threads;
		const int finish = (threadNum + 1)*n / num_threads;
#pragma omp single
		{
			num_threads = omp_get_num_threads();
			partial = new double[num_threads];
			temp = new double[num_threads];

		}

		for (i = start + 1; i < finish; i++) {
			arr[i] += arr[i - 1];
		}
		partial[threadNum] = arr[i - 1];

#pragma omp barrier
		//calculate prefix sum for the array that was made from last elements of each of the previous sub-arrays
		for (i = 1; i < num_threads; i <<= 1) {
			if (threadNum >= i)
				temp[threadNum] = partial[threadNum] + partial[threadNum - i];
#pragma omp barrier
#pragma omp single
			{
				for (int x = 1; x < num_threads; x++)
					partial[x] = temp[x];
			}
		}
		for (i = start; i < finish; i++) {
			arr[i] += partial[threadNum] - arr[finish - 1];
		}

	}
	ShowTime(true);
	fprintf(OutputFile, "\nResult Array: \n");
	for (int i = 0; i < n; i++)
		fprintf(OutputFile, "%.0f ", arr[i]);
	PrintText(("\nPrefix sum: " + to_string(arr[n-1])).c_str());
}

Task3L2::~Task3L2()
{
}
