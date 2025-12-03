/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:18:27 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/03 15:20:32 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Renderer.hpp"

// Constructeur
Renderer::Renderer() {
	_vao = 0;
	_vboPositions = 0; _vboNormals = 0; _vboUVs = 0;
	_ebo = 0;
	_shaderProgram = 0;
}

Renderer::~Renderer() {}

Renderer::Renderer(const Renderer &other) {
    *this = other;
}

Renderer &Renderer::operator=(const Renderer &other) {
    if (this != &other) {
        this->_vao = other._vao;
        this->_vboPositions = other._vboPositions;
        this->_vboNormals = other._vboNormals;
        this->_vboUVs = other._vboUVs;
        this->_ebo = other._ebo;
    }
    return *this;	
}

static std::string readFile(const char* path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error(std::string("Cannot open shader file: ") + path);

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Renderer::init() {
	const char* vPath = "shaders/vertex.glsl";
	const char* fPath = "shaders/fragment.glsl";

	std::string vCode = readFile(vPath);
	std::string fCode = readFile(fPath);

	const char* vSrc = vCode.c_str();
	const char* fSrc = fCode.c_str();
	
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vSrc, nullptr);
	glCompileShader(vShader);

	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fSrc, nullptr);
	glCompileShader(fShader);

	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, vShader);
	glAttachShader(_shaderProgram, fShader);
	glLinkProgram(_shaderProgram);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void Renderer::loadTextures(const Object& obj) {
	std::vector<std::string> texPath = obj.getTexturesPath();
	
	for(int i = 0; i < texPath.size(); i++) {
		int width, height, channels;
		unsigned char* data = stbi_load(texPath[i].c_str(), &width, &height, &channels, 0);
		if (!data)
			throw fileError("Failed to load texture");
		
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
		
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		stbi_image_free(data);
		_texturesGPU.push_back(texture);
	}
}

void Renderer::setUpMesh(const Object& obj) {
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// // Points
	// glGenBuffers(1, &_vboPositions);
	// glBindBuffer(GL_ARRAY_BUFFER, _vboPositions);
	// glBufferData(GL_ARRAY_BUFFER, obj.getPositions().size() * sizeof(Vect3),
	// 			obj.getPositions().data(), GL_STATIC_DRAW);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// glEnableVertexAttribArray(0);

	// // Normals
	// glGenBuffers(1, &_vboNormals);
	// glBindBuffer(GL_ARRAY_BUFFER, _vboNormals);
	// glBufferData(GL_ARRAY_BUFFER, obj.getNormals().size() * sizeof(Vect3),
	// 			obj.getNormals().data(), GL_STATIC_DRAW);
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// glEnableVertexAttribArray(1);

	// // UVs
	// glGenBuffers(1, &_vboUVs);
	// glBindBuffer(GL_ARRAY_BUFFER, _vboUVs);
	// glBufferData(GL_ARRAY_BUFFER, obj.getUVs().size() * sizeof(Vect2),
	// 			obj.getUVs().data(), GL_STATIC_DRAW);
	// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// glEnableVertexAttribArray(2);

	// VBO unique
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, obj.getVertex().size() * sizeof(Vertex),
				obj.getVertex().data(), GL_STATIC_DRAW);

		// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(0);
	
		// Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

		// Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glEnableVertexAttribArray(2);

		// Material color
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(3);

		// Has Texture
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, hasTex));
	glEnableVertexAttribArray(4);

	// EBO
	std::vector<unsigned int> indice = obj.getIndiceBuild();
	
	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice.size() * sizeof(unsigned int),
				indice.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Renderer::display() {
	std::cout << "vao : " << _vao << std::endl;
	std::cout << "vbo position : " << _vboPositions << std::endl;
	std::cout << "vbo Normals : " << _vboNormals << std::endl;
	std::cout << "vbo UVs: " << _vboUVs<< std::endl;
	std::cout << "ebo : " << _ebo << std::endl;
	std::cout << "shaderProgram : " << _shaderProgram << std::endl;

	for(int i = 0; i < _texturesGPU.size(); i++) {
		std::cout << "texture GPU " << i << ": " << _texturesGPU[i] << std::endl;
	}
}
