/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:44:45 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/28 11:41:03 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Application.hpp"

static float lastFrameTime = 0.0f;
static float deltaTime = 0.0f;

Application::Application() {
	_obj = new Object;
}

Application::~Application() {
	delete _obj;
}

void Application::init(int argc, char **argv) {
	inputValidate(argc, argv);
	_obj->load(argv[1]);		// Load the mesh
	_obj->saveTex(argc, argv);	// Load the textures
	initGLFW();					// Create the window
	initOpenGL();				// Configure OpenGl global
	_renderer.init();			// Load the shaders
	_obj->display();
}

void Application::run() {
	while(!glfwWindowShouldClose(_window)) {
		float currentFrameTime = (float)glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;
		
		glfwPollEvents();

		glfwSwapBuffers(_window);
	}
}

void Application::cleanup() {
	glfwTerminate();
}

void Application::inputValidate(int argc, char **argv) {
	if (argc < 3) {
		std::stringstream ss;
		ss << "Not enough arguments,\n";
		ss << "The program needs the following:\n";
		ss << "An object file, textures.";
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
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}
