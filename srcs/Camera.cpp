/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:19:33 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/08 15:05:12 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

	// Constructeur
Camera::Camera() {
	_projMatrix = Mat4::perspective(45.0f, (float)WIDTH/(float)HEIGHT, 0.1f, 10.0f);
	
	_yaw = -90.0f;
	_pitch = 0.0f;
	_moveSpeed = 0.002f;
	_turnSpeed = 0.2f;
	
	_currentPos = Vect3(0.0f, 0.0f, 2.0f);
	_orientation = Vect3(0.0f, 0.0f, 0.0f);
	
	
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

void Camera::updateCam(GLFWwindow* win) {
	Vect3 forward = normalize(_orientation);               // direction où regarde la caméra
	Vect3 right = normalize(cross(forward, Vect3(0,1,0))); // axe local droite
	Vect3 up = normalize(cross(right, forward)); 
	
	// Update key states
	for(auto &keyPair : _keys) {
		keyPair.second.update(glfwGetKey(win, keyPair.first) == GLFW_PRESS);
	}

	// Movement
	if (_keys[GLFW_KEY_W].isDown) _currentPos = _currentPos + forward * _moveSpeed;
	if (_keys[GLFW_KEY_S].isDown) _currentPos = _currentPos - forward * _moveSpeed;
	if (_keys[GLFW_KEY_A].isDown) _currentPos = _currentPos - right * _moveSpeed;
	if (_keys[GLFW_KEY_D].isDown) _currentPos = _currentPos + right * _moveSpeed;
	if (_keys[GLFW_KEY_Q].isDown) _currentPos = _currentPos + up * _moveSpeed;
	if (_keys[GLFW_KEY_E].isDown) _currentPos = _currentPos - up * _moveSpeed;

	// Rotation
	if (_keys[GLFW_KEY_LEFT].isDown) _yaw -= _turnSpeed;
	if (_keys[GLFW_KEY_RIGHT].isDown) _yaw += _turnSpeed;
	if (_keys[GLFW_KEY_UP].isDown) _pitch += _turnSpeed;
	if (_keys[GLFW_KEY_DOWN].isDown) _pitch -= _turnSpeed;

	// Clamp pitch pour éviter de retourner complètement la caméra
	if (_pitch > 89.0f) _pitch = 89.0f;
	if (_pitch < -89.0f) _pitch = -89.0f;

	// Recalculer la direction
	_orientation.x = cos(radians(_yaw)) * cos(radians(_pitch));
	_orientation.y = sin(radians(_pitch));
	_orientation.z = sin(radians(_yaw)) * cos(radians(_pitch));
	_orientation = normalize(_orientation);

	// Mise à jour de la matrice vue
	_viewMatrix = Mat4::lookAt(_currentPos, _currentPos + _orientation, up);
}
