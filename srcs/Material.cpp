/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:00:59 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/21 15:39:58 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Material.hpp"

Material::Material() : _colorMode(0), _useTexture(false) {}

Material::~Material() {}

void Material::setColorMode() {
	_colorMode = (_colorMode + 1) % 3;
}

void Material::toogleTexture() {
	_useTexture = !_useTexture;
}

void Material::apply(GLuint program) const {
	glUseProgram(program);
	
	GLint locColorMode = glGetUniformLocation(program, "uColorMode");
	GLint locUseTexture = glGetUniformLocation(program, "uUseTexture");

	if (locColorMode != -1)
		glUniform1i(locColorMode, _colorMode);

	if (locUseTexture != -1)
		glUniform1i(locUseTexture, _useTexture);
}