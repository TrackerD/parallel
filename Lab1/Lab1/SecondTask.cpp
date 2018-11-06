#include "pch.h"
#include "SecondTask.h"
#include <stdio.h> 
#include "omp.h";

SecondTask::~SecondTask()
{
}

void SecondTask::DoTaskSerial(ArrayInfo arrayInfo)
{
	int arrayLength = GetNonZeroCount(arrayInfo);
	int counter = 0;
	double*arr = new double[arrayLength];
	StartClock();
	for (int i = 0; i < arrayInfo.rows; i++) {
		for (int j = 0; j < arrayInfo.cols; j++) {
			if (arrayInfo.arr[i][j] != 0) {
				arr[counter] = arrayInfo.arr[i][j];
				++counter;
			}
		}
	}
	ShowTime();
	printf("Non zero items count: %d\n", arrayLength);
	fprintf(OutputFile, "\nResult Array: \n");
	for (int i = 0; i < counter; i++)
		fprintf(OutputFile, "%.2f ", arr[i]);
}

int SecondTask::GetNonZeroCount(ArrayInfo info) {
	int result = info.rows * info.cols;
	for (int i = 0; i < info.rows; i++) {
		for (int j = 0; j < info.cols; j++) {
			if (info.arr[i][j] == 0) {
				--result;
			}
		}
	}
	return result;
}

void SecondTask::DoTaskParallel(ArrayInfo arrayInfo)
{
	int arrayLength = GetNonZeroCount(arrayInfo);
	int counter = 0;
	double*arr = new double[arrayLength];
	StartClock();
#pragma omp parallel for reduction(+:counter)
	for (int i = 0; i < arrayInfo.rows; i++) {
		for (int j = 0; j < arrayInfo.cols; j++) {
			if (arrayInfo.arr[i][j] != 0) {
				arr[counter] = arrayInfo.arr[i][j];
				++counter;
			}
		}
	}

	ShowTime(true);
	printf("Non zero items count: %d\n", arrayLength);
	fprintf(OutputFile, "Non zero items count: %d\n", arrayLength);

}
