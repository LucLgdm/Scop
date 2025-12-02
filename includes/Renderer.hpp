/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:18:20 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/01 17:18:03 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Object.hpp"

class Renderer {
	public:
		Renderer();
		~Renderer();
		Renderer(const Renderer &other);
		
		Renderer &operator=(const Renderer &other);
		
		void init();
		void loadTextures(const Object&);
		
		void setUpMesh(const Object&);

		GLuint getShaderProg() const {return _shaderProgram;};
		GLuint getVAO() const {return _vao;};
		GLuint getTexGPU(int i) const {return _texturesGPU[i];};

		void display();
		
	private:
		GLuint _vao;
		GLuint _vboPositions;
		GLuint _vboNormals;
		GLuint _vboUVs;
		GLuint _vbo;
		GLuint _ebo;
		GLuint _shaderProgram;

		std::vector<GLuint> _texturesGPU;
};
