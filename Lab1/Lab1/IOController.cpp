#include "pch.h"
#include "IOController.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <omp.h>
#include <stdio.h> 
#include <direct.h>
#include <io.h>
#include <windows.h>
#include <atlbase.h>
#include <atlconv.h>

using namespace std;

void IOController::Save(string path, string text)
{
	std::ofstream out(path, std::ios::app);
	if (out.is_open())
	{
		out << text << std::endl;
		printf("File Saved\n");
	}
	out.close();
}

FILE* IOController::WriteTaskFile(int taskIndex, int labIndex) {
	FILE*OutputFile;
	string directoryPath = string(current_work_dir) + "\\TaskOut" + to_string(labIndex);
	string filePath = directoryPath + "\\Task" + to_string(taskIndex) + ".txt";

	if(CreateDirectory(CA2W(directoryPath.c_str()),NULL))
		printf(("Directory Created. Path: " + directoryPath).c_str());
	fopen_s(&OutputFile, filePath.c_str(), "w");
	return OutputFile;
}

bool IOController::FileExists(const char *fileName)
{
	return _access(fileName, 0) != -1;
}

IOController::IOController()
{
	_getcwd(current_work_dir, sizeof(current_work_dir));
}


IOController::~IOController()
{

}



