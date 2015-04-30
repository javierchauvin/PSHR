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

	float IBoxFactorX = 0.6, IBoxFactorY = 0.6, IBoxFactorZ = 0.6; 
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
//		if ( isInsideBox(Data[i][1].Vertex, InnerBox) ){
			for ( int j=1; j<Data.at(i).size(); j++ ){
				for (	int k = 0; k < Data.size(); k++){
					for ( int l = 1; l<Data.at(k).size(); l++){
						if (Data[k][l].Vertex.x == Data[i][j].Vertex.x &&
							 Data[k][l].Vertex.y == Data[i][j].Vertex.y &&
							 k!=i ){

							newIndex.i = k; newIndex.j = l;
							id[i][j].push_back(newIndex);

							//cout<<"Trianggles i:"<<i<<" j:"<<j << " \n";
						}
					}
				}

			}
//		}
	}

	Connection.assign(id.begin(),id.end());
	cout<< "done searching--------------------\n";

	index CVertex;
	vector<index> ConnectedV;
	bool Repeated = false;
	int b,c,d;


	vector<index> Ring;
	vector<vector<vector<index>>> RealConnection;
	vector<vector<index>> fillingRConnection;
	vector<vector<index>> RCIndex;
	vector<index> fillingRCIndex;


	vector<vector<vector<index>>> ideota (Data.size(), Data.at(0).size());

	for (	int i = 0; i < Connection.size(); i++){
		for ( int j = 1; j<Connection.at(i).size(); j++){
			if(0 < Connection[i][j].size() /*&&
				isInsideBox(Data[i][j].Vertex, InnerBox)*/)	
				{
				for (int k=0; k<Connection[i][j].size(); k++){//// Until here only for the 3D 

					b = Connection[i][j][k].i;
					c = Connection[i][j][k].j;
					d = Connection[Connection[i][j][k].i].size();
					for (int dotCoor=1; dotCoor<Connection[Connection[i][j][k].i].size(); dotCoor++){ //To check in triangles
						if( Connection[i][j][k].j != dotCoor ){  // To not add the analized vertex
							
							int triCoor = Connection[i][j][k].i;
							
								if (ConnectedV.size() == 0){
									for (int c=1; c<Connection[i].size(); c++){
										if( j != c){
											CVertex.i = i; CVertex.j = c;
											ConnectedV.push_back(CVertex);
											ideota[i][j].push_back(CVertex);
										}
									}
								}
									
								for(int c=0; c<ConnectedV.size(); c++){
									int m = ConnectedV[c].i;
									int p = ConnectedV[c].j;
									if (	Data[triCoor][dotCoor].Vertex.x == Data[ConnectedV[c].i][ConnectedV[c].j].Vertex.x &&
											Data[triCoor][dotCoor].Vertex.y == Data[ConnectedV[c].i][ConnectedV[c].j].Vertex.y &&
											Data[triCoor][dotCoor].Vertex.z == Data[ConnectedV[c].i][ConnectedV[c].j].Vertex.z ||
											
											Data[i][j].Vertex.x == Data[ConnectedV[c].i][ConnectedV[c].j].Vertex.x &&
											Data[i][j].Vertex.y == Data[ConnectedV[c].i][ConnectedV[c].j].Vertex.y &&
											Data[i][j].Vertex.z == Data[ConnectedV[c].i][ConnectedV[c].j].Vertex.z  
											)
									{
													
										Repeated = true;//find how to end the loop when is repeated
										c = ConnectedV.size();
									}
								}

								if ( !Repeated ){
									CVertex.i = triCoor;
									CVertex.j = dotCoor; //just storing the dot
									ConnectedV.push_back(CVertex);
									ideota[i][j].push_back(CVertex);
								}
								Repeated = false;
							//}
						}
					}

				}
			}
			if (ConnectedV.size() != 0){
				fillingRConnection.push_back(ConnectedV);
				CVertex.i = i;		CVertex.j = j;
				fillingRCIndex.push_back(CVertex);
				ConnectedV.clear();	
			}
		}
		if (fillingRConnection.size() != 0 ){
			RealConnection.push_back(fillingRConnection);
			fillingRConnection.clear();

			RCIndex.push_back(fillingRCIndex);
			fillingRCIndex.clear();
		}
	}


	////Saving the ring.
	//for (int i=0; i<RealConnection.size(); i++ ){
	//	for(int j=0; j<RealConnection[i].size(); j++){

	//		int w = RCIndex[i][j].i; 
	//		int x = RCIndex[i][j].j; 
	//		int y = RealConnection[i][j].size();
	//		int z = Connection[ RCIndex[i][j].j ][RCIndex[i][j].j].size();

	//		if(RealConnection[i][j].size() != 0 && 
	//			RealConnection[i][j].size() != Connection[ RCIndex[i][j].i ][RCIndex[i][j].j].size()+1)
	//		{
	//			// j+1 due to data's dimensions are [i][4] and RealConnection is [i][3]
	//			index boundary; boundary.i = i; boundary.j = j+1;
	//			Ring.push_back( boundary );
	//			//i = RealConnection.size();
	//		}
	//	}
	//}

	for (int i=0; i<ideota.size(); i++ ){
		for(int j=1; j<ideota[i].size(); j++){

			if(ideota[i][j].size() != 0 && 
				// +1 because in connection is not taken into account the analized vertex
				ideota[i][j].size() != Connection[i][j].size()+1)
			{
				index boundary; boundary.i = i; boundary.j = j;
				Ring.push_back( boundary );
				j = ideota[i].size();
				i = ideota.size()-1;
			}
		}
	}

	index firstBV = Ring[0];
	index newBV = firstBV; 
	bool keepSearching = true;
	index idi;
	

	while (keepSearching){
		//Checks all connections of the first found boundary vertex
		int i=0;
		int aux = ideota[newBV.i][newBV.j].size();
		while ( i < ideota[newBV.i][newBV.j].size() ){
		//for (int i=0; i<ideota[newBV.i][newBV.j].size(); i++){

			idi = ideota[newBV.i][newBV.j][i]; 

			
			if (ideota[idi.i][idi.j].size() != Connection[idi.i][idi.j].size()+1){

				if( idi.i != newBV.i && //avoiding that analyzed seed and the analyzed would be in the same trianlge
					 Ring[0].i == idi.i && Ring[0].j == idi.j ){ // if the loop is closed
					 keepSearching = false;
				} else if ( (Ring[0].i == idi.i) ? (Ring[0].j != idi.j) : true ){
					bool notRepeated = true; 
					for (int w = 0; w< Ring.size(); w++){
						if (idi.i == Ring[w].i && idi.j == Ring[w].j){
							notRepeated = false;
						}
					}
					if (notRepeated){
						newBV = idi;
						Ring.push_back( newBV );
						i = 0;
					}
				}
			}
			i++;
		}
	}





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

