#include "plane.h"

Plane::Plane()
{
	index = 0;
	//ctor
}

Plane::~Plane()
{
	//dtor
}

Plane::Plane(const GVector3& _normal, float _d)
{
	normal = _normal;
	d = _d;
	index = 0;
}
IntersectResult Plane::isIntersected(CRay& ray)
{
	IntersectResult result = IntersectResult::noHit();
	float a = ray.getDirection().dotMul(this->normal);
	if (a <0)
	{
		result.isHit = 1;
		result.object = this;
		float b = this->normal.dotMul(ray.getOrigin() - normal*d);
		result.distance = -b / a;
		number++;
		if (result.distance > 0)
			pos++;
		result.position = ray.getPoint(result.distance);
		result.normal = this->normal;
	}
	return result;
}
void Plane::getinfo()
{
	cout << "plane rate: " << pos / number << endl;
}