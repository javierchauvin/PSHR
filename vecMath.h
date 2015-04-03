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
	Vertice vecMath::vectorStringToVerticeVector ( vector<string>tokens );
};



