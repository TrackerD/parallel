#include "MatrixController.h"
#include <ctime>
#include "IOController.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <omp.h>
#include <stdio.h> 
#include <direct.h>
#include <io.h>
#pragma once
class BaseTask
{
public:
	void StartClock(bool parallel = false);
	virtual void ShowTime(bool parallel = false);
	virtual void DoAll();
	~BaseTask();
	explicit BaseTask(MatrixController m, int labIndex, int taskIndex);
protected:
	int taskIndex = 0;
	int labIndex = 0;
	virtual void DoTaskSerial(ArrayInfo arrayInfo) = 0;
	virtual void DoTaskParallel(ArrayInfo arrayInfo) = 0;
	void PrintText(const char * text);
	double*ConvertToODArr(ArrayInfo info);
	double*ConvertToODArr(double ** _arr, int rows, int cols);
	MatrixController matrixController;
	clock_t start, end;
	FILE *OutputFile;
	long double totalConsistentTime, totalParallelTime, serTime, parTime;
	double e1, e2;
};

