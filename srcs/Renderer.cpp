/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:33:39 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/24 13:04:32 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer.hpp"

Renderer::Renderer() {}

Renderer::~Renderer() {}

static std::string loadShaderSource(const std::string &filePath) {
	std::ifstream file(filePath);
	if (!file.is_open())
		throw std::runtime_error("Failed to open shader file: " + filePath);

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

static GLuint compileShader(const std::string &source, GLenum type) {
	GLuint shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[512];
		glGetShaderInfoLog(shader, 512, nullptr, log);
		throw std::runtime_error(std::string("Shader compilation failed: ") + log);
	}
	return shader;
}

void Renderer::init() {
	// Compilation des shaders
	string vertexSrc   = loadShaderSource("shaders/vertex.vs");
	string fragmentSrc = loadShaderSource("shaders/fragment.fs");
	
	GLuint vertexShader   = compileShader(vertexSrc, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);

	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, vertexShader);
	glAttachShader(_shaderProgram, fragmentShader);
	glLinkProgram(_shaderProgram);

	GLint success;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char log[512];
		glGetProgramInfoLog(_shaderProgram, 512, nullptr, log);
		throw std::runtime_error(std::string("Shader linking failed: ") + log);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Configuration d'OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void Renderer::render(Model model, Camera camera, Material material) {
	// Step 1 : CLear the screen
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Step 2 : Activate the shader
	glUseProgram(_shaderProgram);
	
	// Step 3 : Build the MVP Matrix
	Mat4 modelMat = model.getModelMatrix();
	Mat4 viewMat = camera.getViewMatrix();
	Mat4 proj = camera.getProjectionMatrix();

	Mat4 mvp = proj * viewMat * modelMat;

	// Step 4 : Send the matrix to shader
	GLint loc = glGetUniformLocation(_shaderProgram, "uMVP");
	glUniformMatrix4fv(loc, 1, GL_FALSE, mvp.getMatrix());
	
	// Step 5 : Apply material
	material.apply(_shaderProgram);

	// Step 6 : Draw the model
	model.draw();
}

void Renderer::destroy() {
	
}

