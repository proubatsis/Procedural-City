#include "LuaScript.h"

LuaScript::LuaScript()
	: _hasBeenRun(false)
{
	_L = 0;
}

LuaScript::LuaScript(std::string scriptName)
	: _hasBeenRun(false)
{
	load(scriptName);
}

LuaScript::~LuaScript()
{
	if(_L != 0)
		lua_close(_L);
}

void LuaScript::load(std::string scriptFile)
{
	std::string fileLoc = "lua/";
	fileLoc += scriptFile;
	fileLoc += ".lua";

	_L = luaL_newstate();
	luaL_loadstring(_L, Resources::getTextFileAsString(fileLoc).c_str());
	luaL_openlibs(_L);
}

void LuaScript::run()
{
	if(_hasBeenRun)
		return;

	lua_call(_L, 0, 0);
	_hasBeenRun = true;
}

void LuaScript::registerFunction(std::string luaFunction, int (*f)(lua_State*))
{
	lua_register(_L, luaFunction.c_str(), f);
}