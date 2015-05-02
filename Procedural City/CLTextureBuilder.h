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
	Description: Generate textures for the 3D models
	using OpenCL. By using OpenCL the process of generating
	the textures is faster since it calculates each
	pixel of the texture in parallel on the GPU.
*/

#ifndef CL_TEXTURE_BUILDER_H
#define CL_TEXTURE_BUILDER_H

#include <iostream>
#include <irrlicht.h>
#include "Resources.h"

class CLTextureBuilder
{
private:
	unsigned char* _pixels;	//Texture pixels in A8R8G8B8 ECF format
	
	int _width, _height;
	irr::video::ITexture* _texture;
	
public:
	CLTextureBuilder();
	~CLTextureBuilder();

	//Will return true if it runs successfully.
	//Otherwise it will return false.
	bool run(int texWidth, int texHeight, std::string clFile);

	irr::video::ITexture* getTexture(irr::video::IVideoDriver* driver, std::string textureName);
};

#endif