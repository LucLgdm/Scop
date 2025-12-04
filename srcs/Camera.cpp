/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:19:33 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/04 10:18:20 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

// Constructeur
Camera::Camera() {
	_viewMatrix = Mat4::lookAt(
		Vect3(0.0f, 0.0f, 1.0f),
		Vect3(0.0f, 0.0f, 0.0f),
		Vect3(0.0f, 1.0f, 0.0f)
	);
	_projMatrix = Mat4::perspective(45.0f, (float)WIDTH/(float)HEIGHT, 0.1f, 10.0f);

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

void Camera::updateview(float time) {
	_viewMatrix = Mat4::lookAt(Vect3(2.0f * std::cos(time), 0.0f, 2.0f * std::sin(time)),
								Vect3(0.0f, 0.0f, 0.0f),
								Vect3(0.0f, 1.0f, 0.0f));
}
