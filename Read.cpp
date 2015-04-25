#include "stdafx.h"
#include "Read.h"
#include <fstream>

Read::Read(string fileName){

	cout<<"receiving the file at reading\n";
	Read::fileToRead = fileName;
	getData();
}

void Read::getData(void){

//	TODO
// Authomatic calculation of the normal for each triangle, 
// in order to compute it instead of store it.
	
	cout<<"reading data\n";
	const int Completed = 4; //1 for the normal and 3 for the vertices.

	string line;
	ifstream surfaceFile (fileToRead);
	vector<vecMath> Triangle;
	vecMath each;

	if (surfaceFile.is_open()){ 
		cout << fileToRead << " is being ridden...\n";
		getline (surfaceFile,line);

		unsigned long long int cont = 0;
		unsigned long long int contaux = 0;

		vector<string> splitLine = split(line);
		while ("endsolid" != splitLine[0] )
		{
			if ("facet" == splitLine[0]){
				each.Vertex.x = stof(splitLine[2]);	
				each.Vertex.y = stof(splitLine[3]);	
				each.Vertex.z = stof(splitLine[4]);
				Triangle.push_back(each);
				splitLine = split(line);
			}

			if ("vertex" == splitLine[0]){
				each.Vertex.x = stof(splitLine[1]);
				each.Vertex.y = stof(splitLine[2]);
				each.Vertex.z = stof(splitLine[3]);
				Triangle.push_back(each);
			
				if(Completed == Triangle.size()){
					Data.push_back(Triangle);
					Triangle.clear();

							
						if(1000 == ++cont){
							cout << ++contaux <<" "; 
							cont = 1;
						}
				}
			}
			getline (surfaceFile,line);
			splitLine = split(line);
		}

		//for (int i = 0 ;i < Data.size(); i++){
		//	for (int j = 0; j<Completed; j++){
		//		cout<< Data[i][j].Vertex.x << " " << Data[i][j].Vertex.y <<" "<< Data[i][j].Vertex.z << "\n";
		//	}
		//	cout << "-------------------\n";
		//}

		cout << "-------------------\n";
	}
}


void Read::getContainingBox ( void ){

	// j starts at 1 due to position 0 is the normal of the triangle
	for(unsigned int i = 0; i < Data.size(); i++){
		for(unsigned int j = 1; j < Data.at(i).size(); j++){

			if ( Data.at(i).at(j).Vertex.x < Box.min.x ){
				Box.min.x = Data.at(i).at(j).Vertex.x;
			}
			if ( Data.at(i).at(j).Vertex.y < Box.min.y ){
				Box.min.y = Data.at(i).at(j).Vertex.y;
			}
			if ( Data.at(i).at(j).Vertex.z < Box.min.z ){
				Box.min.z = Data.at(i).at(j).Vertex.z;
			}


			if ( Box.max.x < Data.at(i).at(j).Vertex.x ){
				Box.max.x = Data.at(i).at(j).Vertex.x;
			}
			if ( Box.max.y < Data.at(i).at(j).Vertex.y ){
				Box.max.y = Data.at(i).at(j).Vertex.y;
			}
			if ( Box.max.z < Data.at(i).at(j).Vertex.z ){
				Box.max.z = Data.at(i).at(j).Vertex.z;
			}
		}
	}
	
	Box.dimensions.x = Box.max.x - Box.min.x;
	Box.dimensions.y = Box.max.y - Box.min.y;
	Box.dimensions.z = Box.max.z - Box.min.z; 
}


///////////////////////////////////////////////////////////////////////////////////////
// Getting Holes

bool isInsideBox( Vertice Vertex, CBox InnerBox ){
	bool isInside = false;

	if ( InnerBox.min.x < Vertex.x &&
			InnerBox.min.y < Vertex.y &&
			InnerBox.min.z < Vertex.z &&
			Vertex.x < InnerBox.max.x &&
			Vertex.y < InnerBox.max.y &&
			Vertex.z < InnerBox.max.z ){
		
			isInside = true;
	}
	return isInside;
}

CBox Read::getInnerBox ( void ){

	float IBoxFactorX = 0.8, IBoxFactorY = 0.8, IBoxFactorZ = 0.8; 
	CBox InnerBox;

	InnerBox.max.x = Box.max.x - ((1-IBoxFactorX)/2 * Box.max.x); 
	InnerBox.max.y = Box.max.y - ((1-IBoxFactorY)/2 * Box.max.y); 
	InnerBox.max.z = Box.max.z - ((1-IBoxFactorZ)/2 * Box.max.z); 

	InnerBox.min.x = Box.max.x + ((1-IBoxFactorX)/2 * Box.min.x); 
	InnerBox.min.y = Box.max.y + ((1-IBoxFactorY)/2 * Box.min.y); 
	InnerBox.min.z = Box.max.z + ((1-IBoxFactorZ)/2 * Box.min.z); 

	return InnerBox;
}

void Read::getHoles( void ){
	
	CBox InnerBox = getInnerBox();
	
	for (int i = 0; i< Data.size(); i++ ){
		for ( int j=0; j<Data.at(i).size(); j++ ){
			
			if ( isInsideBox(Data[i][j].Vertex, InnerBox) ){
				//do the algorithm to find the boudary vertices.

				
			}

		}
	}
}

