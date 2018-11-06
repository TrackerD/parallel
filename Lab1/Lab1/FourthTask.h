#pragma once
#include "BaseTask.h"
class FourthTask :
	public BaseTask
{
public:
	using BaseTask::BaseTask;
	~FourthTask();
	void DoAll() override;
	void DoTaskSerial(ArrayInfo arrayInfo) override;
	void DoTaskParallel(ArrayInfo arrayInfo) override;
private:
	int index;
};

