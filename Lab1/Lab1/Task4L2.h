#pragma once
#include "BaseTask.h"
class Task4L2 :
	public BaseTask
{
public:
	using BaseTask::BaseTask;
	void DoTaskSerial(ArrayInfo arrayInfo) override;
	void DoTaskParallel(ArrayInfo arrayInfo) override;
	~Task4L2();
private:
	double * transp(double *arr, int n, int m)
	{
		double *tmp = (double *)calloc(n*m, sizeof(double));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				tmp[i*m + j] = arr[j*m + i];
			}
		}
		return tmp;
	}
	double * transpParallel(double *arr, int n, int m)
	{
		double * tmp = (double *)calloc(n*m, sizeof(double));
		int i, j;
#pragma omp parallel for private(i,j) shared(n,m)
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				tmp[i*m + j] = arr[j*m + i];
			}
		}
		return tmp;
	}
};

