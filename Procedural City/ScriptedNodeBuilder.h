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