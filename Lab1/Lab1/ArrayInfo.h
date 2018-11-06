#pragma once
class ArrayInfo
{
public:
	long id;
	int rows;
	int cols;
	double** arr;
	int GetLength() {
		return rows * cols;
	}
	ArrayInfo();
	~ArrayInfo();
};

