#pragma once
#include "BaseTask.h"
#include "ArrayInfo.h"
class FirstTask :
	public BaseTask
{
public:
	using BaseTask::BaseTask;
	~FirstTask();
	void DoAll() override;
	void DoTaskSerial(ArrayInfo arrayInfo) override;
	void DoTaskParallel(ArrayInfo arrayInfo) override;
private:
	double k;
};

