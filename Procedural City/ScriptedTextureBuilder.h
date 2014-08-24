#ifndef SCRIPTED_TEXTURE_BUILDER
#define SCRIPTED_TEXTURE_BUILDER

#include "procedural_city.h"
#include <irrlicht.h>
#include "LuaScript.h"

class ScriptedTextureBuilder
{
private:
	LuaScript _script;
	irr::io::path _textureName;
	irr::video::ITexture* _texture;

public:
	ScriptedTextureBuilder(std::string scriptName, std::string textureName);

	void build(irr::video::IVideoDriver* driver);

	irr::io::path getIOPath();
	irr::video::ITexture* getTexture();
};

#endif