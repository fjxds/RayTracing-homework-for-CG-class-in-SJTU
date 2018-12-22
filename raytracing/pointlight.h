#pragma once

#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "color.h"
#include "gvector3.h"
#include "union.h"

class PointLight
{
public:
	PointLight();
	PointLight(Color _color, GVector3 _position, bool _isShadow);
	virtual ~PointLight();
	Color intersect(Union &scence, IntersectResult &result);
protected:
private:
	bool isShadow;
	Color color;
	GVector3 position;
};

#endif // POINTLIGHT_H
