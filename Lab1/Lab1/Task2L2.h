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

	void CascadeSum(double* arr, int length, double res)
	{
		int n = length % 2 == 0 ? n = length : n = length - 1;
		
		int i;
		double * result = (double*)malloc(n/2 * sizeof(double));
		int threadCount;
		if (n > 8)
			threadCount = 8;
		else if (n == 1)
			return;
		else threadCount = n / 2;
		if (length % 2 != 0) {
			res += arr[length - 1];
		}
		StartClock(true);

#pragma omp parallel default(none) private(i) shared(arr, n, result) num_threads(threadCount)
		{
			int num_threads = omp_get_num_threads();
			int threadNum = omp_get_thread_num();
			const int start = threadNum * n / num_threads;
			const int finish = (threadNum + 1)*n / num_threads;
#pragma omp single
			{
				num_threads = omp_get_num_threads();
			}
			int index;
			if (n > num_threads) index = start / 2;
			else index = start == 0 ? start : start - 1;
			if(start%2 == 0)
			for (i = start; i < finish; i += 2) {
				result[index] = arr[i] + arr[i + 1];
				//printf("result[%d] = %f\n", index, result[index]);
				index++;
			}
#pragma omp barrier
		}
		ShowTime(true);

		if (n / 2 > 1) {
			CascadeSum(result, n/2, res);
		}
		else {
			printf("\nRESULT = %f\n", result[0] + res);
			printf("TIME = %f\n", parallelTime);
			PrintText("=========================================================\n");
			PrintText(("Serial Time: " + to_string(serTime)).c_str());
			PrintText(("\nParallel Time: " + to_string(parallelTime)).c_str());
			PrintText(("\nParallel faster: " + to_string(serTime / parallelTime)).c_str());
			PrintText("\n=========================================================\n");
			PrintText("=========================================================\n");
			return;
		}
	}

};

