#include "material.h"

Material::Material()
{
	//ctor
}

Material::Material(float _reflectiveness)
{
	reflectiveness = _reflectiveness;
}
Material::~Material()
{
	//dtor
}
float Material::getRef()
{
	return reflectiveness;
}
void Material::setRef(float _reflectiveness)
{
	reflectiveness = _reflectiveness;
}
