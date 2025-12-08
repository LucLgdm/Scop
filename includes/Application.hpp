/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 09:36:08 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/05 15:37:45 by lde-merc         ###   ########.fr       */
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
#include "Camera.hpp"

class Application {
	public :
		Application();
		~Application();
		
		void init(int, char **);
		void run();
		void cleanup();

		void updateState();

		Object *getObj() {return _obj;}
		Renderer &getRenderer() {return _renderer;};
		
	private :
		GLFWwindow* _window;
		Object *_obj;
		Renderer _renderer;
		Camera _camera;
		
		std::map<int, KeyState> _keys;
		int _state;		
		int _indiceTex;
		
		void initGLFW();
		void initOpenGL();
		void inputValidate(int, char **);
};
