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