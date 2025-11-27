/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:34:11 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/27 16:36:23 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <functional>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Mat4.hpp"
#include "utils.hpp"
#include "exception.hpp"


class Object {
	public:
		Object();
		~Object();
		Object(const Object &other);
		
		Object &operator=(const Object &other);
		
		void load(char *);
		void setNameAndCoord(std::istringstream&, std::string);
		void setVertexCoord(std::istringstream&);
		void setMtAttributes(std::istringstream&);
		void setFaces(std::istringstream&);

		std::string getName() {return _name;};
		
	private:
		Mtl _mtl;
		std::vector<Vect3> _vertices;
		std::vector<Vect3> _uvs;
		std::vector<Vect3> _normals;
		std::vector<std::vector<Index>> _faces;
		
		// OpenGL
		GLuint _vao;
		GLuint _vbo;
		GLuint _ebo;

		// Transformation
		Mat4 _modelMatrix;

		std::string _name;
};
