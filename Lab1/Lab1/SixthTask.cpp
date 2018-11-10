#include "pch.h"
#include "SixthTask.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

SixthTask::~SixthTask()
{
}

void SixthTask::DoTaskSerial(ArrayInfo arrayInfo)
{
	double *in = (double *)calloc(arrayInfo.rows, sizeof(double));
	double *M = ConvertToODArr(arrayInfo);
	double *vec = (double *)malloc(arrayInfo.cols * sizeof(double));
	
	for (int i = 0; i < arrayInfo.cols; i++)
		vec[i] = GetRandomDouble(0, 100);
	StartClock();
	for (int i = 0; i < arrayInfo.rows; i++)
	{
		for (int j = 0; j < arrayInfo.cols; j++)
			in[i] += M[i*arrayInfo.cols + j] * vec[j];
	}
	ShowTime();
}

double SixthTask::GetRandomDouble(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void SixthTask::DoTaskParallel(ArrayInfo arrayInfo)
{
	double *in = (double *)calloc(arrayInfo.rows, sizeof(double));
	double *M = ConvertToODArr(arrayInfo);
	double *vec = (double *)malloc(arrayInfo.rows * sizeof(double));

	for (int i = 0; i < arrayInfo.rows; i++)
		vec[i] = GetRandomDouble(0, 100);
	StartClock(true);
#pragma omp parallel for schedule(runtime)
	for (int i = 0; i < arrayInfo.rows; i++)
	{
		for (int j = 0; j < arrayInfo.cols; j++)
			in[i] += M[i*arrayInfo.cols + j] * vec[j];
	}
	ShowTime(true);
	fprintf(OutputFile, "\nResult Array: \n");
	for(int i =0; i < arrayInfo.rows;i++)
		fprintf(OutputFile, "%.2f ", in[i]);
}
