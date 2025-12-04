/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:19:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/04 17:14:42 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <map>

#include "Mat4.hpp"

struct GLFWwindow;


class Camera {
	public:
		Camera();
		~Camera();
		Camera(const Camera &other);
		
		Camera &operator=(const Camera &other);

		void updateCam(GLFWwindow*, float);
		void updateKeyStates(GLFWwindow*);
		void movementControl();

		Mat4 getViewMatrix() const { return _viewMatrix; };
		Mat4 getProjMatrix() const { return _projMatrix; };

	private:
		Mat4 _viewMatrix;
		Mat4 _projMatrix;

		Vect3 _currentPos;
		Vect3 _currentDir;
		Vect3 _currentRot;

		std::map<int, KeyState> _keys;
};
