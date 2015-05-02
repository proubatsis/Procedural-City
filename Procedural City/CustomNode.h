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
	Description: A custom irrlicht node.
*/

#ifndef CUSTOM_NODE
#define CUSTOM_NODE

#include <irrlicht.h>
#include <vector>

class CustomNode : public irr::scene::ISceneNode
{
private:
	std::vector<irr::video::S3DVertex> _vertices;
	std::vector<irr::u16> _indices;
	irr::core::aabbox3df _box;
	irr::video::SMaterial _material;
	int _polyCount;

public:
	CustomNode(std::vector<irr::video::S3DVertex> vertices, std::vector<irr::u16> indices, irr::core::aabbox3df box, irr::scene::ISceneManager* sceneManager, ISceneNode* parent, int id);
	CustomNode(CustomNode* node, irr::scene::ISceneManager* sceneManager, ISceneNode* parent, int id);

	void setMaterial(irr::video::SMaterial material);

	virtual void OnRegisterSceneNode();
	virtual void render();

	virtual const irr::core::aabbox3df& getBoundingBox() const { return _box; }
	virtual irr::u32 getMaterialCount() const { return 1; }
	virtual irr::video::SMaterial& getMaterial(irr::u32 i) { return _material; }
};

#endif