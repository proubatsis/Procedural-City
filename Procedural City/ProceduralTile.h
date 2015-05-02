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
	Description: Generates tiles for use by the city class.
*/

#ifndef PROCEDURAL_TILE_H
#define PROCEDURAL_TILE_H

#include <irrlicht.h>

namespace Procedural
{
	namespace Tile
	{
		//Buildings
		irr::scene::ISceneNode* generateSkyscraper(irr::scene::ISceneManager* sceneManager);
		irr::scene::ISceneNode* generateApartment(irr::scene::ISceneManager* sceneManager);
		irr::scene::ISceneNode* generateHouses(irr::scene::ISceneManager* sceneManager);

		//Outdoors
		irr::scene::ISceneNode* generatePark(irr::scene::ISceneManager* sceneManager);

		//Roads
		irr::scene::ISceneNode* generateSixLaneRoad(irr::scene::ISceneManager* sceneManager);
		irr::scene::ISceneNode* generateSixToTwoT(irr::scene::ISceneManager* sceneManager);
		irr::scene::ISceneNode* generateSixToSixT(irr::scene::ISceneManager* sceneManager);
		irr::scene::ISceneNode* generateSixLaneCorner(irr::scene::ISceneManager* sceneManager);
		irr::scene::ISceneNode* generateSixLaneIntersection(irr::scene::ISceneManager* sceneManager);

		//Road Combos
		irr::scene::ISceneNode* generateTwoLaneAndHouses(irr::scene::ISceneManager* sceneManager);
		irr::scene::ISceneNode* generateTwoToSixTAndHouses(irr::scene::ISceneManager* sceneManager);
		
	};
};

#endif