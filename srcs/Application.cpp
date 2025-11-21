/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 09:36:08 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/21 15:40:35 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Application.hpp"

static float lastFrameTime = 0.0f;
static float deltaTime = 0.0f;

Application::Application() {}

Application::~Application() {}

void Application::init(const string &file) {
	try {
		initGLFW();					// Create the window
		initOpenGL();				// Configure OpenGl global
		_renderer.init();			// Compile shaders + ressources renderer
		_model.loadOBJ(file);
		_material.setColorMode();
	} catch (fileError &e) {
		cout << e.what() << endl;
		exit(1);
	}
}

void Application::run() {
	while(!glfwWindowShouldClose(_window)) {
		float currentFrameTime = (float)glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
		
		glfwPollEvents();
		_input.update();
		
		if (_input.isKeyPressed(GLFW_KEY_T))
			_material.toogleTexture();
			
		if (_input.isKeyPressed(GLFW_KEY_UP))
			_camera.moveForward();
			
		_model.rotate(deltaTime);
		_renderer.render(_model, _camera, _material);

		glfwSwapBuffers(_window);
	}
}

void Application::cleanup() {
	_model.destroy();
	_renderer.destroy();
	glfwTerminate();
}

void Application::initGLFW() {
    if (!glfwInit())
        throw std::runtime_error("GLFW initialization failed");
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    _window = glfwCreateWindow(HEIGHT, WIDTH, "Scop", nullptr, nullptr);
    if (!_window)
        throw std::runtime_error("Window creation failed");
    
    glfwMakeContextCurrent(_window);
}

void Application::initOpenGL() {
    // Charger les fonctions OpenGL avec Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");
    
    // Configuration OpenGL
    glViewport(0, 0, HEIGHT, WIDTH);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}
