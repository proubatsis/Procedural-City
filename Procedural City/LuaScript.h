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
	Description: Allow lua files to be run, and given access
	to C++ functions.
*/

#ifndef LUA_SCRIPT_H
#define LUA_SCRIPT_H

#include <iostream>
#include <lua.hpp>
#include "Resources.h"

class LuaScript
{
private:
	lua_State* _L;
	bool _hasBeenRun;

public:
	LuaScript();
	LuaScript(std::string scriptFile);
	~LuaScript();

	void load(std::string scriptFile);
	void run();

	void registerFunction(std::string luaFunction, int (*f)(lua_State*));
};

#endif