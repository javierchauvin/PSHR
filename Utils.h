//This file contains all the utility functions

#include <iostream>
#include <vector>
#include <string>

using namespace std;

union Vertice {
	float m_vVec[3];  
	struct {
			float x;
			float y;
			float z;
	};
};


//Separate a string into tokens and store them in a vector of strings
vector<string> split (string line);

//Transform a vector of strings into a vector of int
vector<int> vectorStringToInt ( vector<string> tokens );

//Transform a vector of strings into each coordinate of a Vertice
//Vertice.x = Token 0
//Vertice.y = Token 1
//Vertice.z = Token 2
Vertice vectorStringToVertice ( vector<string> tokens );

//Returns Vec1 + Vec2
Vertice add(Vertice Vec1, Vertice Vec2);

//Returns Vec1-Vec2
Vertice sub(Vertice Vec1, Vertice Vec2);

//Retunrs the multiplication of scalar*Vec
Vertice multiScalar(float scalar, Vertice Vec);

//Retunrs the dotProduct of Vec1 and Vec2
float dotProduct ( Vertice Vec1, Vertice Vec2 );

//Returns Vec1 x Vec2
Vertice crossProduct ( Vertice Vec1, Vertice Vec2 );


