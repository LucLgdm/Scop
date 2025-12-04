/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:15:45 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/04 11:12:16 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Application.hpp"

int main(int argc, char *argv[]) {
	std::cout << "Hello, Scop!" << std::endl;
	Application app;
	try {
		app.init(argc, argv);
		app.run();
	} catch (fileError &e) {
		std::cerr << "\033[31mFile error:\033[m" << std::endl << e.what() << std::endl;
	} catch (glfwError &e) {
		std::cerr << "\033[31mGLFW error:\033[m" << std::endl << e.what() << std::endl;
	} catch (openGlError &e) {
		std::cerr << "\033[31mOpenGl error:\033[m" << std::endl << e.what() << std::endl;
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
