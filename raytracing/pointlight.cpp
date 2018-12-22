/*****************************************************************************
Copyright: 2012, ustc All rights reserved.
contact:k283228391@126.com
File name: pointlight.cpp
Description:pointlight's cpp doc.
Author:Silang Quan
Version: 1.0
Date: 2012.12.04
*****************************************************************************/
#include "pointlight.h"

PointLight::PointLight()
{
	//ctor
}

PointLight::~PointLight()
{
	//dtor
}
PointLight::PointLight(Color _color, GVector3 _position, bool _isShadow)
{
	color = _color;
	position = _position;
	isShadow = _isShadow;
}
//ͨ�������볡�����ཻ���������ս��
Color PointLight::intersect(Union &scence, IntersectResult &rayResult)
{
	//����shadowRay������ֵ
	const float k = 1e-4;
	GVector3 delta = this->position - rayResult.position;
	float distance = delta.getLength();
	//����������෴�����shadowRay
	CRay shadowRay = CRay(rayResult.position, delta.normalize());
	GVector3 shadowDir = delta.normalize();
	//����shadowRay�Ƿ��볡���ཻ
	IntersectResult lightResult = scence.isIntersected(shadowRay);
	Color resultColor = Color::black();
	Color returnColor = Color::black();
	//���shadowRay�볡���е������ཻ
	if (lightResult.object && (lightResult.distance <= distance))
	{
		return resultColor;;
	}
	else
	{
		resultColor = this->color.divide(distance*distance);
		float NdotL = rayResult.normal.dotMul(shadowDir);
		if (NdotL >= 0)
			returnColor = returnColor.add(resultColor.multiply(NdotL));
		return returnColor;
	}

}
