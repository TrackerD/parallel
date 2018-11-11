#include "pch.h"
#include "Task2L2.h"
#include <math.h>


void Task2L2::DoTaskSerial(ArrayInfo arrayInfo)
{

	double * arr = ConvertToODArr(arrayInfo);
	int length = arrayInfo.rows * arrayInfo.cols;

	int counter = 0;
	StartClock();
	for (int step = 1; step < length; step *= 2) {
		for (int i = step; i < length; i += 2 * step)
			arr[i - step] += arr[i];
	}
	BaseTask::ShowTime();
	PrintText(("Cascade Summing Result: " + to_string(arr[0])).c_str());
}

void Task2L2::DoTaskParallel(ArrayInfo arrayInfo)
{
	int n = arrayInfo.GetLength();
	parallelTime = 0;
	CascadeSum(ConvertToODArr(arrayInfo), arrayInfo.GetLength());
}

void Task2L2::ShowTime(bool parallel)
{
	//end = clock();
	e2 = omp_get_wtime();
	char buff[120];

	//double time = ((long double)end - start) / ((long double)CLOCKS_PER_SEC);
	double time = e2 - e1;
	parallelTime += time;
	snprintf(buff, sizeof(buff), "Iteration executed in %.25f second(s)\n", time);
	PrintText(buff);
}

Task2L2::~Task2L2()
{
}
