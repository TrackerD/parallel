#include "pch.h"
#include "ThirdTask.h"
#include <stdio.h> 
#include <iostream>


using namespace std;

ThirdTask::~ThirdTask()
{
}

void ThirdTask::DoAll()
{
	do {
		printf("\nSet Range:\nMin: ");
		cin >> min;
		printf("Max: ");
		cin >> max;
	} while (max - min <= 0 || min < 0);
	BaseTask::DoAll();
}

void ThirdTask::DoTaskSerial(ArrayInfo arrayInfo)
{
	if (arrayInfo.rows * arrayInfo.cols < max) {
		cout << "Too big max value. Skipped " << endl;
		return;
		/*cout << "Too big max value. New Max = " << arrayInfo.id - 1 << endl;
		max = arrayInfo.id - 1;*/
	}
	fprintf(OutputFile, "Max: %d ", max);
	fprintf(OutputFile, "Min: %d ", min);

	double*arr = ConvertToODArr(arrayInfo);
	int counter = 0;
	double* newArr = new double[max-min];
	StartClock();
	for (int i = 0; i < arrayInfo.rows * arrayInfo.cols; i++) {
		if (i > min && i < max) {
			newArr[counter] = arr[i];
			counter++;
		}
	}
	ShowTime();
	fprintf(OutputFile, "\nResult Array: \n");

	for (int i = 0; i < counter; i++)
		fprintf(OutputFile, "%.2f ", arr[i]);
	fprintf(OutputFile, "\n");

}

void ThirdTask::DoTaskParallel(ArrayInfo arrayInfo)
{
	if (arrayInfo.rows * arrayInfo.cols < max) {
		cout << "Too big max value. Skipped " << endl;
		return;
		/*cout << "Too big max value. New Max = " << arrayInfo.id - 1 << endl;
		max = arrayInfo.id - 1;*/
	}
	double*arr = ConvertToODArr(arrayInfo);
	int counter = 0;
	double* newArr = new double[max - min];
	StartClock(true);
#pragma omp parallel for reduction(+:counter)
	for (int i = 0; i < arrayInfo.rows * arrayInfo.cols; i++) {
		if (i > min && i < max) {
			newArr[counter] = arr[i];
			counter++;
		}
	}
	ShowTime(true);
}
