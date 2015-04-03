#include "stdafx.h"
#include "Read.h"
#include <fstream>

Read::Read(string fileName){

	cout<<"receiving the file at reading\n";
	Read::fileToRead = fileName;
	getData();
}

void Read::getData(void){
	
	cout<<"reading data\n";
	const int Completed = 4; //1 for the normal and 3 for the vertices.

	string line;
	ifstream surfaceFile (fileToRead);
	vector<vecMath> Triangle;
	vecMath each;

	if (surfaceFile.is_open()){ 
		cout << fileToRead << " is being ridden...\n";
		getline (surfaceFile,line);

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
				}
			}
			getline (surfaceFile,line);
			splitLine = split(line);
		}

		for (int i = 0 ;i < Data.size(); i++){
			for (int j = 0; j<Completed; j++){
				cout<< Data[i][j].Vertex.x << " " << Data[i][j].Vertex.y <<" "<< Data[i][j].Vertex.z << "\n";
			}
			cout << "-------------------\n";
		}
	}
}
