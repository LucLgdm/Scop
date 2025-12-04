/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:34:20 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/04 17:24:03 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.hpp"

// Constructeur
Object::Object() {
	_modelMatrix = Mat4::identity();
	_vertices.clear();
	_uvs.clear();
	_normals.clear();
	_faces.clear();
	_verticeBuild.clear();
	_indiceBuild.clear();
	_indexMap.clear();
	_textures.clear();
	_mtlMap.clear();
	_name = "Scop";
	_verticeMin = Vect3(std::numeric_limits<float>::max(),
						std::numeric_limits<float>::max(),
						std::numeric_limits<float>::max());
	_verticeMax = Vect3(std::numeric_limits<float>::lowest(),
						std::numeric_limits<float>::lowest(),
						std::numeric_limits<float>::lowest());
	_m = KeyState();
}

Object::~Object() {}

Object::Object(const Object &other) {
    *this = other;
}

Object &Object::operator=(const Object &other) {
    if (this != &other) {
		this->_mtlMap = other._mtlMap;
		this->_vertices = other._vertices;
		this->_uvs = other._uvs;
		this->_normals = other._normals;
		this->_faces = other._faces;
		this->_textures = other._textures;
		this->_verticeBuild = other._verticeBuild;
		this->_indiceBuild = other._indiceBuild;
		this->_indexMap = other._indexMap;
		this->_modelMatrix = other._modelMatrix;
		this->_name = other._name;		
    }
    return *this;
}

void Object::load(int argc, char *filePath) {
	std::ifstream file(filePath);
	std::string line;
	std::string prefix;
	std::string currentMtl = "";
	

	std::unordered_map<std::string, std::function<void(istringstream&)>> parser = {
		{"o", [this, &prefix](std::istringstream& iss) {setNameAndCoord(iss, prefix);}},
		{"mtllib", [this](std::istringstream& iss) {setMtAttributes(iss);}},
		{"v", [this](std::istringstream& iss) {setVertexCoord(iss);}},
		{"vn", [this, &prefix](std::istringstream& iss) {setNameAndCoord(iss, prefix);}},
		{"vt", [this, &prefix](std::istringstream& iss) {setNameAndCoord(iss, prefix);}},
		{"f", [this, &currentMtl](std::istringstream& iss) {setFaces(iss, currentMtl);}},
		{"usemtl", [&currentMtl](std::istringstream& iss) {iss >> currentMtl;}}
	};

	while(std::getline(file, line)) {
		std::istringstream iss(line);
		prefix = "";
		iss >> prefix;
		std::unordered_map<std::string, std::function<void(istringstream&)>>::iterator it;
		it = parser.find(prefix);
		if (it != parser.end())
			it->second(iss);
	}
	file.close();
	if (_vertices.empty() || _faces.empty())
		throw fileError("There isn't any vertices or faces");
	if (_textures.empty() && argc == 2 && _mtlMap.empty())
		throw fileError("No texture or material found");
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
		Vect2 uv;
		if (!(iss >> uv.x >> uv.y))
			throw fileError("Wrong line for tex coord");
		_uvs.push_back(uv);
	}
}

void Object::setMtAttributes(std::istringstream& iss) {
	std::string fileName, line;
	iss >> fileName;
	fileName = "resources/" + fileName;
	std::ifstream file(fileName);
	if (file.is_open()) {
		Mtl current;
		while(std::getline(file, line)) {
			std::istringstream stream(line);
			stream >> line;
			if (line == "newmtl") {
				std::string name;
				stream >> name;
				if (!current.name.empty())
					_mtlMap[current.name] = current;
				current = Mtl();
				current.name = name;
			}
			if (line == "Ns") {
				stream >> current.Ns;
			} else if (line == "Ka") {
				stream >> current.ka.r >> current.ka.g >> current.ka.b;
			} else if (line == "Kd") {
				stream >> current.kd.r >> current.kd.g >> current.kd.b;
			} else if (line == "Ks") {
				stream >> current.ks.r >> current.ks.g >> current.ks.b;
			} else if (line == "Ni") {
				stream >> current.Ni;
			} else if (line == "d") {
				stream >> current.d;
			} else if (line == "illum") {
				stream >> current.illum;
			} else if (line == "map_Kd") {
				stream >> current.mapKd;
			}
		}
		file.close();
		if (!current.name.empty())
			_mtlMap[current.name] = current;
	} else {
		throw fileError(fileName + " file doesn't exist");
	}
}

void Object::setFaces(std::istringstream& iss, std::string currentMtl) {
	std::string aliquid;
	_faces.emplace_back();
	
	while (iss >> aliquid) {
		Index ind;
		ind.v = 0, ind.vt = 0, ind.vn = 0;
		size_t pos1 = aliquid.find('/');
		if (pos1 == std::string::npos) // v only
			ind.v = std::stoi(aliquid) - 1;
		else {
			ind.v = std::stoi(aliquid.substr(0, pos1)) - 1;
			size_t pos2 = aliquid.find('/', pos1 + 1);
			if (pos2 == std::string::npos) // v/vt
				ind.vt = std::stoi(aliquid.substr(pos1 + 1)) - 1;
			else { // v/vt/n or v//n
				if (pos2 > pos1 + 1)
					ind.vt = std::stoi(aliquid.substr(pos1 + 1, pos2 - pos1 - 1)) - 1;
				if (pos2 + 1 < aliquid.size())
					ind.vn = std::stoi(aliquid.substr(pos2 + 1)) - 1;
			}
		}
		ind.mtlName = currentMtl;
		_faces.back().push_back(ind);
	}
}

void Object::setVertexCoord(std::istringstream& iss) {
	Vect3 vertex;
	iss >> vertex.x >> vertex.y >> vertex.z;
	_vertices.push_back(vertex);
		// Update min and max vertices
	if (vertex.x < _verticeMin.x) _verticeMin.x = vertex.x;
	if (vertex.y < _verticeMin.y) _verticeMin.y = vertex.y;
	if (vertex.z < _verticeMin.z) _verticeMin.z = vertex.z;

	if (vertex.x > _verticeMax.x) _verticeMax.x = vertex.x;
	if (vertex.y > _verticeMax.y) _verticeMax.y = vertex.y;
	if (vertex.z > _verticeMax.z) _verticeMax.z = vertex.z;
}

void Object::setTexturesPath(int argc, char **argv) {
	
	for (const auto& mtlpair : _mtlMap) {
		const Mtl& mtl = mtlpair.second;
		if (!mtl.mapKd.empty()) {
			_textures.push_back("textures/" + mtl.mapKd);
		}
	}
	
	if (argc != 1) {
		for (int i = 2; i < argc; ++i) {
			_textures.push_back(std::string(argv[i]));
		}
	}
	
	// Remove duplicates
	std::sort(_textures.begin(), _textures.end());
	auto last = std::unique(_textures.begin(), _textures.end());
	_textures.erase(last, _textures.end());

	// put back the textures in the order of the materials
	std::vector<std::string> tmp;
	tmp = _textures;
	_textures.clear();
	for (const auto& mtlpair : _mtlMap) {
		const Mtl& mtl = mtlpair.second;
		if (!mtl.mapKd.empty()) {
			std::string texPath = "textures/" + mtl.mapKd;
			_textures.push_back(texPath);
		}
	}
	for (const auto& path : tmp) {
		if (std::find(_textures.begin(), _textures.end(), path) == _textures.end()) {
			_textures.push_back(path);
		}
	}
}

void Object::display() {
	std::cout << "Name: " << _name << std::endl;
	std::cout << "Coordinates:" << std::endl;
	int n = _vertices.size();
	for(int i = 0; i < n; i++) {
		std::cout << "Vertice [" << i << "] : (x, y, z) = "
				  << "(" << _vertices[i].x << ", "
				  << _vertices[i].y << ", "
				  << _vertices[i].z << ")" << std::endl;
	}

	n = _uvs.size();
	for(int i = 0; i < n; i++) {
		std::cout << "uv [" << i << "] : (u, v) = "
				  << "(" << _uvs[i].x << ", "
				  << _uvs[i].y << ")" << std::endl;
	}

	n = _normals.size();
	for(int i = 0; i < n; i++) {
		std::cout << "Normal [" << i << "] : (x, y, z) = "
				  << "(" << _normals[i].x << ", "
				  << _normals[i].y << ", "
				  << _normals[i].z << ")" << std::endl;
	}

	n = _faces.size();
	for(int i = 0; i < n; i++) {
		int n2 = _faces[i].size();
		std::cout << "face [" << i << "] : " << std::endl;
		for(int j = 0; j < n2; j++) {
			std::cout << "	index [" << j << "] : (v, vt, vn) = "
					  << "(" << _faces[i][j].v << ", "
					  << _faces[i][j].vt << ", "
					  << _faces[i][j].vn << "), mtl: " << _faces[i][j].mtlName << std::endl;
		}
	}

	std::cout << std::endl << "Materials:" << std::endl;
	for(auto it = _mtlMap.begin(); it != _mtlMap.end(); ++it) {
		std::cout << "	Material name: " << it->first << std::endl;
		Mtl _mtl = it->second;
		std::cout << "		ka: (r, g, b) =  " 
				<< "(" << _mtl.ka.r << ", "
				<< _mtl.ka.g << ", "
				<< _mtl.ka.b << ")" << std::endl;
		std::cout << "		kd: (r, g, b) =  " 
				<< "(" << _mtl.kd.r << ", "
				<< _mtl.kd.g << ", "
				<< _mtl.kd.b << ")" << std::endl;
		std::cout << "		ks: (r, g, b) =  " 
				<< "(" << _mtl.ks.r << ", "
				<< _mtl.ks.g << ", "
				<< _mtl.ks.b << ")" << std::endl;
		std::cout << "		Ns, Ni, d, illum: "
				<< _mtl.Ns << ", "
				<< _mtl.Ni << ", "
				<< _mtl.d << ", "
				<< _mtl.illum << std::endl;
		std::cout << "		map_Kd: " << _mtl.mapKd << std::endl;
	}
	std::cout << "Textures:" << std::endl;
	n = _textures.size();
	for(int i = 0; i < n; i++) {
		std::cout << "	" << i + 1<< " : " << _textures[i] << std::endl;
	}
}

std::vector<unsigned int> Object::getFacesIndices() const {
	std::vector<unsigned int> indice;
	for(const auto& face : _faces) {
		for(const auto& idv : face) {
			indice.push_back(idv.v);
		}
	}
	return indice;
}

void Object::buildVertex() {
	_verticeBuild.clear();
	_indiceBuild.clear();
	_indexMap.clear();

	for(auto &f : _faces) {
		int count = f.size();
		for(int i = 1; i < count - 1 ; ++i) {
			std::array<int, 3> tri = {0, i, i + 1};
			
			for(int idx : tri) {
				auto key = std::make_tuple(f[idx].v, f[idx].vt, f[idx].vn);
				
				if(_indexMap.count(key) == 0) {
					Vertex v;
					v.pos = _vertices[f[idx].v];
					if(f[idx].vn >= 0 && f[idx].vn < static_cast<int>(_normals.size()))
						v.normal = _normals[f[idx].vn];
					else
						v.normal = Vect3(0.0f, 0.0f, 1.0f);
					
					if (f[idx].vt >= 0 && f[idx].vt < static_cast<int>(_uvs.size()))
						v.uv = _uvs[f[idx].vt];
					else
						v.uv = Vect2(0.0f, 0.0f);
						
					v.uv.y = 1.0f - v.uv.y; // OpenGl need an origin at bottom-left but Blender at top-left

					if (!f[idx].mtlName.empty()) {
						const Mtl mtl = _mtlMap[f[idx].mtlName];
						if (!mtl.mapKd.empty())
							v.hasTex = 1.0f;
						else
							v.color = Vect3(mtl.kd.r, mtl.kd.g, mtl.kd.b);
					} else
						v.hasTex = 1.0f;
					_verticeBuild.push_back(v);
					_indexMap[key] = _verticeBuild.size() - 1;
				}

				_indiceBuild.push_back(_indexMap[key]);
			}
		}
	}
}

void Object::centerAndScaleToUnit() {
	Vect3 center(
		(_verticeMin.x + _verticeMax.x) / 2.0f,
		(_verticeMin.y + _verticeMax.y) / 2.0f,
		(_verticeMin.z + _verticeMax.z) / 2.0f
	);
	float maxDim = std::max({
		_verticeMax.x - _verticeMin.x,
		_verticeMax.y - _verticeMin.y,
		_verticeMax.z - _verticeMin.z
	});
	
	float scale = (maxDim > 0) ? (1.0f / maxDim) : 1.0f;
	
	_modelMatrix = Mat4::translate( -center.x, -center.y, -center.z )
				* Mat4::scale( scale, scale, scale );
}

void Object::updateMatrix(GLFWwindow* win) {
	_m.update(glfwGetKey(win, GLFW_KEY_M) == GLFW_PRESS);
	if (_m.pressed()) {
		_stopMove = !_stopMove;
	}
	
	if (!_stopMove) {
		float angle = 1.0f/360.0f; // rotation speed
		_modelMatrix = _modelMatrix * Mat4::rotateY(angle);
	}
}
