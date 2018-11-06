#include "pch.h"
#include "FourthTask.h"
#include <stdio.h> 
#include "omp.h"
#include <iostream>

using namespace std;

FourthTask::~FourthTask()
{
}

void FourthTask::DoAll()
{
	do {
		cout << "\nInput zero index: ";
		cin >> index;
	} while (index < 0);
	BaseTask::DoAll();
}

void FourthTask::DoTaskSerial(ArrayInfo arrayInfo)
{
	int counter = 0;
	fprintf(OutputFile, "\nZero index: %d \n", index);

	StartClock();
	for (int i = 0; i < arrayInfo.rows; i++) {
		if (arrayInfo.arr[i][index] == 0)
			++counter;
	}
	ShowTime();
	printf("\nRows matching the given condition: %d\n", counter);
	fprintf(OutputFile, "\nRows matching the given condition: %d\n", counter);

}

void FourthTask::DoTaskParallel(ArrayInfo arrayInfo)
{
	int counter = 0;
	StartClock();
#pragma omp parallel for reduction(+:counter)
	for (int i = 0; i < arrayInfo.rows; i++) {
		if (arrayInfo.arr[i][index] == 0)
			++counter;
	}
	ShowTime(true);
	printf("\nRows matching the given condition: %d\n", counter);
}
