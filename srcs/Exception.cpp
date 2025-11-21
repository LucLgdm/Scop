/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:47:52 by lde-merc          #+#    #+#             */
/*   Updated: 2025/11/21 15:49:22 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exception.hpp"

fileError::fileError() : _msg("file error") {}

fileError::~fileError() {}

fileError::fileError(string message) : _msg(message) {}

const char * fileError::what() const noexcept {return _msg.c_str();}
