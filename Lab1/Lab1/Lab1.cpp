#include "pch.h"
#include <fstream>
#include <iostream>
#include "omp.h"
#include "IOController.h"
#include "MatrixController.h"
#include "BaseTask.h"
#include "FirstTask.h"
#include "SecondTask.h"
#include "ThirdTask.h"
#include "FourthTask.h"
#include "FifthTask.h"
#include "SixthTask.h"
#include "Task1L2.h"
#include "Task2L2.h"
#include "Task3L2.h"
#include "Task4L2.h"
#include "Task5L2.h"
#include "Task6L2.h"
#include "Lab1.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	MatrixController m;
	m.Load();
	//DoTask(FirstTask(m, 1, 1));
	//DoTask(SecondTask(m, 1, 2));
	//DoTask(ThirdTask(m, 1, 3));
	//DoTask(FourthTask(m, 1, 4));
	//DoTask(FifthTask(m, 1, 5));
	//DoTask(SixthTask(m, 1, 6));

	//DoTask(Task1L2(m, 2, 1));
	DoTask(Task2L2(m, 2, 2));
	//DoTask(Task3L2(m, 2, 3));
	//DoTask(Task4L2(m, 2, 4));
	//DoTask(Task5L2(m, 2, 5));
	//DoTask(Task6L2(m, 2, 6));

	return 0;
}
