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