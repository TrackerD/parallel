#pragma once
#include "BaseTask.h"
class FifthTask :
	public BaseTask
{
public:
	using BaseTask::BaseTask;
	~FifthTask();
	void DoAll() override;
	void DoTaskSerial(ArrayInfo arrayInfo) override;
	void DoTaskParallel(ArrayInfo arrayInfo) override;
private:
	int limit;
};

