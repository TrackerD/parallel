#pragma once
#include "BaseTask.h"
class Task6L2 :
	public BaseTask
{
public:
	using BaseTask::BaseTask;
	void DoTaskSerial(ArrayInfo arrayInfo) override;
	void DoTaskParallel(ArrayInfo arrayInfo) override;
	~Task6L2();
	void swap(double *xp, double *yp)
	{
		int temp = *xp;
		*xp = *yp;
		*yp = temp;
	}

	void bubbleSort(double *arr, int n)
	{
		int i, j;
		for (i = 0; i < n - 1; i++)
			for (j = 0; j < n - i - 1; j++)
				if (arr[j] > arr[j + 1])
					swap(&arr[j], &arr[j + 1]);
	}

	void bubbleSortP(double *arr, int n)
	{
		int i, j;
		#pragma omp for schedule(dynamic, 10)
		for (i = 0; i < n - 1; i++)
			for (j = 0; j < n - i - 1; j++)
				if (arr[j] > arr[j + 1])
					swap(&arr[j], &arr[j + 1]);
	}
	void quickSort_parallel(double* array, int lenArray) {

		int cutoff = 1000;

#pragma omp parallel
		{
#pragma omp single nowait
			{
				quickSort_parallel_internal(array, 0, lenArray - 1, cutoff);
			}
		}
	}
	void quickSort_co(double* array, int lenArray) {

		int cutoff = 1000;
		quickSort_parallel_internal(array, 0, lenArray - 1, cutoff);

	}



	void quickSort_parallel_internal(double* array, int left, int right, int cutoff)
	{
		int i = left, j = right;
		int tmp;
		int pivot = array[(left + right) / 2];

		{
			/* PARTITION PART */
			while (i <= j) {
				while (array[i] < pivot)
					i++;
				while (array[j] > pivot)
					j--;
				if (i <= j) {
					tmp = array[i];
					array[i] = array[j];
					array[j] = tmp;
					i++;
					j--;
				}
			}

		}


		if (((right - left) < cutoff)) {
			if (left < j) { quickSort_parallel_internal(array, left, j, cutoff); }
			if (i < right) { quickSort_parallel_internal(array, i, right, cutoff); }

		}
		else {
			{ quickSort_parallel_internal(array, left, j, cutoff); }
			{ quickSort_parallel_internal(array, i, right, cutoff); }
		}

	}
};

