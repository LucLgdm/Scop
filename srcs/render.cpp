/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:38:00 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/18 10:55:50 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

// -------------------------------------------------------------
// Render loop
// -------------------------------------------------------------
void renderLoop(GLFWwindow* window, unsigned int VAO, unsigned int shaderProgram) {
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 9); // n vertices,  starting from index 0

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

// -------------------------------------------------------------
// Cleanup
// -------------------------------------------------------------
void cleanup(unsigned int VAO, unsigned int VBO, unsigned int shaderProgram, GLFWwindow* window) {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
}
