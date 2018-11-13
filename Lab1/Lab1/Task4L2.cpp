#include "pch.h"
#include "Task4L2.h"

void Task4L2::DoTaskSerial(ArrayInfo arrayInfo)
{
	double *d = (double *)calloc(arrayInfo.rows*arrayInfo.cols, sizeof(double));
	double *arr1 = ConvertToODArr(arrayInfo);
	int i, j, k;
	StartClock();
	double *arr2 = transp(arr1, arrayInfo.rows, arrayInfo.cols);
	int n = arrayInfo.rows, m = arrayInfo.cols;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			for (k = 0; k < m; ++k) {
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
	double *d = (double *)calloc(arrayInfo.rows*arrayInfo.cols, sizeof(double));
	double *arr1 = ConvertToODArr(arrayInfo);
	int i, j, k;
	double *arr2 = transpParallel(arr1, arrayInfo.rows, arrayInfo.cols);
	int n = arrayInfo.rows, m = arrayInfo.cols;
	StartClock(true);
#pragma omp parallel for private (i,k,j) shared(n,m)
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			for (k = 0; k < m; ++k) {
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
