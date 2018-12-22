#pragma once
#ifndef Plane_H
#define Plane_H
#include "checkermaterial.h"
#include "cobject.h"
class Plane :public CObject
{
public:
	Plane();
	Plane(const GVector3& _normal, float _d);
	virtual ~Plane();
	virtual IntersectResult isIntersected(CRay& RAY);
	int number=0;
	float pos = 0;
	void getinfo();
protected:
private:
};

#endif // Plane_H
