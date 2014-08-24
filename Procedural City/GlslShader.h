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