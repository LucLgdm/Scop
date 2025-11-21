/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 09:35:54 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/21 14:04:37 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Renderer.hpp"
#include "Input.hpp"
#include <exception>

static int HEIGHT = 800;
static int WIDTH = 600;

class Application {
	public :
		Application();
		~Application();
		
		void init(const string &);
		void run();
		void cleanup();
	
	private :
		GLFWwindow* _window;
		Camera _camera;
		Renderer _renderer;
		Model _model;
		Input _input;
		Material _material;

		void initGLFW();
		void initOpenGL();
};