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
};

