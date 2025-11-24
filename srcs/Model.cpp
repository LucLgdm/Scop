/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:01:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/24 13:12:55 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Model.hpp"

Model::Model() : _vao(0), _vbo(0), _ebo(0) {
	_modelMatrix = Mat4::identity();
}

Model::~Model() {
	destroy();
}

Mat4 Model::getModelMatrix() const {
	return _modelMatrix;
}

void Model::loadOBJ(const string &file) {
	ifstream objFile(file);
	if (!objFile.is_open())
		throw fileError("Can't open file");
	
	_vertices.clear();
	_indices.clear();

	string line;
	while(getline(objFile, line)) {
		istringstream ss(line);
		string prefix;
		ss >> prefix;

		switch (prefix[0]) {
			case 'v' :
				float x, y, z;
				ss >> x >> y >> z;
				_vertices.push_back(x); _vertices.push_back(y); _vertices.push_back(z);
				break;
			case 'f' :
				unsigned int idx[4];
				int count = 0;
				string vertex;
				/*
				f 1 2 3             # Juste les vertices
				f 1/1 2/2 3/3       # Vertices/Textures
				f 1/1/1 2/2/2 3/3/3 # Vertices/Textures/Normales
				f 1//1 2//2 3//3    # Vertices//Normales	
				*/
				while(ss >> vertex) {
					size_t pos  = vertex.find('/');
					if (pos != string::npos)
						vertex = vertex.substr(0, pos); // on garde juste avant le '/' s'il y a '/'
					idx[count++] = stoi(vertex) - 1;    // convertit en int et decremente (OBJ commence a 1, OpenGl a 0)
				}
				if (count == 3) {
					_indices.push_back(idx[0]); _indices.push_back(idx[1]); _indices.push_back(idx[2]);
				}
				if (count == 4) { // quad -> 2 triangles
					_indices.push_back(idx[0]); _indices.push_back(idx[1]); _indices.push_back(idx[2]);
					_indices.push_back(idx[0]); _indices.push_back(idx[2]); _indices.push_back(idx[3]);
				}
				break;
		}
	}
	objFile.close();
	setupMesh();
}

void Model::rotate(float time, int axe) {
	float angle = time * 1.0f;
	Mat4 r;
	switch (axe) {
		case 0 :
			r = Mat4::rotateX(angle);
			break;
		case 1 :
			r = Mat4::rotateY(angle);
			break;
		case 2 :
			r = Mat4::rotateZ(angle);
			break;
	}
	_modelMatrix = r * _modelMatrix;
}

void Model::destroy() {
	if (_vao) glDeleteVertexArrays(1, &_vao);
	if (_vbo) glDeleteBuffers(1, &_vbo);
	if (_ebo) glDeleteBuffers(1, &_ebo);

	_vao = _vbo = _ebo = 0;
}

void Model::setupMesh() {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Model::draw() const {
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
