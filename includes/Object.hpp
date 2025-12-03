/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:34:11 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/03 17:03:40 by lde-merc         ###   ########.fr       */
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
		void setFaces(std::istringstream&, std::string);

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

		void setTexturesPath();
		void display();
		
	private:
		std::unordered_map<std::string, Mtl> _mtlMap;
		std::vector<Vect3> _vertices;
		std::vector<Vect2> _uvs;
		std::vector<Vect3> _normals;
		std::vector<std::vector<Index>> _faces;

		std::vector<std::string> _textures;
		std::vector<Vertex> _verticeBuild;
		std::vector<unsigned int> _indiceBuild;
		std::map<std::tuple<int, int, int>, unsigned int> _indexMap;

		Mat4 _modelMatrix;

		std::string _name;
};
