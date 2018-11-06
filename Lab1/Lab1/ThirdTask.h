#pragma once
#include "BaseTask.h"
class ThirdTask :
	public BaseTask
{
public:
	using BaseTask::BaseTask;
	~ThirdTask();
	void DoAll() override;
	void DoTaskSerial(ArrayInfo arrayInfo) override;
	void DoTaskParallel(ArrayInfo arrayInfo) override;
private:
	int min, max;
};

