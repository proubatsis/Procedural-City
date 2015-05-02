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

#include "MeshBuilder.h"

void MeshBuilder::addVertex(float x, float y, float z)
{
	_vertices.push_back(irr::core::vector3df(x, y, z));
}

void MeshBuilder::addNormal(float x, float y, float z)
{
	_normals.push_back(irr::core::vector3df(x, y, z));
}

void MeshBuilder::addUV(float x, float y)
{
	_uvCoordinates.push_back(irr::core::vector2df(x, y));
}

void MeshBuilder::addTriangle(irr::u16 a, irr::u16 b, irr::u16 c)
{
	_indices.push_back(a);
	_indices.push_back(b);
	_indices.push_back(c);
}

std::vector<irr::video::S3DVertex> MeshBuilder::buildVertices()
{
	std::vector<irr::video::S3DVertex> build;

	for(size_t i = 0; i < _vertices.size(); i++)
	{
		irr::core::vector3df vertex = _vertices[i];
		irr::core::vector3df normal = _normals[i];
		irr::core::vector2df uv = _uvCoordinates[i];

		build.push_back(irr::video::S3DVertex(vertex, normal, _vertexColor, uv));
	}

	return build;
}

irr::core::aabbox3df MeshBuilder::buildBox()
{
	irr::core::aabbox3df box;

	box.reset(_vertices[0]);
	for(size_t i = 1; i < _vertices.size(); i++)
	{
		box.addInternalPoint(_vertices[i]);
	}

	return box;
}

std::vector<irr::u16> MeshBuilder::getIndices()
{
	return _indices;
}

CustomNode* MeshBuilder::buildSceneNode(irr::scene::ISceneManager* sceneManager, irr::scene::ISceneNode* parent, int id)
{
	return new CustomNode(buildVertices(), getIndices(), buildBox(), sceneManager, parent, id);
}