#include "stdafx.h"
#include "vecMath.h"

#include <math.h>


vecMath::vecMath(Vertice newPoint){
	Vertex =  newPoint;
}

float vecMath::magnitude (){
	return sqrt(Vertex.x*Vertex.x + Vertex.y*Vertex.y + Vertex.z*Vertex.z);
}

Vertice vecMath::unitVector(){
	Vertice unit;
	unit.x = Vertex.x/vecMath::magnitude();
	unit.y = Vertex.y/vecMath::magnitude();
	unit.z = Vertex.z/vecMath::magnitude();
	return unit;
}

vecMath::~vecMath(void)
{
}
