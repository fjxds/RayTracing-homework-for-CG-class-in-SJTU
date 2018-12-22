 #include "directlight.h"

DirectLight::DirectLight()
{
	//ctor
}
DirectLight::DirectLight(Color _color, GVector3 _direction, bool _isShadow)
{
	color = _color;
	direction = _direction;
	isShadow = _isShadow;
}
DirectLight::~DirectLight()
{
	//dtor
}
//通过光线与场景的相交结果计算光照结果
Color DirectLight::intersect(Union &scence, IntersectResult &rayResult)
{
	//生产shadowRay的修正值
	const float k = 1e-4;
	//生成与光照相反方向的shadowRay
	GVector3 shadowDir = direction.normalize().negate();
	CRay shadowRay = CRay(rayResult.position + rayResult.normal*k, shadowDir);
	//计算shadowRay是否与场景相交
	IntersectResult lightResult = scence.isIntersected(shadowRay);
	Color resultColor = Color::black();
	if (isShadow)
	{
		if (lightResult.object)
		{
			return resultColor;
		}
	}

	//计算光强
	float NdotL = rayResult.normal.dotMul(shadowDir);
	if (NdotL >= 0)
		resultColor = resultColor.add(this->color.multiply(NdotL));
	//return this->color;

	return resultColor;
}
