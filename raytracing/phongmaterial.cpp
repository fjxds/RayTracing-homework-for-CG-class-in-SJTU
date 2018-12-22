#include "phongmaterial.h"

PhongMaterial::PhongMaterial()
{
	//ctor
}
PhongMaterial::PhongMaterial(const Color& _diffuse, const Color& _specular, const float& _shininess, float _reflectiveness)
{
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
	reflectiveness = _reflectiveness;
}
PhongMaterial::~PhongMaterial()
{
	//dtor
}
Color PhongMaterial::sample(CRay& ray, const GVector3& position,GVector3& normal)
{
	float NdotL = normal.dotMul(lightDir);
	GVector3 H = (lightDir - ray.getDirection()).normalize();
	Color diffuseTerm;
	Color specularTerm;
	float NdotH = normal.dotMul(H);

	if (NdotL >= 0)
	{
		diffuseTerm = this->diffuse.multiply(NdotL);
	}
	else
	{
		diffuseTerm = this->diffuse.multiply((float)0);
	}
	if (NdotH >= 0)
	{
		specularTerm = this->specular.multiply(pow(NdotH, this->shininess));
	}
	else
	{
         specularTerm = this->specular.multiply(pow((float)0, this->shininess));
	}
	return lightColor.modulate(diffuseTerm.add(specularTerm));
}
