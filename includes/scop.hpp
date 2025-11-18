/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:15:44 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/18 11:10:21 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
using namespace std;

#include "exception.hpp"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

/* Initialisation */
GLFWwindow* initWindow(int width, int height, const char* title);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int createShaderProgram();

/* Heart of the project*/
void renderLoop(GLFWwindow* window, unsigned int VAO, unsigned int shaderProgram);


/* Cleanup */
void cleanup(unsigned int VAO, unsigned int VBO, unsigned int shaderProgram, GLFWwindow* window);
