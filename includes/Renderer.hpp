/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:41:43 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/21 14:08:04 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Camera.hpp"
#include "Model.hpp"
#include "Material.hpp"

#include <fstream>
#include <sstream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>


class Renderer {
	public :
		Renderer();
		~Renderer();
		void init();
		void render(Model, Camera, Material);
		void destroy();
	private :
		GLuint _shaderProgram;
};
