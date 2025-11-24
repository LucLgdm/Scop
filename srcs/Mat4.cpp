/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mat4.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:48:35 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/24 13:07:08 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mat4.hpp"

Mat4::Mat4() {
	for (int i = 0; i < 16; i++) {
		m[i] = 0.0f;
	}
}

const float *Mat4::getMatrix() const {
	return m;
}

Mat4 Mat4::identity() {
	Mat4 mat;
	mat.m[0]  = 1.0f;
	mat.m[5]  = 1.0f;
	mat.m[10] = 1.0f;
	mat.m[15] = 1.0f;
	return mat;
}

Mat4 Mat4::translate(float x, float y, float z) {
	Mat4 mat = identity();
	mat.m[12] = x;
	mat.m[13] = y;
	mat.m[14] = z;
	return mat;
}

Mat4 Mat4::scale(float sx, float sy, float sz) {
	Mat4 mat = identity();
	mat.m[0]  = sx;
	mat.m[5]  = sy;
	mat.m[10] = sz;
	return mat;
}


Mat4 Mat4::rotateX(float angle) {
	Mat4 result = identity();
	float c = std::cos(angle);
	float s = std::sin(angle);
	
	result.m[5] = c;
	result.m[9] = -s;
	result.m[6] = s;
	result.m[10] = c;
	return result;
}

Mat4 Mat4::rotateY(float angle) {
	Mat4 result = identity();
	float c = std::cos(angle);
	float s = std::sin(angle);
	
	result.m[0] = c;
	result.m[8] = s;
	result.m[2] = -s;
	result.m[10] = c;
	return result;
}

Mat4 Mat4::rotateZ(float angle) {
	Mat4 mat = identity();
	float c = std::cos(angle);
	float s = std::sin(angle);

	mat.m[0] = c;
	mat.m[4] = -s;
	mat.m[1] = s;
	mat.m[5] = c;

	return mat;
}

Mat4 Mat4::operator*(const Mat4 &other) const {
	Mat4 result;

	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			result.m[row * 4 + col] =
				m[row * 4 + 0] * other.m[0 * 4 + col] +
				m[row * 4 + 1] * other.m[1 * 4 + col] +
				m[row * 4 + 2] * other.m[2 * 4 + col] +
				m[row * 4 + 3] * other.m[3 * 4 + col];
		}
	}

	return result;
}

void Mat4::print() const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			cout << m[i * 4 + j] << " ";
		cout << "\n";
	}
}