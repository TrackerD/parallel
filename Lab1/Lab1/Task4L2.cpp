#include "pch.h"
#include "Task4L2.h"

void Task4L2::DoTaskSerial(ArrayInfo arrayInfo)
{
	if (arrayInfo.rows != arrayInfo.cols) {
		PrintText("Matrix Not Square");
		return;
	}
	double *d = (double *)calloc(arrayInfo.rows*arrayInfo.cols, sizeof(double));
	double *arr1 = ConvertToODArr(arrayInfo);
	int i, j, k;
	StartClock();
	double *arr2 = transp(arr1, arrayInfo.rows, arrayInfo.cols);
	int n = arrayInfo.rows, m = arrayInfo.cols;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				d[i*m + j] += arr1[i*m + k] * arr2[j*m + k];
			}
		}
	}
	ShowTime(false);
	fprintf(OutputFile, "\nResult Array: \n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			fprintf(OutputFile, "%.2f ", d[i*m + j]);
		}
		fprintf(OutputFile, "\n");
	}
}

void Task4L2::DoTaskParallel(ArrayInfo arrayInfo)
{
	if (arrayInfo.rows != arrayInfo.cols) {
		PrintText("Matrix Not Square");
		return;
	}
	double *d = (double *)calloc(arrayInfo.rows*arrayInfo.cols, sizeof(double));
	double *arr1 = ConvertToODArr(arrayInfo);
	int i, j, k;
	StartClock(true);
	double *arr2 = transpParallel(arr1, arrayInfo.rows, arrayInfo.cols);
	int n = arrayInfo.rows, m = arrayInfo.cols;
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				d[i*m + j] += arr1[i*m + k] * arr2[j*m + k];
			}
		}
	}
	ShowTime(true);
	fprintf(OutputFile, "\nResult Array: \n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			fprintf(OutputFile, "%.2f ", d[i*m + j]);
		}
		fprintf(OutputFile, "\n");
	}
}

Task4L2::~Task4L2()
{
}
