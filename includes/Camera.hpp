/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:37:53 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/24 13:01:50 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Mat4.hpp"

class Camera {
	public :
		Camera();
		~Camera();

		Mat4 getViewMatrix() const;
		Mat4 getProjectionMatrix() const;
		void moveForward();
	private :
		// Describe where the camera is in the scene et in which direction it looks
		// When the camera moves, the world is moving
		Mat4 _viewMatrix;
		// Describe how the 3D is projected on a 2D screen
		Mat4 _projMatrix;
};
