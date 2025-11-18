/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:15:45 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/18 11:41:42 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

int main(int argc, char *argv[]) {
	std::cout << "Hello, Scop!" << std::endl;

	
	
	GLFWwindow* window = initWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Scop");
	if (!window) return -1;

	unsigned int shaderProgram = createShaderProgram();

	unsigned int VAO, VBO;
	
	renderLoop(window, VAO, shaderProgram);

    cleanup(VAO, VBO, shaderProgram, window);
	return 0;
}
