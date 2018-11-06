#include "pch.h"
#include "BaseTask.h"
#include "IOController.h"
#include <time.h>
#include <omp.h>
#include "ArrayInfo.h"

void BaseTask::StartClock()
{
	//start = clock();
	e1 = omp_get_wtime();
}

void BaseTask::ShowTime(bool parallel)
{
	//end = clock();
	char buff[120];
	e2 = omp_get_wtime();

	//double time = ((long double)end - start) / ((long double)CLOCKS_PER_SEC);
	double time = e2 - e1;

	snprintf(buff, sizeof(buff), "The above code block was executed in %.25f second(s)\n", time);
	PrintText(buff);
	if (parallel)
		totalParallelTime += time;
	else
		totalConsistentTime += time;
}

void BaseTask::DoAll()
{
	IOController ioc;
	OutputFile = ioc.WriteTaskFile(taskIndex, labIndex);
	for (int i = 0; i < 3; i++)
		printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	totalConsistentTime = 0;
	totalParallelTime = 0;
	for (int i = 0; i < matrixController.GetSize(); i++) {
		ArrayInfo arrayInfo = matrixController.GetMatrixInfo(matrixController.matrixIds[i]);
		PrintText(("\nExecuting task " + to_string(taskIndex) + " with array id: " + to_string(matrixController.matrixIds[i]) + "\n").c_str());
		PrintText("\nSerial:\n");
		DoTaskSerial(arrayInfo);
		PrintText("\nParralel:\n");
		DoTaskParallel(arrayInfo);
		PrintText("\n=========================================================\n");
	}
	PrintText("=========================================================\n");
	PrintText(("Total Serial Time: " + to_string(totalConsistentTime)).c_str());
	PrintText(("\nTotal Parallel Time: " + to_string(totalParallelTime)).c_str());
	PrintText(("\nParallel faster: " + to_string(totalConsistentTime / totalParallelTime)).c_str());
	PrintText("\n=========================================================\n");
	PrintText("=========================================================\n");


	fclose(OutputFile);
}

void BaseTask::PrintText(const char * text) {
	printf(text);
	fprintf(OutputFile, text);
}

BaseTask::~BaseTask()
{
}

BaseTask::BaseTask(MatrixController m, int labIndex, int taskIndex)
{
	this->matrixController = m;
	this->labIndex = labIndex;
	this->taskIndex = taskIndex;
}

double* BaseTask::ConvertToODArr(ArrayInfo info) {
	double* arr = 0;
	arr = new double[info.rows * info.cols];
	int counter = 0;
	for (int i = 0; i < info.rows; i++) {
		for (int j = 0; j < info.cols; j++) {
			arr[counter] = info.arr[i][j];
			counter++;
		}
	}
	return arr;
}

double * BaseTask::ConvertToODArr(double ** _arr, int rows, int cols)
{
	double* arr = 0;
	arr = new double[rows * cols];
	int counter = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			arr[counter] = _arr[i][j];
			counter++;
		}
	}
	return arr;
}
