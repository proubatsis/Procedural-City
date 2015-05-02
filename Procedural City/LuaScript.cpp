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