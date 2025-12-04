/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:19:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/04 10:18:04 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include "Mat4.hpp"


class Camera {
	public:
		Camera();
		~Camera();
		Camera(const Camera &other);
		
		Camera &operator=(const Camera &other);

		void updateview(float);


		Mat4 getViewMatrix() const { return _viewMatrix; };
		Mat4 getProjMatrix() const { return _projMatrix; };

	private:
		Mat4 _viewMatrix;
		Mat4 _projMatrix;

};
