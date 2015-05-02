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

#include "GlslShader.h"

GlslShader::GlslShader()
{
	_isLoaded = false;
}

GlslShader::GlslShader(std::string fileName, irr::video::IGPUProgrammingServices* gpu, int type)
{
	load(fileName, gpu, type);
}

void GlslShader::load(std::string fileName, irr::video::IGPUProgrammingServices* gpu, int type)
{
	bool hasFrag = false;
	bool hasVert = false;
	std::string fragFile = "";
	std::string vertFile = "";
	
	//Adjust file with shader sub-folder and
	//the appropriate file extensions.

	if((type & Shader::TYPE_PIXEL) != 0)
	{
		fragFile = "shaders/glsl/";
		fragFile += fileName;
		fragFile += ".frag";

		hasFrag = true;
	}

	if((type & Shader::TYPE_VERT) != 0)
	{
		vertFile = "shaders/glsl/";
		vertFile += fileName;
		vertFile += ".vert";

		hasVert = true;
	}

	_materialType = (irr::video::E_MATERIAL_TYPE)gpu->addHighLevelShaderMaterialFromFiles(
			hasVert ? vertFile.c_str() : 0, hasVert ? "main" : 0, irr::video::EVST_VS_1_1,
			hasFrag ? fragFile.c_str() : 0, hasFrag ? "main" : 0, irr::video::EPST_PS_1_1
		);

	_isLoaded = true;
}

void GlslShader::apply(irr::scene::ISceneNode* node)
{
	if(_isLoaded)
		node->setMaterialType(_materialType);
}