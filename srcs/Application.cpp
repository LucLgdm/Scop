/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:44:45 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/03 17:12:52 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Application.hpp"

Application::Application() {
	_obj = new Object;
	_viewMatrix = Mat4::lookAt(
		Vect3(0.0f, 40.0f, -10.0f),
		Vect3(0.0f, 0.0f, 0.0f),
		Vect3(0.0f, 0.0f, 1.0f)
	);
	_projMatrix = Mat4::identity();
}

Application::~Application() {
	delete _obj;
}

void Application::init(int argc, char **argv) {
	inputValidate(argc, argv);
	_obj->load(argv[1]);		// Load the mesh
	_obj->setTexturesPath();	// Load the textures
	_obj->buildVertex();
	initGLFW();					// Create the window
	initOpenGL();				// Configure OpenGl global
	_renderer.init();			// Load the shaders
	_renderer.loadTextures(*_obj);
	_renderer.setUpMesh(*_obj);	
	// _obj->display();
	// _renderer.display();
	
	_projMatrix = Mat4::perspective(45.0f, (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);
}

void Application::run() {
	while (!glfwWindowShouldClose(_window)) {
		float time = glfwGetTime() / 2;

		glClearColor(0.2f, 0.2f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(_renderer.getShaderProg());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderer.getTexGPU(0));

		GLint texLoc = glGetUniformLocation(_renderer.getShaderProg(), "uTexture");
		glUniform1i(texLoc, 0);

		_viewMatrix = Mat4::lookAt(Vect3(45 * std::cos(time), 45 * std::sin(time), 10.0f),
								Vect3(0.0f, 0.0f, 12.0f),
								Vect3(0.0f, 0.0f, 1.0f));
		GLuint modelLoc = glGetUniformLocation(_renderer.getShaderProg(), "model");
		GLuint viewLoc  = glGetUniformLocation(_renderer.getShaderProg(), "view");
		GLuint projLoc  = glGetUniformLocation(_renderer.getShaderProg(), "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, _obj->getMat().data());
		glUniformMatrix4fv(viewLoc,  1, GL_FALSE, _viewMatrix.data());
		glUniformMatrix4fv(projLoc,  1, GL_FALSE, _projMatrix.data());

		glBindVertexArray(_renderer.getVAO());
		glBindTexture(GL_TEXTURE_2D, _renderer.getTexGPU(0));

		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
			// Triangle
		glDrawElements(GL_TRIANGLES, _obj->getIndiceBuild().size(), GL_UNSIGNED_INT, 0);

		// glDrawArrays(GL_TRIANGLES, 0, _obj->getVertex().size());
			// Points
		// glDrawElements(GL_POINTS, _obj->getIndiceBuild().size() * 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

void Application::cleanup() {
	glfwTerminate();
}

void Application::inputValidate(int argc, char **argv) {
	if (argc < 2) {
		std::stringstream ss;
		ss << "Not enough arguments,\n";
		ss << "The program needs an object file";
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
