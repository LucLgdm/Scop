/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:18:20 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/28 11:24:06 by lde-merc         ###   ########.fr       */
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

class Renderer {
	public:
		Renderer();
		~Renderer();
		Renderer(const Renderer &other);
		
		Renderer &operator=(const Renderer &other);
		void init();

	private:
		GLuint _vao;
		GLuint _vbo;
		GLuint _ebo;
		GLuint _shaderProgram;

		


};
