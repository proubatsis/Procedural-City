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
	Description: Provides functionality for lua
	to build 3D models for the city to use.
*/

#ifndef SCRIPTED_NODE_BUILDER_H
#define SCRIPTED_NODE_BUILDER_H

#include <irrlicht.h>
#include <vector>
#include "LuaScript.h"
#include "MeshBuilder.h"
#include "CustomNode.h"
#include "Shader.h"

class ScriptedNodeBuilder
{
public:
	ScriptedNodeBuilder();
	ScriptedNodeBuilder(std::string scriptFile);
	~ScriptedNodeBuilder();

	//Loads the script.
	void load(std::string scriptFile);

	//Build the node and return it
	CustomNode* build(irr::scene::ISceneManager* sceneManager, irr::scene::ISceneNode* parent, int id);

	struct LuaSceneGraphNode
	{
		int parentIndex;
		MeshBuilder builder;
		Shader* shader;
		irr::video::ITexture* texture;
		irr::core::vector3df position;
		irr::core::vector3df rotation;
	};

private:
	LuaScript _script;
	std::vector<LuaSceneGraphNode> _graphNodes;
	bool _isBuilt;
};

#endif