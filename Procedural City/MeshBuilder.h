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
	Description: Used to build a 3D model.
*/

#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include <irrlicht.h>
#include <vector>
#include "CustomNode.h"

class MeshBuilder
{
private:
	std::vector<irr::core::vector3df> _vertices;		//The vertices used to make up the mesh
	std::vector<irr::core::vector3df> _normals;			//The normal vectors for the mesh, these are used for lighting
	std::vector<irr::core::vector2df> _uvCoordinates;	//The UV coordinates for the mesh, these are used for texturing and shading
	std::vector<irr::u16> _indices;						//The indices define the triangles of the mesh
	irr::video::SColor _vertexColor;

public:
	MeshBuilder() : _vertexColor(irr::video::SColor(255,255,255,255)) {}

	//Set the color of the vertices
	void setVertexColor(irr::video::SColor color){ _vertexColor = color; }

	//Add a vertex position to the mesh
	void addVertex(float x, float y, float z);

	//Add a normal vector to the mesh
	void addNormal(float x, float y, float z);

	//Add a UV (Texture) coordinate to the mesh (Between 0 & 1)
	void addUV(float x, float y);

	//Add indices to create a triangle (CCW)
	void addTriangle(irr::u16 a, irr::u16 b, irr::u16 c);

	//Builds by creating the vertices for a custom
	//irrlicht scene node.
	std::vector<irr::video::S3DVertex> buildVertices();

	//Build bounding box used for culling by irrlicht
	irr::core::aabbox3df buildBox();

	//Get the indices to draw the triangles appropriately
	std::vector<irr::u16> getIndices();

	CustomNode* buildSceneNode(irr::scene::ISceneManager* sceneManager, irr::scene::ISceneNode* parent, int id);
};

#endif