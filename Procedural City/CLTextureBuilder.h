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