/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:44:45 by lde-merc          #+#    #+#             */
/*   Updated: 2026/01/07 14:15:49 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Application.hpp"

Application::Application(): _state(0) {
	_obj = new Object;
	_keys[GLFW_KEY_P] = KeyState();
	_keys[GLFW_KEY_ESCAPE] = KeyState();
	_indiceTex = 0;
	_lightOn = false;
}

Application::~Application() {
	delete _obj;
	cleanup();
}

void Application::init(int argc, char **argv) {
	inputValidate(argc, argv);
	
	_obj->load(argc, argv[1]);		// Load the mesh
	_obj->centerAndScaleToUnit(); // Center and scale the object
	_obj->setTexturesPath(argc, argv);	// Load the textures
	_obj->buildVertex();

	initGLFW();					// Create the window
	initOpenGL();				// Configure OpenGl global

	_renderer.init();			// Load the shaders
	_renderer.loadTextures(*_obj);
	_renderer.setUpMesh(*_obj);

	// _obj->display();
	// _renderer.display();
	
}

void Application::run() {
	while (!glfwWindowShouldClose(_window)) {
		float time = glfwGetTime() / 2;
		
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(_renderer.getShaderProg());
	
			// Bind texture
		if (_obj->getTexturesPath().size() > 0)	{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _renderer.getTexGPU(_indiceTex));
			GLint texLoc = glGetUniformLocation(_renderer.getShaderProg(), "uTexture");
			glUniform1i(texLoc, 0);
		}
		
			// Update matrix
		_obj->updateMatrix(_window);
			// Update camera
		_camera.updateCam(_window);
			// Update state
		updateState();
		
			// Set uniforms
		GLuint modelLoc = glGetUniformLocation(_renderer.getShaderProg(), "model");
		GLuint viewLoc  = glGetUniformLocation(_renderer.getShaderProg(), "view");
		GLuint projLoc  = glGetUniformLocation(_renderer.getShaderProg(), "projection");
		
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, _obj->getMat().data());
		glUniformMatrix4fv(viewLoc,  1, GL_FALSE, _camera.getViewMatrix().data());
		glUniformMatrix4fv(projLoc,  1, GL_FALSE, _camera.getProjMatrix().data());

		GLuint lightOnLoc = glGetUniformLocation(_renderer.getShaderProg(), "uLightOn");
		glUniform1i(lightOnLoc, _lightOn ? 1 : 0);

		if (_lightOn) {
			GLuint lightPosLoc = glGetUniformLocation(_renderer.getShaderProg(), "lightPos");
			GLuint lightIntensityLoc = glGetUniformLocation(_renderer.getShaderProg(), "lightIntensity");
			glUniform3fv(lightPosLoc, 1, _renderer.getLight().position.data());
			glUniform1f(lightIntensityLoc, _renderer.getLight().intensity);
		}
		
		glBindVertexArray(_renderer.getVAO());
		
		switch (_state){
			case 0 : // Triangle
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glDrawElements(GL_TRIANGLES, _obj->getIndiceBuild().size(), GL_UNSIGNED_INT, 0);
				break;
			case 1 : // Points
				glDrawElements(GL_POINTS, _obj->getIndiceBuild().size(), GL_UNSIGNED_INT, 0);
				break;
			case 2 : // Lines
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glDrawElements(GL_TRIANGLES, _obj->getIndiceBuild().size(), GL_UNSIGNED_INT, 0);	
				break;
		}
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

void Application::cleanup() {
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void Application::inputValidate(int argc, char **argv) {
	if (argc == 1) {
		std::stringstream ss;
		ss << "Not enough arguments,\n";
		ss << "The program needs at least an object file in .obj format";
		ss << "and optionally texture files in .jpeg format.\n";
		throw std::runtime_error(ss.str());
	}
	std::string fileName = argv[1];
	if (fileName.length() >= 4 && fileName.substr(fileName.length() - 4) != ".obj")
		throw fileError("Invalid object file, it doesn't have .obj extension.");
		
	std::ifstream file(fileName);
	if (file.is_open()) {
		if (file.peek() == std::ifstream::traits_type::eof()) {
			file.close();
			throw fileError("The object file is empty.");
		}
		file.close();
	} else {
		throw fileError("Unable to open the object file.");
	}
}

void Application::initGLFW() {
	if (!glfwInit())
		throw glfwError("GLFW initialization failed");
		
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	_window = glfwCreateWindow(WIDTH, HEIGHT, getObj()->getName().c_str(), nullptr, nullptr);
	if (!_window)
		throw glfwError("Window creation failed");
	
	glfwMakeContextCurrent(_window);
}

void Application::initOpenGL() {
	// Charger les fonctions OpenGL avec Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw openGlError("Failed to initialize GLAD");
	
	// Configuration OpenGL
	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);
	// glDisable(GL_CULL_FACE);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void Application::updateState() {
	for(auto &key : _keys) {
		key.second.update(glfwGetKey(_window, key.first) == GLFW_PRESS);
	}

	if (_keys[GLFW_KEY_P].pressed())
		_state++;
	if (_state == 3)
		_state = 0;

	if (_keys[GLFW_KEY_T].pressed())
		_indiceTex++;
	if (_indiceTex == _obj->getTexturesPath().size())
		_indiceTex = 0;
	if (_keys[GLFW_KEY_ESCAPE].pressed())
		glfwSetWindowShouldClose(_window, true);
	if (_keys[GLFW_KEY_L].pressed())
		_lightOn = !_lightOn;
}

