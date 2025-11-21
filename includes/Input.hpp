/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:04:27 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/21 11:00:38 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


class Input {
	public :
		Input();
		~Input();
		void update();
		bool isKeyPressed(int);

	private :
	
};
