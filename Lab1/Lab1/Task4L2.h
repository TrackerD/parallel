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
	double *transp(double *arr, int n, int m)
	{
		double *tmp = (double *)calloc(n*m, sizeof(double));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				tmp[i*m + j] = arr[j*m + i];
			}
		}
		return tmp;
	}
	double *transpParallel(double *arr, int n, int m)
	{
		double *tmp = (double *)calloc(n*m, sizeof(double));
#pragma omp parallel for
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				tmp[i*m + j] = arr[j*m + i];
			}
		}
		return tmp;
	}
};

