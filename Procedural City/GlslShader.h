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
	Description: Load and apply GLSL shaders
	to irrlicht nodes.
*/

#ifndef GLSL_SHADER_H
#define GLSL_SHADER_H

#include "Shader.h"
#include <iostream>
#include <irrlicht.h>

class GlslShader : public Shader
{
private:
	irr::video::E_MATERIAL_TYPE _materialType;
	bool _isLoaded;

public:
	GlslShader();
	GlslShader(std::string fileName, irr::video::IGPUProgrammingServices* gpu, int type);

	void load(std::string fileName, irr::video::IGPUProgrammingServices* gpu, int type);
	void apply(irr::scene::ISceneNode* node);
};

#endif