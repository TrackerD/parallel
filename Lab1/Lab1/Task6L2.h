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
		int maxThreads = 32;
#pragma omp parallel
		{
#pragma omp single nowait
			{
				quickSort_parallel(array, 0, lenArray - 1, maxThreads);
			}
		}
	}
	void quickSort_co(double* array, int lenArray) {
		quickSort_serial(array, 0, lenArray - 1);
	}
	

	void quickSort_parallel(double* arr, int left, int right,int threads)
	{
		int i = left, j = right;
		int tmp;
		int pivot = arr[(left + right) / 2];

		/* PARTITION PART */
		while (i <= j) {
			while (arr[i] < pivot)
				i++;
			while (arr[j] > pivot)
				j--;
			if (i <= j) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				i++;
				j--;
			}
		}

		/* RECURSION PART */
#pragma omp parallel sections if(threads > 1)
		{
#pragma omp section
			if (left < j) {
				quickSort_parallel(arr, left, j, threads/2);
			}
#pragma omp section
			if (i < right) {
				quickSort_parallel(arr, i, right, threads/2);
			}
		}
	}
	void quickSort_serial(double* arr, int left, int right)
	{
		int i = left, j = right;
		int tmp;
		int pivot = arr[(left + right) / 2];

		/* PARTITION PART */
		while (i <= j) {
			while (arr[i] < pivot)
				i++;
			while (arr[j] > pivot)
				j--;
			if (i <= j) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				i++;
				j--;
			}
		}

		/* RECURSION PART */
		if (left < j) {
			quickSort_serial(arr, left, j);
		}
		if (i < right) {
			quickSort_serial(arr, i, right);
		}
	}
};

