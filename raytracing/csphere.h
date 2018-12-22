#pragma once
#ifndef CSPHERE_H
#define CSPHERE_H
#include "cobject.h"
#include "phongmaterial.h"
class CSphere:public CObject
{
public:
	CSphere();
	CSphere(GVector3 center, double radius);
	CSphere(CSphere& s);
	void setCenter(GVector3& c);
	void setRadius(double r);
	GVector3 getCenter();
	double getRadius();
	//获取物体表面一点的法线
	GVector3 getNormal(GVector3 point);
	//用于判断射线和该物体的交点
	virtual IntersectResult isIntersected(CRay& RAY);
	virtual ~CSphere();
protected:
private:
	GVector3 center;
	double radius;
};

#endif // CSPHERE_H
