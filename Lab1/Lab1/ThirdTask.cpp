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
	double*arr = ConvertToODArr(arrayInfo);
	int counter = 0;
	int i;
	StartClock();
	int n = arrayInfo.rows, m = arrayInfo.cols;
	for (i = 0; i < n*m; i++) {
		if (arr[i] > min && arr[i] < max) {
			counter++;
		}
	}
	ShowTime();
	printf("Counter = %d\n", counter);

}

void ThirdTask::DoTaskParallel(ArrayInfo arrayInfo)
{
	double*arr = ConvertToODArr(arrayInfo);
	int counter = 0;
	int i;
	StartClock(true);
	int n = arrayInfo.rows, m = arrayInfo.cols;
#pragma omp parallel for reduction(+:counter) schedule (dynamic, n) private(i)
	for (i = 0; i < n*m; i++) {
		if (arr[i] > min && arr[i] < max) {
			counter++;
		}
	}
	ShowTime(true);
	printf("Counter = %d\n", counter);
}
