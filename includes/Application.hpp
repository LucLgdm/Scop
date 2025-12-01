/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 09:36:08 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/01 18:16:54 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


#include "exception.hpp"
#include "Object.hpp"
#include "Renderer.hpp"

static int HEIGHT = 1200;
static int WIDTH = 1600;

class Application {
	public :
		Application();
		~Application();
		
		void init(int, char **);
		void run();
		void cleanup();

		Object *getObj() {return _obj;}
		
	private :
		GLFWwindow* _window;
		Object *_obj;
		Renderer _renderer;

		Mat4 _viewMatrix;
		Mat4 _projMatrix;
		
		void initGLFW();
		void initOpenGL();
		void inputValidate(int, char **);
};
