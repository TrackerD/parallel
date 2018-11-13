#pragma once
#include "BaseTask.h"
class Task2L2 :
	public BaseTask
{
public:
	using BaseTask::BaseTask;
	void DoTaskSerial(ArrayInfo arrayInfo) override;
	void DoTaskParallel(ArrayInfo arrayInfo) override;
	void ShowTime(bool parallel = false) override;

	~Task2L2();
private:
	double parallelTime;
	bool PowerOfTwo(int &Value)
	{
		int InitValue = 1;
		while (InitValue < Value)
			InitValue *= 2;
		if (InitValue == Value)
			return true;
		return false;
	}

	void CascadeSum(double* arr, int length, double res = 0)
	{
		int n = length % 2 == 0 ? n = length : n = length - 1;
		
		int i;
		double * result = (double*)malloc(n/2 * sizeof(double));
		int threadCount;
		if (n/2 > 8)
			threadCount = 8;
		else if (n == 1)
			return;
		else threadCount = n / 2;

		if (length % 2 != 0) {
			res += arr[length - 1];
		}
		StartClock(true);

#pragma omp parallel default(none) private(i) shared(arr, n, result, threadCount) num_threads(threadCount)
		{
			int num_threads = omp_get_num_threads();
			int threadNum = omp_get_thread_num();
			int start = threadNum * n / num_threads;
			if (start % 2 != 0) start += 1;
			int finish = (threadNum + 1)*n / num_threads;

#pragma omp single
			{
				num_threads = omp_get_num_threads();
			}
			int index = start/2;

			for (i = start; i < finish; i += 2) {
				result[index] = arr[i] + arr[i + 1];
				//printf("arr[%d] = %f, arr2[%d] = %f,, RESULT[%d] = %f\n", i, arr[i], i+1, arr[i+1],index, result[index]);
				index++;
			}


#pragma omp barrier
		}
		ShowTime(true);
		if (n / 2 > 1) {
			CascadeSum(result, n/2, res);
		}
		else {
			totalParallelTime += parallelTime;
			printf("\nRESULT = %f\n", result[0] + res);
			printf("TIME = %.25f\n", parallelTime);
			PrintText("=========================================================\n");
			PrintText(("Serial Time: " + to_string(serTime)).c_str());
			PrintText(("\nParallel Time: " + to_string(parallelTime)).c_str());
			PrintText(("\nParallel faster: " + to_string(serTime / parallelTime)).c_str());
			PrintText("\n=========================================================\n");
			PrintText("=========================================================\n");
		}
	}
	void CascadeSumOptimized(double *arr, int startLength)
	{
		int n = startLength % 2 == 0 ? n = startLength : n = startLength - 1;
		int i;
		int threadCount;
		if (startLength % 2 != 0)
			startLength -= 1;
		int iterationCounter = 1;
		while (n > 1) {
			int temp = 1 << iterationCounter;
			int temp2 = 1 << (iterationCounter - 1);
			if (n / 2 > 8)
				threadCount = 8;
			else threadCount = n / 2;
			StartClock(true);
#pragma omp parallel default(none) private(i) shared(arr, n, threadCount, temp, temp2, startLength) num_threads(threadCount)
			{
				int threadNum = omp_get_thread_num();
				int start = threadNum * startLength / threadCount;
				if (start % 2 != 0) start += 1;
				int finish = (threadNum + 1)*startLength / threadCount;

				for (i = start; i < finish; i += temp) {
					if (i + temp2 < startLength) {
						//printf("arr[%d] = %f, arr2[%d] = %f, RESULT = %f\n", i, arr[i], i + temp2, arr[i + temp2], arr[i] + arr[i+temp2]);

						arr[i] += arr[i + temp2];

					}
					else 
						arr[startLength] += arr[i];
				}
			}
			ShowTime(true);
			n /= 2;
			iterationCounter++;
		}

		printf("\nRESULT = %f\n", arr[0] + arr[startLength]);
		printf("TIME = %.25f\n", parallelTime);

	}

};

