/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:34:11 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/01 14:23:02 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <functional>

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

		void saveTex(int, char **);

		std::string getName() {return _name;};
		std::vector<std::string> getTexturesPath() const {return _textures;};

		void display();
		
	private:
		Mtl _mtl;
		std::vector<Vect3> _vertices;
		std::vector<Vect3> _uvs;
		std::vector<Vect3> _normals;
		std::vector<std::vector<Index>> _faces;

		std::vector<std::string> _textures;
		
		// Transformation
		Mat4 _modelMatrix;

		std::string _name;
};
