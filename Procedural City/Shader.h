/*
    Copyright (C) 2015 Panagiotis Roubatsis

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

/*
	Created by Panagiotis Roubatsis
	Description: An abstract class which
	can be used for loading and applying
	shaders to irrlicht nodes.
*/

#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <irrlicht.h>

class Shader
{
public:
	const static int TYPE_PIXEL = 1;
	const static int TYPE_VERT = 1 << 1;

	virtual void load(std::string,irr::video::IGPUProgrammingServices*,int) = 0;
	virtual void apply(irr::scene::ISceneNode*) = 0;
};

#endif