#pragma once
#include "BaseTask.h"
class Task3L2 :
	public BaseTask
{
public:
	using BaseTask::BaseTask;
	void DoTaskSerial(ArrayInfo arrayInfo) override;
	void DoTaskParallel(ArrayInfo arrayInfo) override;
	~Task3L2();
	void computeparallelprefix(double *iplist, double *_pprefixsum, unsigned long size)
	{
		int nthr;
		double *z, *x = _pprefixsum;
#pragma omp parallel
		{
			int i;
#pragma omp single
			{
				nthr = omp_get_num_threads();
				z = (double*)malloc(sizeof(double)*nthr + 1);
				z[0] = 0;
			}
			int tid = omp_get_thread_num();
			int sum = 0;
#pragma omp for schedule(static) 
			for (i = 0; i < size; i++) {
				sum += iplist[i];
				x[i] = sum;
			}
			z[tid + 1] = sum;
#pragma omp barrier

			int offset = 0;
			for (i = 0; i < (tid + 1); i++) {
				offset += z[i];
			}

#pragma omp for schedule(static)
			for (i = 0; i < size; i++) {
				x[i] += offset;
			}
		}
		free(z);
	}
};

