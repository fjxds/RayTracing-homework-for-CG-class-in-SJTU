#include "cobject.h"

CObject::CObject()
{
	//ctor
}

CObject::~CObject()
{
	//dtor
}

CObject::CObject(const GVector3& _normal, float _d)
{
	normal = _normal;
	d = _d;
}