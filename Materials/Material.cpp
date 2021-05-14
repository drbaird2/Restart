#include "Material.h"
#include "../Utilities/Constants.h"

Material::Material()
{}

Material::Material(const Material& material)
{}

Material::~Material()
{}

shared_ptr<Material> Material::clone() const{
    return make_shared<Material>(*this);
}

Color Material::shade(Record& recentHits){
    return black;
}

Color Material::areaLightShade(Record& recentHits)
{
	return black;
}

Color Material::pathShade(Record& recentHits)
{
	return black;
}

Color Material::globalShade(Record& recentHits)
{
	return black;
}

Color Material::getLe(Record& recentHits) const
{
	return black;
}
