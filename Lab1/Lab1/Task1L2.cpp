#include "pch.h"
#include "Task1L2.h"
#include <stdio.h> 
#include <iostream>

void Task1L2::DoTaskSerial(ArrayInfo arrayInfo)
{
	double * arr = ConvertToODArr(arrayInfo);
	int positive = 0, negative = 0, zero = 0;
	StartClock();
	for (int i = 0; i < arrayInfo.rows * arrayInfo.cols; i++)
	{
		if (arr[i] > 0) {
			positive++;
		}
		else if (arr[i] < 0) {
			negative++;
		}
		else {
			zero++;
		}
	}
	ShowTime();
	PrintText(("\nPositiveCount: " + to_string(positive)).c_str());
	PrintText(("\nNegativeCount: " + to_string(negative)).c_str());
	PrintText(("\nZeroCount: " + to_string(zero)).c_str());
}

void Task1L2::DoTaskParallel(ArrayInfo arrayInfo)
{
	double *arr = ConvertToODArr(arrayInfo);
	StartClock(true);
	int totalPositive = 0, totalNegative = 0, totalZero = 0;
	int i;
#pragma omp parallel private(i)
	{
		int localPositive = 0, localNegative = 0, localZero = 0;
#pragma omp for schedule(dynamic, arrayInfo.rows/10)
		for (i = 0; i < arrayInfo.GetLength(); i++)
		{
			if (arr[i] > 0)
				localPositive++;
			else if (arr[i] < 0)
				localNegative++;
			else
				localZero++;
		}
#pragma omp critical(positiveCompleted)
		totalPositive += localPositive;
#pragma omp critical(negativeCompleted)
		totalNegative += localNegative;
#pragma omp critical(zeroCompleted)
		totalZero += localZero;
	}
	ShowTime(true);
	PrintText(("\nPositiveCount: " + to_string(totalPositive)).c_str());
	PrintText(("\nNegativeCount: " + to_string(totalNegative)).c_str());
	PrintText(("\nZeroCount: " + to_string(totalZero)).c_str());
}

Task1L2::~Task1L2()
{
}

