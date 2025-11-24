/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:59:05 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/24 13:02:16 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

Camera::Camera() {
	_viewMatrix = Mat4::identity();
	_projMatrix = Mat4::identity();
}

Camera::~Camera() {}

Mat4 Camera::getViewMatrix() const {
	return _viewMatrix;
}

Mat4 Camera::getProjectionMatrix() const {
	return _projMatrix;
}

void Camera::moveForward() {
	
}

