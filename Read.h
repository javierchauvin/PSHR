#include <iostream>
#include "stdafx.h"
#include "vecMath.h"

using namespace std;

	struct CBox{
		Vertice min;
		Vertice max;
		Vertice dimensions;
	};

class Read {
	
	//File to add to the system
	string fileToRead;

	//Vector composedby triangles, each triangle is formed by 4 elements.
	//Element 0 is the normal. 1,2 and 3 are the vertices.
	vector<vector<vecMath>> Data;

	//Containing box of the mesh
	CBox Box;

	//Closed loops of boundary edges 
	vector<vector<vecMath>> holes;

public:
	Read (string fileName);

private:

	//Reads the data from a .stl file
	void getData(void);

	//Calculates the containing box of the mesh
	void getContainingBox ( void );

	//Finds the boundary edges and unify the closed loop.
	//Each closed loop is stored on the vector "holes"
	void getHoles ( void );

	CBox getInnerBox ( void );

	void fillOctree (void);

};