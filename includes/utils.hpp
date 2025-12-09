/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:53:55 by lde-merc          #+#    #+#             */
/*   Updated: 2025/12/09 17:33:50 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

static int HEIGHT = 1200;
static int WIDTH = 1600;

struct Vect3 {
	float x, y, z;
	Vect3() : x(0), y(0), z(0) {}
	Vect3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

	Vect3 operator-(const Vect3& other) const {
		return Vect3(x - other.x, y - other.y, z - other.z);
	}

	Vect3 operator+(const Vect3& other) const {
		return Vect3(x + other.x, y + other.y, z + other.z);
	}

	Vect3 operator*(float s) const {
		return Vect3(x * s, y * s, z * s);
	}

	const float* data() const { return &x; }
};

static Vect3 cross(const Vect3& a, const Vect3& b) {
	return Vect3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

static float dot(const Vect3& a, const Vect3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static Vect3 normalize(const Vect3& v) {
	float len = std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	if (len == 0) return Vect3(0,0,0);
	return Vect3(v.x/len, v.y/len, v.z/len);
}

struct Vect2 {
	float x, y;
	Vect2() : x(0), y(0) {}
	Vect2(float xx, float yy) : x(xx), y(yy) {};
};

struct Index {
	int v, vt, vn;
	std::string mtlName;
};

struct Vertex {
	Vect3 pos;
	Vect3 normal;
	Vect2 uv;
	Vect3 color;
	float hasTex;
	
	Vertex() : pos(), normal(), uv(), color(), hasTex(0.0f) {};
};


struct Ka {
	float r, g, b;
};

struct Kd {
	float r, g, b;
};

struct Ks {
	float r, g, b;
};

struct Mtl {
	std::string name;
	Ka ka;
	Kd kd;
	Ks ks;
	float Ns, Ni, d;
	int illum;
	std::string mapKd;
	
	Mtl() : name(""), Ns(0), Ni(0), d(0), illum(0) {
		ka = {0, 0, 0};
		kd = {0, 0, 0};
		ks = {0, 0, 0};
	}
};

struct KeyState {
    bool isDown = false;
    bool wasDown = false;

    bool pressed() const {
        return isDown && !wasDown;
    }

    bool released() const {
        return !isDown && wasDown;
    }

    void update(bool currentDown) {
        wasDown = isDown;
        isDown = currentDown;
    }
};
