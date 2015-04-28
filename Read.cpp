#include "stdafx.h"
#include "Read.h"
#include <fstream>

struct index{
	int i;
	int j;
};

vector<index> Ids;
vector<vector<vector<index>>> Connection;

Read::Read(string fileName){

	cout<<"receiving the file at reading\n";
	Read::fileToRead = fileName;
	getData();
	getContainingBox();
	getHoles();
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

	Box.min = Data.at(0).at(1).Vertex;
	Box.max = Data.at(0).at(1).Vertex;

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

	InnerBox.min.x = Box.min.x + ((1-IBoxFactorX)/2 * Box.min.x); 
	InnerBox.min.y = Box.min.y + ((1-IBoxFactorY)/2 * Box.min.y); 
	InnerBox.min.z = Box.min.z + ((1-IBoxFactorZ)/2 * Box.min.z); 

	return InnerBox;
}

void Read::getHoles( void ){

	cout<< "getting Holes-------- \n";
	
	CBox InnerBox = getInnerBox();
	index newIndex;
	vector<index> tri;

	vector<vector<vector<index>>> id (Data.size(), Data.at(0).size());
	
	
	for (int i = 0; i< Data.size(); i++ ){
		if ( isInsideBox(Data[i][1].Vertex, InnerBox) ){
			for ( int j=1; j<Data.at(i).size(); j++ ){
			
			
				//do the algorithm to find the boudary vertices.


				for (	int k = 0; k < Data.size(); k++){
					for ( int l = 1; l<Data.at(k).size(); l++){
						if (Data[k][l].Vertex.x == Data[i][j].Vertex.x &&
							k!=i ){

							newIndex.i = k; newIndex.j = l;
							id[i][j].push_back(newIndex);

							//cout<<"Trianggles i:"<<i<<" j:"<<j << " \n";
						}
					}
				}

			}
		}
	}

	Connection.assign(id.begin(),id.end());
	cout<< "done searching--------------------\n";

	index CVertex;
	vector<index> ConnectedV;
	bool Repeated = false;
	int b,c,d;


	vector<index> Ring;
	vector<vector<index>> RealConnection;
	vector<index> dotsAnalized;
	index Analized;

	for (	int i = 0; i < Connection.size(); i++){
		for ( int j = 1; j<Connection.at(i).size(); j++){
			if(0 < Connection[i][j].size() ){
				for (int k=0; k<Connection[i][j].size(); k++){//// Until here only for the 3D 

					b = Connection[i][j][k].i;
					c = Connection[i][j][k].j;
					d = Connection[Connection[i][j][k].i].size();
					for (int dotCoor=1; dotCoor<Connection[Connection[i][j][k].i].size(); dotCoor++){ //To check in triangles
						if( Connection[i][j][k].j != dotCoor ){  // To not add the analized vertex
							
							int triCoor = Connection[i][j][k].i;
							
							// Connection[triCoor][dotCoor]; index cheking

							if ( 0 == ConnectedV.size()){  //If there are not repeated connected vertices yet.
								CVertex.i = triCoor; CVertex.j = dotCoor; //just storing the dot
								ConnectedV.push_back(CVertex);
								Analized.i = i; Analized.j = j;
							} 
							else {

								for(int c=0; c<ConnectedV.size(); c++){
									if (	ConnectedV[c].i == triCoor &&
											ConnectedV[c].j == dotCoor){
										
										Repeated = true;//find how to end the loop when is repeated
									}
								}

								if ( !Repeated ){
									CVertex.i = triCoor; CVertex.j = dotCoor; //just storing the dot
									ConnectedV.push_back(CVertex);
									Analized.i = i; Analized.j = j;
								}
							}
						}
					}

					//if ( ConnectedV.size() != Connection[i][j].size() ){
					//	CVertex.i = i; CVertex.j = j;
					//	Ring.push_back( CVertex );
					//	ConnectedV.clear();
					//}

				}
			}
			RealConnection.push_back(ConnectedV);
			dotsAnalized.push_back(Analized);
			ConnectedV.clear();
		}
	}

	for (int i=0; i<RealConnection.size(); i++ ){
		//for(int j=0; j<RealConnection[i].size(); j++){
		if(RealConnection[i].size() != 0 && 
			RealConnection[i].size() != Connection[dotsAnalized.at(i).i][dotsAnalized.at(i).j].size())
		{
			Ring.push_back( dotsAnalized.at(i) );
			i = RealConnection.size();
		}
	}

	//int a = 0;

	//for (int i=0; i<Connection.size(); i++){
	//	for (int j=0; j<Connection.at(i).size(); j++){
	//		if (0 != Connection[i][j].size()){
	//			for (int k=0; k<Connection[i][j].size(); k++){
	//				cout << Connection[i][j][k].i<<" "<< Connection[i][j][k].j <<" ";
	//			}
	//			cout <<" "<< ++a<<"\n";
	//		}
	//	}
	//}

}

