// PSHR.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "PSHR.h"
#include "Read.h"

int _tmain(int argc, _TCHAR* argv[])
{
	string fileName = "test.stl";

	cout<< "sending the file\n";
	Read file(fileName);

	cin.get();
	return 0;
}

