#pragma once
#ifndef CUBE_H
#define CUBE_H
#include "cobject.h"
#include "checkermaterial.h"
#include <vector>
class Cube :public CObject
{
public:
	Cube();
	Cube(Cube &obj);
	Cube(const vector<GVector3> &v);
	virtual IntersectResult isIntersected(CRay& RAY);
	virtual ~Cube();
	GVector3 getCenter();
	GVector3 getNormal(GVector3 point);
	double getLength();
	void getinfo();
private:
	vector<GVector3> vertexes;
	GVector3 center;
	float length;
	vector<GVector3> normals;
	vector<GVector3> mid;
	vector<float> d;
	GVector3 **pl;
	int number = 0;
	float pos = 0;
};


#endif //end CUBE_H