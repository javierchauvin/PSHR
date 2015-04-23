#pragma once

#include "Utils.h"

using namespace std;

class vecMath
{
public:
	Vertice Vertex;

	vecMath() {};
	vecMath(Vertice newPoint);
	~vecMath();

	float magnitude ();
	Vertice unitVector ();
	Vertice vectorStringToVerticeVector ( vector<string>tokens );
};

class face
{
	vector<Vertice> Face;

public:
	Vertice normal();
};



