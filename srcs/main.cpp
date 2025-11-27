/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:15:45 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/27 12:02:36 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Application.hpp"

int main(int argc, char *argv[]) {
	std::cout << "Hello, Scop!" << std::endl;
	
	Application app;
	app.init(argc, argv);
	app.run();
	app.cleanup();
	return 0;
}
