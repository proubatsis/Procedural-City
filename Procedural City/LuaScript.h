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