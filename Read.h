#include <iostream>
#include "stdafx.h"
#include "vecMath.h"

using namespace std;

class Read {
	
	string fileToRead;

	//Element 0 is the normal of the triangle, elemnts 1,2 and 3 are the vertices on each triangle.
	vector<vector<vecMath>> Data;

public:
	Read (string fileName);

private:
	void getData(void);

};