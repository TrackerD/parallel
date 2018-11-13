#include "pch.h"
#include "Task6L2.h"

void Task6L2::DoTaskSerial(ArrayInfo arrayInfo)
{
	/*double *arr = ConvertToODArr(arrayInfo);
	PrintText("\nBubbleSort\n");
	StartClock();
	bubbleSort(arr, arrayInfo.GetLength());
	ShowTime();*/
	double *arrx = ConvertToODArr(arrayInfo);
	PrintText("\nQuickSort\n");
	StartClock();
	quickSort_co(arrx, arrayInfo.GetLength());
	ShowTime();
	printf("TIME = %f\n", serTime);

	printf("ARR[%d] = %f\n", 0, arrx[0]);

}

void Task6L2::DoTaskParallel(ArrayInfo arrayInfo)
{
	//double *arr = ConvertToODArr(arrayInfo);
	//PrintText("\nBubbleSort\n");
	//StartClock(true);
	//bubbleSortP(arr, arrayInfo.GetLength());
	//ShowTime(true);
	double *arrx = ConvertToODArr(arrayInfo);
	PrintText("\nQuickSort\n");
	StartClock(true);
	quickSort_parallel(arrx, arrayInfo.GetLength());
	ShowTime(true);
	printf("TIME = %f\n", parTime);

	printf("ARR[%d] = %f\n", 0, arrx[0]);
}

Task6L2::~Task6L2()
{
}
