#ifndef OctreePoint_H
#define OctreePoint_H

#include "Vec3.h"

// Simple point data type to insert into the tree.
// Have something with more interesting behavior inherit
// from this in order to store other attributes in the tree.
class OctreePoint {
	Vec3 position;
	int triangle; //is the index where the containigntriangle is inside the data vector.
public:
	OctreePoint() { }
	OctreePoint(const Vec3& position) : position(position) { }
	inline const Vec3& getPosition() const { return position; }
	inline void setPosition(const Vec3& p) { position = p; }
	inline const int getTriangle() const { return triangle; }
	inline void setTriangle(int t) { triangle = t; }
};

#endif
