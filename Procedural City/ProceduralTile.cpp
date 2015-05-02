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

#include "ProceduralTile.h"
#include "TileBuilder.h"

using namespace irr;

//Buildings
irr::scene::ISceneNode* Procedural::Tile::generateSkyscraper(irr::scene::ISceneManager* sceneManager)
{
	TileBuilder tb(sceneManager);
	tb.addSkyScraper(core::vector3df(0,0,0),0);
	return tb.getNode();
}

irr::scene::ISceneNode* Procedural::Tile::generateApartment(irr::scene::ISceneManager* sceneManager)
{
	TileBuilder tb(sceneManager);
	tb.addFlat(core::vector3df(0,0,0),0);
	tb.addApartment(core::vector3df(0,0,0),0);
	return tb.getNode();
}

irr::scene::ISceneNode* Procedural::Tile::generateHouses(irr::scene::ISceneManager* sceneManager)
{
	TileBuilder tb(sceneManager);
	tb.addGrass(core::vector3df(0,0,0), 0);

	//Place a group of houses on a single tile
	for(int z = -11; z <= 11; z += 11)
	{
		tb.addHouse(core::vector3df(11.0f,0.15f,(float)z), -90.0f);
		tb.addHouse(core::vector3df(-11.0f,0.15f,(float)z), 90.0f);
	}

	return tb.getNode();
}

//Outdoors
irr::scene::ISceneNode* Procedural::Tile::generatePark(irr::scene::ISceneManager* sceneManager)
{
	TileBuilder tb(sceneManager);
	tb.addGrass(core::vector3df(0,0,0), 0);
	return tb.getNode();
}

//Roads
scene::ISceneNode* Procedural::Tile::generateSixLaneRoad(scene::ISceneManager* sceneManager)
{
	TileBuilder tb(sceneManager);
	tb.addSixLaneRoad(core::vector3df(0,0,0),0);
	return tb.getNode();
}

irr::scene::ISceneNode* Procedural::Tile::generateSixToTwoT(irr::scene::ISceneManager* sceneManager)
{
	TileBuilder tb(sceneManager);
	tb.addSixToTwoTRoad(core::vector3df(0,0,0),0);
	return tb.getNode();
}

irr::scene::ISceneNode* Procedural::Tile::generateSixToSixT(irr::scene::ISceneManager* sceneManager)
{
	TileBuilder tb(sceneManager);
	tb.addSixToSixTRoad(core::vector3df(0,0,0),0);
	return tb.getNode();
}

irr::scene::ISceneNode* Procedural::Tile::generateSixLaneCorner(irr::scene::ISceneManager* sceneManager)
{
	TileBuilder tb(sceneManager);
	tb.addSixLaneCornerRoad(core::vector3df(0,0,0),0);
	return tb.getNode();
}

irr::scene::ISceneNode* Procedural::Tile::generateSixLaneIntersection(irr::scene::ISceneManager* sceneManager)
{
	TileBuilder tb(sceneManager);
	tb.addSixLaneIntersection(core::vector3df(0,0,0),0);
	return tb.getNode();
}

//Road combos
scene::ISceneNode* Procedural::Tile::generateTwoLaneAndHouses(scene::ISceneManager* sceneManager)
{
	TileBuilder tb(sceneManager);
	tb.addTwoLaneRoad(core::vector3df(0,0,0),0);

	//Place a group of houses on each side of the two lane road
	for(int z = -11; z <= 11; z += 11)
	{
		tb.addHouse(core::vector3df(11.0f,0.15f,(float)z), -90.0f);
		tb.addHouse(core::vector3df(-11.0f,0.15f,(float)z), 90.0f);
	}

	return tb.getNode();
}

scene::ISceneNode* Procedural::Tile::generateTwoToSixTAndHouses(scene::ISceneManager* sceneManager)
{
	TileBuilder tb(sceneManager);
	tb.addTwoToSixTRoad(core::vector3df(0,0,0),0);

	for(int z = -11; z <= 11; z += 11)
	{
		tb.addHouse(core::vector3df(-11.0f,0.15f,(float)z), 90.0f);
	}

	return tb.getNode();
}