/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:44:45 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/27 17:10:14 by lde-merc         ###   ########.fr       */
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
	try {
		inputValidate(argc, argv);
		_obj->load(argv[3]);
		initGLFW();					// Create the window
		initOpenGL();				// Configure OpenGl global
	} catch (fileError &e) {
		std::cerr << "\033[31mFile error:\033[m" << std::endl << e.what() << std::endl;
		exit(1);
	} catch (glfwError &e) {
		std::cerr << "\033[31mGLFW error:\033[m" << std::endl << e.what() << std::endl;
		exit(1);
	} catch (openGlError &e) {
		std::cerr << "\033[31mOpenGl error:\033[m" << std::endl << e.what() << std::endl;
		exit(1);
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
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
	if (argc != 5) {
		std::stringstream ss;
		ss << "Not enough arguments,\n";
		ss << "The program needs the following:\n";
		ss << "A vertex shader, fragment shader, an object file, a texture.";
		throw std::runtime_error(ss.str());
	}
	std::string fileName = argv[3];
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
		
	std::string namewin = getObj()->getName();
	if (namewin.empty())
		namewin = "Scop";
		
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	_window = glfwCreateWindow(WIDTH, HEIGHT, namewin.c_str(), nullptr, nullptr);
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
