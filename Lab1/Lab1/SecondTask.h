#include "BaseTask.h"
#pragma once
class SecondTask:
	public BaseTask
{
public:
	using BaseTask::BaseTask;
	~SecondTask();
	void DoTaskSerial(ArrayInfo arrayInfo) override;
	void DoTaskParallel(ArrayInfo arrayInfo) override;
private:
	int GetNonZeroCount(ArrayInfo info);
};

