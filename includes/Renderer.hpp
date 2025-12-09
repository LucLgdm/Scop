/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:18:20 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/09 17:26:40 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Object.hpp"

struct Light {
	Vect3 position;
	Vect3 color;
	float intensity;	
};

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

		void setLight(const Light& light) { _light = light; };
    	const Light& getLight() const { return _light; };

		void display();
		void cleanup();
		
	private:
		GLuint _vao;
		GLuint _vbo;
		GLuint _ebo;
		GLuint _shaderProgram;

		std::vector<GLuint> _texturesGPU;
		Light _light;
};
