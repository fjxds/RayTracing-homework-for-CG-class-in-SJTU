#pragma once
#ifndef Material_H
#define Material_H
#include "gvector3.h"
#include "cray.h"
#include "color.h"
class Material
{
public:
	Material();
	Material(float _reflectiveness);
	float getRef();
	void setRef(float _reflectiveness);
	virtual ~Material();
	virtual Color sample(CRay& ray, const GVector3& position,GVector3& normal)=0;
protected:
	float reflectiveness;
private:

};

#endif // Material_H
