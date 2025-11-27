/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:34:20 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/27 17:19:17 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.hpp"

// Constructeur
Object::Object(): _vao(0), _vbo(0), _ebo(0) {
	_modelMatrix = Mat4::identity();
	_vertices.clear();
	_uvs.clear();
	_normals.clear();
	_faces.clear();
	
	_mtl.ka.r = 0.0f; _mtl.ka.g = 0.0f; _mtl.ka.b = 0.0f;
	_mtl.kd.r = 0.0f; _mtl.kd.g = 0.0f; _mtl.kd.b = 0.0f;
	_mtl.ks.r = 0.0f; _mtl.ks.g = 0.0f; _mtl.ks.b = 0.0f;
	_mtl.d = 0.0f; _mtl.Ni = 0.0f; _mtl.Ns = 0.0f;
	_mtl.illum = 0;
	
}

Object::~Object() {}

Object::Object(const Object &other) {
    *this = other;
}

Object &Object::operator=(const Object &other) {
    if (this != &other) {
        // copy attributes here
    }
    return *this;
}

void Object::load(char *filePath) {
	std::ifstream file(filePath);
	std::string line;
	std::string prefix;

	std::unordered_map<std::string, std::function<void(istringstream&)>> parser = {
		{"o", [this, &prefix](std::istringstream& iss) {setNameAndCoord(iss, prefix);}},
		{"mtllib", [this](std::istringstream& iss) {setMtAttributes(iss);}},
		{"v", [this](std::istringstream& iss) {setVertexCoord(iss);}},
		{"vn", [this, &prefix](std::istringstream& iss) {setNameAndCoord(iss, prefix);}},
		{"vt", [this, &prefix](std::istringstream& iss) {setNameAndCoord(iss, prefix);}},
		{"f", [this](std::istringstream& iss) {setFaces(iss);}}
	};

	while(std::getline(file, line)) {
		std::istringstream iss(line);
		iss >> prefix;
		std::unordered_map<std::string, std::function<void(istringstream&)>>::iterator it;
		it = parser.find(prefix);
		if (it != parser.end())
			it->second(iss);
	}
	file.close();
}

void Object::setNameAndCoord(std::istringstream& iss, std::string prefix) {
	if (prefix == "o"){
		iss >> _name;
	} else if (prefix == "vn") {
		float nX, nY, nZ;
		if (!(iss >> nX >> nY >> nZ))
			throw fileError("Wrong line for normals");
		_normals.push_back({nX, nY, nZ});
	} else if (prefix == "vt") {
		Vect3 uv;
		uv.z = 0.0f;
		if (!(iss >> uv.x >> uv.y))
			throw fileError("Wrong  lien for tex coord");
		iss >> uv.z;
		_uvs.push_back(uv);
	}
}

void Object::setMtAttributes(std::istringstream& iss) {
	std::string fileName, line;
	iss >> fileName;
	fileName = "ressources/" + fileName;
	std::ifstream file(fileName);
	if (file.is_open()) {
		while(std::getline(file, line)) {
			std::istringstream stream;
			stream >> line;
			if (line == "Ns") {
				stream >> _mtl.Ns;
			} else if (line == "Ka") {
				stream >> _mtl.ka.r >> _mtl.ka.g >> _mtl.ka.b;
			} else if (line == "Kd") {
				stream >> _mtl.kd.r >> _mtl.kd.g >> _mtl.kd.b;
			} else if (line == "Ks") {
				stream >> _mtl.ks.r >> _mtl.ks.g >> _mtl.ks.b;
			} else if (line == "Ni") {
				stream >> _mtl.Ni;
			} else if (line == "d") {
				stream >> _mtl.d;
			} else if (line == "illum") {
				stream >> _mtl.illum;
			}
		}
		file.close();
	} else {
		throw fileError(fileName + " file doesn't exist");
	}
}

void Object::setFaces(std::istringstream& iss) {
	std::string aliquid;
	_faces.emplace_back();
	
	while (iss >> aliquid) {
		Index ind;
		ind.v = 0, ind.vt = 0, ind.vn = 0;
		size_t pos1 = aliquid.find('/');
		if (pos1 == std::string::npos) // v only
			ind.v = std::stoi(aliquid);
		else {
			ind.v = std::stoi(aliquid.substr(0, pos1));
			size_t pos2 = aliquid.find('/', pos1 + 1);
			if (pos2 == std::string::npos) // v/vt
				ind.vt = std::stoi(aliquid.substr(pos1 + 1));
			else { // v/vt/n or v//n
				if (pos2 > pos1 + 1)
					ind.vt = std::stoi(aliquid.substr(pos1 + 1, pos2 - pos1 - 1));
				if (pos2 + 1 < aliquid.size())
					ind.vn = std::stoi(aliquid.substr(pos2 + 1));		
			}
		}
		_faces.back().push_back(ind);
	}
}

void Object::setVertexCoord(std::istringstream& iss) {
	Vect3 vertex;
	iss >> vertex.x >> vertex.y >> vertex.z;
	_vertices.push_back(vertex);
}
