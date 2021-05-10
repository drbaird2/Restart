#include "Obj.h"

Obj::Obj() 
{}

Obj::Obj(std::string filePath) {
	fileName = filePath;
	ifstream file(filePath);
	string line;

	// Iterate through the file line by line for parsing
	while (getline(file, line)) {
	    // If line has vertex info
		if (line.find("v") == 0) {
			istringstream iss(line);
			vector<string> parsed_double((istream_iterator<string>(iss)),istream_iterator<string>());
			double x = stod(parsed_double[1]);
			double y = stod(parsed_double[2]);
			double z = stod(parsed_double[3]);

			// Parse vertex position and push to vector
			vertices.push_back(Point3(x, y, z));
			// Initialize per-vertex normal for the parsed vertex
			normals.push_back(Vec3(0, 0, 0));
		}else if (line.find("f") == 0) { // If line has face info
			istringstream iss(line);
			vector<string> parsed_int((istream_iterator<string>(iss)),istream_iterator<string>());
			int v0 = stoi(parsed_int[1]) - 1;
			int v1 = stoi(parsed_int[2]) - 1;
			int v2 = stoi(parsed_int[3]) - 1;

			// Construct triangle with parsed face info
			shared_ptr<Triangle> tri = make_shared<Triangle>(vertices[v0], vertices[v1], vertices[v2]);
			Normal n = tri->getFaceNormal();
			// Compute vertex normal for each vertex
			normals[v0] += n;
			normals[v1] += n;
			normals[v2] += n;
			// Push triangle to vector
			meshes.push_back(tri);
		}else{
			continue;
        }
	}

	// Normalize all per-vertex normals
	for (int i = 0; i < normals.size(); i++) {
		normals[i].unit_vector();
	}

	file.close();
}

vector<Point3> Obj::getVertices() { 
    return vertices; 
}

vector<shared_ptr<Triangle>> Obj::getMeshes() { 
    return meshes; 
}

// Update all vertex normals in the triangles
void Obj::update_vertex_normals(shared_ptr<Material> mat) {
	std::ifstream file(fileName);
	std::string line;
	int tri_count = 0;

	while (std::getline(file, line)) {
		if (line.find("f") == 0) {
			std::istringstream iss(line);
			std::vector<std::string> parsed_int((std::istream_iterator<std::string>(iss)),std::istream_iterator<std::string>());
			int v0 = std::stoi(parsed_int[1]) - 1;
			int v1 = std::stoi(parsed_int[2]) - 1;
			int v2 = std::stoi(parsed_int[3]) - 1;
            meshes[tri_count]->setMaterial(mat);
			// Update per-vertex normals in the triangle
			meshes[tri_count]->n0 = normals[v0];
			meshes[tri_count]->n1 = normals[v1];
			meshes[tri_count]->n2 = normals[v2];

			tri_count++;
		}
	}
}
