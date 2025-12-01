/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mat4.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:48:35 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/01 18:00:55 by lde-merc         ###   ########.fr       */
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

Mat4 Mat4::null() {
	Mat4 mat;
	for (int i = 0; i < 16; i++) {
		mat.m[i] = 0.0f;
	}
	return mat;
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

Mat4 Mat4::perspective(float fovDeg, float aspect, float near, float far) {
	float fovRad = fovDeg * (3.14159265359f / 180.0f);
	float f = 1.0f / std::tan(fovRad / 2.0f);

	Mat4 mat;

	mat.m[0]  = f / aspect;
	mat.m[5]  = f;
	mat.m[10] = (far + near) / (near - far);
	mat.m[11] = -1.0f;
	mat.m[14] = (2 * far * near) / (near - far);

	return mat;
}

Mat4 Mat4::lookAt(const Vect3 &eye, const Vect3 &center, const Vect3 &up) {
	Vect3 f = normalize(center - eye);
	Vect3 s = normalize(cross(f, up));
	Vect3 u = cross(s, f);

	Mat4 m = Mat4::identity();

	m.m[0] = s.x;
	m.m[1] = u.x;
	m.m[2] = -f.x;

	m.m[4] = s.y;
	m.m[5] = u.y;
	m.m[6] = -f.y;

	m.m[8] = s.z;
	m.m[9] = u.z;
	m.m[10] = -f.z;

	m.m[12] = -dot(s, eye);
	m.m[13] = -dot(u, eye);
	m.m[14] =  dot(f, eye);

	return m;
}

