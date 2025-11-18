/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:35:47 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/18 10:46:25 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"


// -------------------------------------------------------------
// Initialization
// -------------------------------------------------------------
GLFWwindow* initWindow(int width, int height, const char* title) {
	if (!glfwInit()) return nullptr;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window) { glfwTerminate(); return nullptr; }

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";
		return nullptr;
	}
	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// -------------------------------------------------------------
// Shaders
// -------------------------------------------------------------
unsigned int createShaderProgram() {
	const char* vertexShaderSource = R"(
		#version 330 core
		layout(location = 0) in vec2 aPos;
		void main() {
			gl_Position = vec4(aPos, 0.0, 1.0);
		}
	)";
	const char* fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;
		void main() {
			FragColor = vec4(1.0, 0.5, 0.2, 1.0);
		}
	)";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

