#pragma once
#include "BaseTask.h"
class SixthTask :
	public BaseTask
{
public:
	using BaseTask::BaseTask;
	~SixthTask();
	void DoTaskSerial(ArrayInfo arrayInfo) override;
	void DoTaskParallel(ArrayInfo arrayInfo) override;
private:
	double GetRandomDouble(double fMin, double fMax);
};

