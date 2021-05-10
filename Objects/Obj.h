#ifndef OBJ_H
#define OBJ_H

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "../Utilities/Constants.h"
#include "Triangle.h"

// Class for parsing obj file and computing per-vertex normals of obj file
class Obj : public Object{
	public:
		std::string fileName;
		std::vector<Point3> vertices;
		std::vector<shared_ptr<Triangle>> meshes;
		std::vector<Normal> normals;

	public:
		Obj();
		Obj(std::string filePath);

		vector<Point3> getVertices();
		vector<shared_ptr<Triangle>> getMeshes();

		void update_vertex_normals(shared_ptr<Material> mat);
};


#endif