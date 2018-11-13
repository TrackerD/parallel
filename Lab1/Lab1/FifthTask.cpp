#include "pch.h"
#include "FifthTask.h"
#include <stdio.h> 
#include <iostream>


using namespace std;

FifthTask::~FifthTask()
{
}

void FifthTask::DoAll()
{
	do {
		printf("\nSet Limit: ");
		cin >> limit;
	} while (limit < 0);
	BaseTask::DoAll();
}

void FifthTask::DoTaskSerial(ArrayInfo arrayInfo)
{
	double summa = 0;
	double*odArr = ConvertToODArr(arrayInfo);
	double*newArr = (double *)calloc(arrayInfo.rows*arrayInfo.cols / limit, sizeof(double));
	fprintf(OutputFile, ("\nLimit: " + to_string(limit) +"\n").c_str());

	StartClock();
	for (int i = 0; i < arrayInfo.rows*arrayInfo.cols; i++) {
		if (i % limit == limit - 1 && i != 0)
		{
			summa += odArr[i];
			newArr[(i + 1) / limit] = summa / limit;
			summa = 0;
		}
		else {
			summa += odArr[i];
		}
	}
	ShowTime();
}

void FifthTask::DoTaskParallel(ArrayInfo arrayInfo)
{
	double summa = 0;
	double*odArr = ConvertToODArr(arrayInfo);
	double*newArr = (double *)calloc(arrayInfo.rows*arrayInfo.cols / limit, sizeof(double));
	int i;
	StartClock(true);
#pragma omp parallel for firstprivate(summa) schedule(dynamic, limit) private(i)
	for (i = 0; i < arrayInfo.rows*arrayInfo.cols; i++) {
		if (i % limit == limit - 1 && i != 0)
		{
			summa += odArr[i];
			newArr[(i + 1) / limit] = summa / limit;
			summa = 0;
		}
		else {
			summa += odArr[i];
		}
	}
	ShowTime(true);
	fprintf(OutputFile, "\nResult Array: \n");
	for (int i = 0; i < arrayInfo.rows*arrayInfo.cols / limit; i++)
		fprintf(OutputFile, "%.2f ", newArr[i]);
	fprintf(OutputFile, "\n");
}
