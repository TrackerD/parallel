#pragma once
#include "BaseTask.h"
class Task2L2 :
	public BaseTask
{
public:
	using BaseTask::BaseTask;
	void DoTaskSerial(ArrayInfo arrayInfo) override;
	void DoTaskParallel(ArrayInfo arrayInfo) override;
	~Task2L2();
private:
	bool PowerOfTwo(int &Value)
	{
		int InitValue = 1;
		while (InitValue < Value)
			InitValue *= 2;
		if (InitValue == Value)
			return true;
		return false;
	}

	void PairwiseSum(double* array, int threads, bool useOmp)
	{
		int resultSize = (threads % 2 == 0) ? (threads / 2) : (threads / 2 + 1);
		double* result = (double*)malloc(resultSize * sizeof(double));
		int i, resultIterator = 0;
		double sum = 0;

#pragma omp parallel private(i, sum) if(useOmp) num_threads(threads)
		{
#pragma omp for schedule(runtime)
			for (i = 0; i < threads; i += 2)
			{
				if (i + 1 == threads)
					sum = array[i];
				else
				{
					sum = array[i] + array[i + 1];
					//printf("\nic = %d, thread# %d, array[i] = %f, array[i+1] = %f, sum = %f\n", iterationCounter, omp_get_thread_num(), array[i], array[i + 1], sum);
				}
				result[omp_get_thread_num()] = sum;
			}
		}

		if (resultSize == 1)
		{
			printf("\n>>>sum = %f<<<\n", result[0]);
		}
		else PairwiseSum(result, resultSize, useOmp);
	}
};

