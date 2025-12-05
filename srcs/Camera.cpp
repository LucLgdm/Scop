/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:19:33 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/05 13:48:31 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

	// Constructeur
Camera::Camera() {
	_projMatrix = Mat4::perspective(45.0f, (float)WIDTH/(float)HEIGHT, 0.1f, 10.0f);
	
		// movement keys
	_keys[GLFW_KEY_W] = KeyState(); // front
	_keys[GLFW_KEY_S] = KeyState(); // back
	_keys[GLFW_KEY_A] = KeyState(); // left
	_keys[GLFW_KEY_D] = KeyState(); // right
	_keys[GLFW_KEY_Q] = KeyState(); // up
	_keys[GLFW_KEY_E] = KeyState(); // down
	
		// axes keys
	_keys[GLFW_KEY_I] = KeyState(); // x anticlock
	_keys[GLFW_KEY_K] = KeyState(); // x clock
	_keys[GLFW_KEY_L] = KeyState(); // y anticlock
	_keys[GLFW_KEY_J] = KeyState(); // y clock
	_keys[GLFW_KEY_U] = KeyState(); // z anticlock
	_keys[GLFW_KEY_O] = KeyState(); // z clock
	
	_currentPos = Vect3(0.0f, 0.0f, 2.0f);
	_currentDir = Vect3(0.0f, 0.0f, 0.0f);
	
	
}

Camera::~Camera() {}

Camera::Camera(const Camera &other) {
	*this = other;
}

Camera &Camera::operator=(const Camera &other) {
	if (this != &other) {
		_viewMatrix = other._viewMatrix;
		_projMatrix = other._projMatrix;
	}
	return *this;
}

void Camera::updateCam(GLFWwindow* win, float time) { 
		// Update key states
	for(auto &keyPair : _keys) {
		keyPair.second.update(glfwGetKey(win, keyPair.first) == GLFW_PRESS);
	}
	
	movementControl();		
	
	_viewMatrix = Mat4::lookAt(_currentPos, _currentDir, Vect3(0.0f, 1.0f, 0.0f));
}

void Camera::movementControl() {
	float moveSpeed = 0.002f;
	
	if (_keys[GLFW_KEY_W].isDown) {
		_currentDir.z -= moveSpeed;
		_currentPos.z -= moveSpeed;
	}
	if (_keys[GLFW_KEY_S].isDown) {
		_currentDir.z += moveSpeed;
		_currentPos.z += moveSpeed;
	}
	if (_keys[GLFW_KEY_A].isDown) {
		_currentDir.x -= moveSpeed;
		_currentPos.x -= moveSpeed;
	}
	if (_keys[GLFW_KEY_D].isDown) {
		_currentDir.x += moveSpeed;
		_currentPos.x += moveSpeed;
	}
	if (_keys[GLFW_KEY_Q].isDown) {
		_currentDir.y += moveSpeed;
		_currentPos.y += moveSpeed;
	}
	if (_keys[GLFW_KEY_E].isDown) {
		_currentDir.y -= moveSpeed;
		_currentPos.y -= moveSpeed;
	}
}

