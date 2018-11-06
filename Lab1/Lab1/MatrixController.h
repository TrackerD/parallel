#include "ArrayInfo.h"
#pragma once
class MatrixController
{
public:
	void Load();
	ArrayInfo GetMatrixInfo(long _id);
	long*matrixIds;
	int GetSize();
	~MatrixController();
private:
	void CheckMatrix(const char * path, int rows, int cols, bool consoleDebug);
	double ** CreateMatrix(const char * path, int rows, int cols, bool consoleDebug);
	double ** LoadMatrix(const char * path, int rows, int cols, bool consoleDebug);
};

