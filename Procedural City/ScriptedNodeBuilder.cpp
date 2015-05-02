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

#include "ScriptedNodeBuilder.h"
#include "GlslShader.h"

ScriptedNodeBuilder::LuaSceneGraphNode createEmptyNode()
{
	ScriptedNodeBuilder::LuaSceneGraphNode node;
	node.parentIndex = 0;
	node.texture = 0;
	node.position = irr::core::vector3df(0, 0, 0);
	node.shader = 0;
	return node;
}

//LUA section
int currentIndex;
std::vector<ScriptedNodeBuilder::LuaSceneGraphNode>* graphNodes;
irr::scene::ISceneManager* snbSceneManager;

int l_createNode(lua_State* L)
{
	ScriptedNodeBuilder::LuaSceneGraphNode node = createEmptyNode();

	node.parentIndex = currentIndex;

	graphNodes->push_back(node);
	currentIndex = graphNodes->size() - 1;

	return 0;
}

int l_switchToNode(lua_State* L)
{
	currentIndex = lua_tointeger(L, 1);
	return 0;
}

int l_addVertex(lua_State* L)
{
	float x = (float)lua_tonumber(L, 1);
	float y = (float)lua_tonumber(L, 2);
	float z = (float)lua_tonumber(L, 3);

	graphNodes->at(currentIndex).builder.addVertex(x, y, z);

	return 0;
}

int l_addNormal(lua_State* L)
{
	float x = (float)lua_tonumber(L, 1);
	float y = (float)lua_tonumber(L, 2);
	float z = (float)lua_tonumber(L, 3);

	graphNodes->at(currentIndex).builder.addNormal(x, y, z);

	return 0;
}

int l_addUV(lua_State* L)
{
	float x = (float)lua_tonumber(L, 1);
	float y = (float)lua_tonumber(L, 2);

	graphNodes->at(currentIndex).builder.addUV(x, y);

	return 0;
}

int l_addTriangle(lua_State* L)
{
	int a = lua_tointeger(L, 1);
	int b = lua_tointeger(L, 2);
	int c = lua_tointeger(L, 3);

	graphNodes->at(currentIndex).builder.addTriangle(a, b, c);

	return 0;
}

int l_setPosition(lua_State* L)
{
	float x = (float)lua_tonumber(L, 1);
	float y = (float)lua_tonumber(L, 2);
	float z = (float)lua_tonumber(L, 3);

	graphNodes->at(currentIndex).position = irr::core::vector3df(x, y, z);

	return 0;
}

int l_setRotation(lua_State* L)
{
	float x = (float)lua_tonumber(L, 1);
	float y = (float)lua_tonumber(L, 2);
	float z = (float)lua_tonumber(L, 3);

	graphNodes->at(currentIndex).rotation = irr::core::vector3df(x, y, z);

	return 0;
}

int l_setVertexColor(lua_State* L)
{
	int r = lua_tointeger(L, 1);
	int g = lua_tointeger(L, 2);
	int b = lua_tointeger(L, 3);

	graphNodes->at(currentIndex).builder.setVertexColor(irr::video::SColor(255, r, g, b));

	return 0;
}

int l_setTexture(lua_State* L)
{
	std::string texName = lua_tostring(L, 1);
	graphNodes->at(currentIndex).texture = snbSceneManager->getVideoDriver()->getTexture(irr::io::path(texName.c_str()));

	return 0;
}

int l_setShader(lua_State* L)
{
	if(graphNodes->at(currentIndex).shader != 0)
		return 0;

	graphNodes->at(currentIndex).shader = new GlslShader(lua_tostring(L, 1), snbSceneManager->getVideoDriver()->getGPUProgrammingServices(), Shader::TYPE_VERT | Shader::TYPE_PIXEL);
	return 0;
}

int l_setVertexShader(lua_State* L)
{
	if(graphNodes->at(currentIndex).shader != 0)
		return 0;

	graphNodes->at(currentIndex).shader = new GlslShader(lua_tostring(L, 1), snbSceneManager->getVideoDriver()->getGPUProgrammingServices(), Shader::TYPE_VERT);
	return 0;
}

int l_setPixelShader(lua_State* L)
{
	if(graphNodes->at(currentIndex).shader != 0)
		return 0;

	graphNodes->at(currentIndex).shader = new GlslShader(lua_tostring(L, 1), snbSceneManager->getVideoDriver()->getGPUProgrammingServices(), Shader::TYPE_PIXEL);
	return 0;
}

//Calculation lua functions
int l_rotateAroundX(lua_State* L)
{
	float x = (float)lua_tonumber(L, 1);
	float y = (float)lua_tonumber(L, 2);
	float z = (float)lua_tonumber(L, 3);
	float angle = (float)lua_tonumber(L, 4);

	irr::core::vector3df vec(x,y,z);
	vec.rotateYZBy(angle);

	lua_pushnumber(L, vec.X);
	lua_pushnumber(L, vec.Y);
	lua_pushnumber(L, vec.Z);

	return 3;
}
int l_rotateAroundY(lua_State* L)
{
	float x = (float)lua_tonumber(L, 1);
	float y = (float)lua_tonumber(L, 2);
	float z = (float)lua_tonumber(L, 3);
	float angle = (float)lua_tonumber(L, 4);

	irr::core::vector3df vec(x,y,z);
	vec.rotateXZBy(angle);

	lua_pushnumber(L, vec.X);
	lua_pushnumber(L, vec.Y);
	lua_pushnumber(L, vec.Z);

	return 3;
}
int l_rotateAroundZ(lua_State* L)
{
	float x = (float)lua_tonumber(L, 1);
	float y = (float)lua_tonumber(L, 2);
	float z = (float)lua_tonumber(L, 3);
	float angle = (float)lua_tonumber(L, 4);

	irr::core::vector3df vec(x,y,z);
	vec.rotateXYBy(angle);

	lua_pushnumber(L, vec.X);
	lua_pushnumber(L, vec.Y);
	lua_pushnumber(L, vec.Z);

	return 3;
}

//Class section
ScriptedNodeBuilder::ScriptedNodeBuilder()
{
	_isBuilt = false;
}

ScriptedNodeBuilder::ScriptedNodeBuilder(std::string scriptFile)
{
	_isBuilt = false;
	load(scriptFile);
}

ScriptedNodeBuilder::~ScriptedNodeBuilder()
{
	//Free the memory of the shaders
	for(std::vector<LuaSceneGraphNode>::iterator it = _graphNodes.begin(); it != _graphNodes.end(); it++)
	{
		if((*it).shader != 0)
			delete (*it).shader;
	}
}

void ScriptedNodeBuilder::load(std::string scriptFile)
{
	_script.load(scriptFile);

	_script.registerFunction("addVertex", l_addVertex);
	_script.registerFunction("addNormal", l_addNormal);
	_script.registerFunction("addUV", l_addUV);
	_script.registerFunction("addTriangle", l_addTriangle);

	_script.registerFunction("createNode", l_createNode);
	_script.registerFunction("switchToNode", l_switchToNode);

	_script.registerFunction("setPosition", l_setPosition);
	_script.registerFunction("setRotation", l_setRotation);
	_script.registerFunction("setVertexColor", l_setVertexColor);
	_script.registerFunction("setTexture", l_setTexture);

	_script.registerFunction("setShader", l_setShader);
	_script.registerFunction("setVertexShader", l_setVertexShader);
	_script.registerFunction("setPixelShader", l_setPixelShader);

	//Calculation functions
	_script.registerFunction("rotateAroundX", l_rotateAroundX);
	_script.registerFunction("rotateAroundY", l_rotateAroundY);
	_script.registerFunction("rotateAroundZ", l_rotateAroundZ);
}

CustomNode* ScriptedNodeBuilder::build(irr::scene::ISceneManager* sceneManager, irr::scene::ISceneNode* parent, int id)
{
	currentIndex = -1;
	graphNodes = &_graphNodes;
	snbSceneManager = sceneManager;

	//Only run the script if the object has not
	//already been built. (For using a ScriptedNodeBuilder instance multiple times)
	if(!_isBuilt)
		_script.run();

	std::vector<CustomNode*> cNodes;

	for(size_t i = 0; i < _graphNodes.size(); i++)
	{
		LuaSceneGraphNode node = _graphNodes[i];
		CustomNode* cNode = node.builder.buildSceneNode(sceneManager, parent, id);
		cNode->setPosition(node.position);
		cNode->setRotation(node.rotation);

		if(node.shader != 0)
		{
			//Apply shader
			node.shader->apply(cNode);
		}

		if(node.texture != 0)
		{
			irr::video::SMaterial mat;
			mat.Lighting = true;
			mat.Wireframe = false;
			mat.setTexture(0, node.texture);
			mat.setFlag(irr::video::EMF_ANISOTROPIC_FILTER, true);	//Makes textures look much better
			cNode->setMaterial(mat);
		}

		if(node.parentIndex != -1)
			cNode->setParent(cNodes[node.parentIndex]);

		cNodes.push_back(cNode);
	}
	
	if(cNodes.size() > 1)
	{
		for(size_t i = 1; i < cNodes.size(); i++)
		{
			cNodes[i]->drop();
		}
	}

	_isBuilt = true;
	return cNodes[0];
}
