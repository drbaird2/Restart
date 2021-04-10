#include "Material.h"
#include "../Utilities/Constants.h"

Material::Material()
{}

Material::Material(const Material& material)
{}

Material::~Material()
{}

Color Material::shade(Record& recentHits){
    return black;
}

