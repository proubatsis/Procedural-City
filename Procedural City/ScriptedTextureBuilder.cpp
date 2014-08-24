#include "ScriptedTextureBuilder.h"

//Lua
irr::video::IImage* image;
irr::video::IVideoDriver* lDriver;

int l_createImage(lua_State* L)
{
	int width = lua_tointeger(L, 1);
	int height = lua_tointeger(L, 2);

	image = lDriver->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2du(width, height));

	return 0;
}

int l_setPixel(lua_State* L)
{
	int x = lua_tointeger(L, 1);
	int y = lua_tointeger(L, 2);

	float r = (float)lua_tonumber(L, 3);
	float g = (float)lua_tonumber(L, 4);
	float b = (float)lua_tonumber(L, 5);

	irr::video::SColor color(255, (int)(r * 255), (int)(g * 255), (int)(b * 255));
	image->setPixel(x, y, color);

	return 0;
}

//Class
ScriptedTextureBuilder::ScriptedTextureBuilder(std::string scriptName, std::string textureName)
{
	_script.load(scriptName);
	_script.registerFunction("createImage", l_createImage);
	_script.registerFunction("setPixel", l_setPixel);

	_textureName = irr::io::path(textureName.c_str());
	_texture = 0;
}

void ScriptedTextureBuilder::build(irr::video::IVideoDriver* driver)
{
	image = 0;
	lDriver = driver;

	_script.run();

	_texture = driver->addTexture(_textureName, image);
	image->drop();
	image = 0;
	lDriver = 0;
}

irr::io::path ScriptedTextureBuilder::getIOPath()
{
	return _textureName;
}

irr::video::ITexture* ScriptedTextureBuilder::getTexture()
{
	return _texture;
}