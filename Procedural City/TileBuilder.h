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
	Description: Builds a tile to be rendered in the
	city. A tile is built of various models generated
	via lua.
*/

#ifndef TILE_BUILDER_H
#define TILE_BUILDER_H

#include <irrlicht.h>
#include <vector>
#include "ScriptedNodeBuilder.h"
#include "IDRequester.h"
#include "Random.h"
#include "CustomNode.h"

class TileBuilder
{
private:
	const int TILE_SIZE;

	//Flat tile
	static ScriptedNodeBuilder _flatBuilder;

	//Buildings
	static std::vector<ScriptedNodeBuilder> _houseBuilders;
	static std::vector<ScriptedNodeBuilder> _skyScraperBuilders;
	static std::vector<ScriptedNodeBuilder> _apartmentBuilders;

	//Plants
	static ScriptedNodeBuilder _grass;

	//Roads
	static ScriptedNodeBuilder _twoLaneRoadBuilder;
	static ScriptedNodeBuilder _sixLaneRoadBuilder;
	static ScriptedNodeBuilder _sixLaneCornerBuilder;

	//T-Intersections
	static ScriptedNodeBuilder _twoToSixTRoadBuilder;
	static ScriptedNodeBuilder _sixToTwoTRoadBuilder;
	static ScriptedNodeBuilder _sixToSixTRoadBuilder;

	//4-Way Intersection
	static ScriptedNodeBuilder _sixLaneIntersection;

	IDPool _idPool;
	irr::scene::ISceneNode* _tileSceneNode;
	irr::scene::ISceneManager* _sceneManager;

public:
	//Load the scripts
	static void initialize();

	TileBuilder(irr::scene::ISceneManager* sceneManager);

	//Flat
	void addFlat(irr::core::vector3df position, float angle);

	//Buildings
	void addHouse(irr::core::vector3df position, float angle);
	void addSkyScraper(irr::core::vector3df position, float angle);
	void addApartment(irr::core::vector3df position, float angle);

	//Plants
	void addGrass(irr::core::vector3df position, float angle);

	//Roads
	void addTwoLaneRoad(irr::core::vector3df position, float angle);
	void addSixLaneRoad(irr::core::vector3df position, float angle);
	void addSixLaneCornerRoad(irr::core::vector3df position, float angle);

	//T-Intersections
	void addTwoToSixTRoad(irr::core::vector3df position, float angle);
	void addSixToTwoTRoad(irr::core::vector3df position, float angle);
	void addSixToSixTRoad(irr::core::vector3df position, float angle);

	//4-Way Intersections
	void addSixLaneIntersection(irr::core::vector3df position, float angle);

	irr::scene::ISceneNode* getNode();
};

#endif