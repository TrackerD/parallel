#include "pch.h"
#include "FirstTask.h"
#include <stdio.h> 
#include <direct.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "ArrayInfo.h"

using namespace std;

FirstTask::~FirstTask()
{
}

void FirstTask::DoAll() {
	cout << "Input coefficient: ";
	cin >> k;
	BaseTask::DoAll();
}

void FirstTask::DoTaskSerial(ArrayInfo arrayInfo)
{
	double sum = 0;
	double * arr = ConvertToODArr(arrayInfo);
	StartClock();

	for (int i = 0; i < arrayInfo.rows * arrayInfo.cols; i++) {
		sum += arr[i] * k;
	}
	ShowTime();
	printf("Sum = %.2f\n", sum);
	fprintf(OutputFile, "Sum = %.2f\n", sum);
}

void FirstTask::DoTaskParallel(ArrayInfo arrayInfo)
{
	double sum = 0;
	double * arr = ConvertToODArr(arrayInfo);
	StartClock(true);
	int i;
	int n = arrayInfo.rows, m = arrayInfo.cols;
#pragma omp parallel for default(shared) private(i)  \
		schedule(static, arrayInfo.rows)      \
		reduction(+:sum)
		for (i = 0; i < n * m; i++) {
			sum += arr[i] * k;
		}
		ShowTime(true);
	printf("Sum = %.2f\n", sum);
	fprintf(OutputFile, "Sum = %.2f\n", sum);
}