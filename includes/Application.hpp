/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 09:36:08 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/27 17:07:32 by lde-merc         ###   ########.fr       */
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

static int HEIGHT = 800;
static int WIDTH = 1200;

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
		
		void initGLFW();
		void initOpenGL();
		void inputValidate(int, char **);
};
