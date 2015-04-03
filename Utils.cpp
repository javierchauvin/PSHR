//This file contains all the utility functions

#include "StdAfx.h"
#include "Utils.h"

#include <iterator>
#include <sstream>

using namespace std;

std::vector<std::string> split (std::string line){
	std::vector<string> tokens; 
	copy(	istream_iterator<string>(istringstream(line)),
			istream_iterator<string>(),
			back_inserter(tokens));
	return tokens;
}

//Just transforms a vector of string into a vector of int.
std::vector<int> vectorStringToInt ( std::vector<string>tokens )
{
	std::vector<int> TransformedTokens (tokens.size());

	if (!tokens.empty())
	{
		for (int i = 0 ; i<int(tokens.size()) ; i++){
			TransformedTokens[i] = std::stoi(tokens[i]);
		}
	} else {
		cout << "transformToInt has received an empty vector\n";	
	}
	return TransformedTokens;
}

//Receives the tokens in a string vector, translate them to float and store the coordinates on vertice 
Vertice vectorStringToVertice ( vector<string>tokens ){
	Vertice TransformedTokens;
	if (!tokens.empty())
	{
		TransformedTokens.x = std::stof(tokens[0]);
		TransformedTokens.y = std::stof(tokens[1]);
		TransformedTokens.z = std::stof(tokens[2]);
	}
	return TransformedTokens;
}

Vertice add(Vertice Vec1, Vertice Vec2){
	Vertice res;
	res.x = Vec1.x + Vec2.x; res.y = Vec1.y + Vec2.y; res.z = Vec1.z + Vec2.z;
	return res;
}

Vertice sum(Vertice Vec1, Vertice Vec2){
	Vertice Sum;
	Sum.x = Vec1.x + Vec2.x; Sum.y = Vec1.y + Vec2.y; Sum.z = Vec1.z + Vec2.z;
	return Sum;
}

Vertice sub(Vertice Vec1, Vertice Vec2){
	Vertice res;
	res.x = Vec1.x - Vec2.x; res.y = Vec1.y - Vec2.y; res.z = Vec1.z - Vec2.z;
	return res;
}

Vertice multiScalar(float scalar, Vertice Vec){
	Vertice res;
	res.x = scalar*Vec.x;
	res.y = scalar*Vec.y;
	res.z = scalar*Vec.z;
	return res;
}

float dotProduct ( Vertice Vec1, Vertice Vec2 ){
	return Vec1.x*Vec2.x + Vec1.y*Vec2.y + Vec1.z*Vec2.z;;
}

Vertice crossProduct ( Vertice Vec1, Vertice Vec2 ){
	Vertice CP ={0};
	CP.x = Vec1.y*Vec2.z - Vec1.z*Vec2.y; 
	CP.y = Vec1.x*Vec2.z - Vec1.z*Vec2.x;
	CP.z = Vec1.x*Vec2.y - Vec1.y*Vec2.x;
	return CP;
}
