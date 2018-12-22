#pragma once
#ifndef CObject_H
#define CObject_H
#include "material.h"
#include "intersectresult.h"
#include "gvector3.h"
#include "cray.h"

class CObject
{
public:
	CObject();
	CObject(const GVector3& _normal, float _d);
	virtual ~CObject();
	virtual IntersectResult isIntersected(CRay& RAY)=0;
	Material *material;
	Color *color;
	//法向量
	GVector3 normal;
	//到原点的距离
	float d;
	int index;
protected:
private:
};

#endif //CObject_H