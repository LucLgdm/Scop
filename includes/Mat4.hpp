/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mat4.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:47:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/01 18:13:42 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cmath>
#include <iostream>
using namespace std;

#include "utils.hpp"

class Mat4 {
	public:
		Mat4();

		const float *getMatrix() const;
		static Mat4 identity();
		static Mat4 null();
		static Mat4 translate(float x, float y, float z);
		static Mat4 scale(float sx, float sy, float sz);
		static Mat4 rotateX(float angle);
		static Mat4 rotateY(float angle);
		static Mat4 rotateZ(float angle);
		static Mat4 perspective(float fovDeg, float aspect, float near, float far);
		static Mat4 lookAt(const Vect3 &eye, const Vect3 &center, const Vect3 &up);

		Mat4 operator*(const Mat4 &other) const;

		const float* data() const { return m; }
		float* data() { return m; }

		
		void print() const;

	private:
		float m[16];
};
