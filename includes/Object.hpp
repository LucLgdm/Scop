/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:34:11 by lde-merc          #+#    #+#             */
/*   Updated: 2026/01/07 14:06:39 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <map>
#include <array>
#include <algorithm>
#include <limits>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mat4.hpp"
#include "exception.hpp"


class Object {
	public:
		Object();
		~Object();
		Object(const Object &other);
		
		Object &operator=(const Object &other);
		
		void load(int, char *);
		void setNameAndCoord(std::istringstream&, std::string);
		void setVertexCoord(std::istringstream&);
		void setMtAttributes(std::istringstream&);
		void setFaces(std::istringstream&, std::string);

		void centerAndScaleToUnit();

		void buildVertex(); // Vertices interleaves
		void saveTex(int, char **);

		std::string getName() {return _name;};
		std::vector<std::string> getTexturesPath() const {return _textures;};
		std::vector<Vect3> getPositions() const {return _vertices;};
		std::vector<Vect3> getNormals() const {return _normals;};
		std::vector<Vect2> getUVs() const {return _uvs;};
		std::vector<Vertex> getVertex() const {return _verticeBuild;};
		std::vector<unsigned int> getIndiceBuild() const {return _indiceBuild;};
		Mat4 getMat() const {return _modelMatrix;};
		std::vector<unsigned int> getFacesIndices() const;
		Vect3 getVerticeMin() const {return _verticeMin;};
		Vect3 getVerticeMax() const {return _verticeMax;};

		void setTexturesPath(int, char **);
		
		void updateMatrix(GLFWwindow*);

		void display();
		
	private:
		std::string _name;
		std::unordered_map<std::string, Mtl> _mtlMap;
		std::vector<Vect3> _vertices;
		std::vector<Vect2> _uvs;
		std::vector<Vect3> _normals;
		std::vector<std::vector<Index>> _faces;

		Vect3 _verticeMin;
		Vect3 _verticeMax;

		std::vector<std::string> _textures;
		std::vector<Vertex> _verticeBuild;
		std::vector<unsigned int> _indiceBuild;
		std::map<std::tuple<int, int, int>, unsigned int> _indexMap;

		std::vector<unsigned int> _indiceLine;
		Mat4 _modelMatrix;
		KeyState _m;
		KeyState _x;
		KeyState _y;
		KeyState _z;
		bool _stopMove = true;
};
