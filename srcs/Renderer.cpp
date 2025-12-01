/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:18:27 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/01 14:30:09 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Renderer.hpp"

// Constructeur
Renderer::Renderer() {
	_vao = 0; _vbo = 0; _ebo = 0;
	_shaderProgram = 0;
}

Renderer::~Renderer() {}

Renderer::Renderer(const Renderer &other) {
    *this = other;
}

Renderer &Renderer::operator=(const Renderer &other) {
    if (this != &other) {
        this->_vao = other._vao;
        this->_vbo = other._vbo;
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