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
	for(int z = -11; z <= 11; z += 11)
	{
		tb.addHouse(core::vector3df(11,0.15f,z), -90);
		tb.addHouse(core::vector3df(-11,0.15f,z), 90);
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
	for(int z = -11; z <= 11; z += 11)
	{
		tb.addHouse(core::vector3df(11,0.15f,z), -90);
		tb.addHouse(core::vector3df(-11,0.15f,z), 90);
	}

	return tb.getNode();
}

scene::ISceneNode* Procedural::Tile::generateTwoToSixTAndHouses(scene::ISceneManager* sceneManager)
{
	TileBuilder tb(sceneManager);
	tb.addTwoToSixTRoad(core::vector3df(0,0,0),0);
	for(int z = -11; z <= 11; z += 11)
	{
		//tb.addHouse(core::vector3df(11,0.15f,z), -90);
		tb.addHouse(core::vector3df(-11,0.15f,z), 90);
	}

	return tb.getNode();
}