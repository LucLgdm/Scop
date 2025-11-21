/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:38:56 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/21 15:35:10 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <glad/glad.h>

class Material {
	public :
		Material();
		~Material();

		void setColorMode();
		void toogleTexture();
		void apply(GLuint) const;
	private :
		int _colorMode;
		bool _useTexture;
};
