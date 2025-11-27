/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:53:55 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/27 17:02:13 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

struct Vect3 {
	float x, y, z;
};

struct Index {
	int v, vt, vn;
};

struct Vertex {
	float x, y, z, texX, texY, normalX, normalY, normalZ;	
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
	Ka ka;
	Kd kd;
	Ks ks;
	float Ns, Ni, d;
	int illum;
};
