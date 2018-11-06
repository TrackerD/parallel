#include "pch.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <omp.h>
#pragma once
using namespace std;
class IOController
{
public:
	char current_work_dir[FILENAME_MAX];
	IOController();
	void Save(string path, string text);
	bool FileExists(const char *fileName);
	FILE* WriteTaskFile(int taskIndex, int labIndex);
	~IOController();
};

