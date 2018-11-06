#include "pch.h"
#include "Task5L2.h"


void Task5L2::DoTaskSerial(ArrayInfo arrayInfo)
{
	double * arr = ConvertToODArr(arrayInfo);
	double min_val = arr[0];
	int i;
	StartClock();

	for (i = 0; i < arrayInfo.GetLength(); i++)
	{
		if (arr[i] < min_val)
		{
			min_val = arr[i];
		}
	}
	ShowTime();
	PrintText(("min = " + to_string(min_val)).c_str());
}

void Task5L2::DoTaskParallel(ArrayInfo arrayInfo)
{
	double * arr = ConvertToODArr(arrayInfo);
	double min_val = arr[0];
	int i;
	StartClock();
#pragma omp parallel for
	for (i = 0; i < arrayInfo.GetLength(); i++)
	{
#pragma omp flush(min_val)
		if (arr[i] < min_val)
		{
#pragma omp critical
			{
				if (arr[i] < min_val) min_val = arr[i];
			}
		}
	}
	ShowTime(true);
	PrintText(("min = " + to_string(min_val)).c_str());
}

Task5L2::~Task5L2()
{
}
