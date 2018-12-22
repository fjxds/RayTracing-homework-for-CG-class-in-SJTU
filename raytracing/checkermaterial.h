#pragma once
#ifndef CHECKERMATERIAL_H
#define CHECKERMATERIAL_H
#include "material.h"
#include "color.h"
#include <stdlib.h>
class CheckerMaterial :public Material
{
public:
	CheckerMaterial();
	CheckerMaterial(float _scale, float _reflectiveness = 0);
	virtual ~CheckerMaterial();
	virtual Color sample(CRay& ray, const GVector3& position,GVector3& normal);
protected:
private:
	float scale;
};

#endif // CHECKERMATERIAL_H
