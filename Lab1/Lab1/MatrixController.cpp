#include "pch.h"
#include "MatrixController.h"
#include "IOController.h"
#include <stdio.h> 
#include <iostream>
#include <list> 
#include <string>
#include <omp.h>
#include <vector>
#include "ArrayInfo.h"

using namespace std;

vector<ArrayInfo> matrices;

void MatrixController::Load()
{
	printf("Matrix loading...\n");
	IOController ioc;

	CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\9.txt").c_str(), 3, 3, false);

	CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\44.txt").c_str(), 4, 4, false);

	//CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\100.txt").c_str(), 10, 10, false);
	//CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\1000.txt").c_str(), 100, 10, false);
	//CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\2000.txt").c_str(), 100, 20, false);
	CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\4000.txt").c_str(), 100, 40, false);
	//CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\6000.txt").c_str(), 100, 60, false);
	//CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\8000.txt").c_str(), 100, 80, false);
	//CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\10000.txt").c_str(), 100, 100, false);
	//CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\200200.txt").c_str(), 200, 200, false);
	//CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\400400.txt").c_str(), 400, 400, false);
	//CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\500500.txt").c_str(), 500, 500, false);
	//CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\800800.txt").c_str(), 800, 800, false);
	//CheckMatrix((string(ioc.current_work_dir) + "\\Matrix\\1000000.txt").c_str(), 1000, 1000, false);
	matrixIds = new long[matrices.size()];
	for (int i = 0; i < matrices.size(); i++)
		matrixIds[i] = matrices[i].id;
}

ArrayInfo MatrixController::GetMatrixInfo(long _id)
{
	for (int i = 0; i < matrices.size(); i++) {
		if (matrices[i].id == _id) return matrices[i];
	}
	cout << "Matrix not defined" << endl;
	return ArrayInfo();
}

double GetRandomDouble(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}


double ** MatrixController::CreateMatrix(const char * path, int rows, int cols, bool consoleDebug)
{
	FILE *OutputFile;
	double** matrix = 0;
	matrix = new double*[rows];
	fopen_s(&OutputFile, path, "w+");
	for (int i = 0; i < rows; i++) {
		matrix[i] = new double[cols];
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = GetRandomDouble(-100,100);
			if (consoleDebug) printf("%.2f ", matrix[i][j]);

			fprintf(OutputFile, "%.0f ", matrix[i][j]);
		}
		if (consoleDebug) printf("\n");
		fprintf(OutputFile, "\n");
	}
	fclose(OutputFile);
	return matrix;
}

double ** MatrixController::LoadMatrix(const char * path, int rows, int cols, bool consoleDebug)
{
	double** matrix = 0;
	matrix = new double*[rows];
	ifstream in(path);
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new double[cols];
		for (int j = 0; j < cols; j++)
		{
			
			in >> matrix[i][j];
			if (consoleDebug) printf("%f ", matrix[i][j]);
		}
		if (consoleDebug) cout << endl;
	}
	in.close();
	return matrix;
}

void MatrixController::CheckMatrix(const char * path, int rows, int cols, bool consoleDebug)
{
	IOController ioc;
	ArrayInfo info;
	info.id = rows * cols;
	info.cols = cols;
	info.rows = rows;
	if (ioc.FileExists(path)) {
		cout << "Loading Matrix: " + string(path) << endl;
		info.arr = LoadMatrix(path, rows, cols, consoleDebug);
		matrices.push_back(info);
	}
	else
	{
		cout << "Creating Matrix: " + string(path) << endl;
		info.arr = CreateMatrix(path, rows, cols, consoleDebug);
		matrices.push_back(info);
		
	}
}

int MatrixController::GetSize()
{
	return matrices.size();
}

MatrixController::~MatrixController()
{

}
