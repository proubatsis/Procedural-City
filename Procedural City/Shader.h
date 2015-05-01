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