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
	ShowTime();
	PrintText(("Cascade Summing Result: " + to_string(arr[0])).c_str());
}

void Task2L2::DoTaskParallel(ArrayInfo arrayInfo)
{
	double * arr = ConvertToODArr(arrayInfo);
	int length = arrayInfo.rows * arrayInfo.cols;
	int i;
	StartClock();
	PairwiseSum(arr, 8, true);
//	for (int step = 1; step < length; step *= 2) {
//#pragma omp parallel for schedule(dynamic, arrayInfo.rows) private(i) default(shared)
//		for (i = step; i < length; i += 2 * step)
//			arr[i - step] += arr[i];
//	}
//#pragma omp parallel for schedule(dynamic,  arrayInfo.rows) private(step, i) default(shared)
//		for (step = 0; step < length; step++) {
//			if (PowerOfTwo(step)) {
//				{
//					for (i = step; i < length; i += 2 * step) {
//						arr[i - step] += arr[i];
//					}
//				}
//			}
//
//		}
	ShowTime(true);
	PrintText(("Cascade Summing Result: " + to_string(arr[0])).c_str());
}

Task2L2::~Task2L2()
{
}
