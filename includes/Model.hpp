/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:40:05 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/24 12:54:51 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <glad/glad.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "exception.hpp"
#include "Mat4.hpp"

class Model {	
	public :
		Model();
		~Model();
		void loadOBJ(const string &);
		void rotate(float, int);
		void destroy();
		void draw() const;

		Mat4 getModelMatrix() const;
	
	private :
		vector<float> _vertices;
		vector<unsigned int> _indices;
		unsigned int _vao;
		unsigned int _vbo;
		unsigned int _ebo;

		unsigned int indexCount;

		Mat4 _modelMatrix;
		
		void setupMesh();
};