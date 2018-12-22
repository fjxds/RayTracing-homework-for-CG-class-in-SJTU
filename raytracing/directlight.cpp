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
//ͨ�������볡�����ཻ���������ս��
Color DirectLight::intersect(Union &scence, IntersectResult &rayResult)
{
	//����shadowRay������ֵ
	const float k = 1e-4;
	//����������෴�����shadowRay
	GVector3 shadowDir = direction.normalize().negate();
	CRay shadowRay = CRay(rayResult.position + rayResult.normal*k, shadowDir);
	//����shadowRay�Ƿ��볡���ཻ
	IntersectResult lightResult = scence.isIntersected(shadowRay);
	Color resultColor = Color::black();
	if (isShadow)
	{
		if (lightResult.object)
		{
			return resultColor;
		}
	}

	//�����ǿ
	float NdotL = rayResult.normal.dotMul(shadowDir);
	if (NdotL >= 0)
		resultColor = resultColor.add(this->color.multiply(NdotL));
	//return this->color;

	return resultColor;
}
