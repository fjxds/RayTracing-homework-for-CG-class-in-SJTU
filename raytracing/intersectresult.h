#pragma once
#ifndef INTERSECTRESULT_H_INCLUDED
#define INTERSECTRESULT_H_INCLUDED
#include "gvector3.h"
class CObject;
struct IntersectResult {
	/*float distance;
	bool isHit;
	GVector3 position;
	GVector3 normal;
	CObject *object;*/
	float distance;
	bool isHit;
	GVector3 position;
	GVector3 normal;
	CObject *object;
	static inline IntersectResult noHit() { return IntersectResult(); }
};

#endif // INTERSECTRESULT_H_INCLUDED
