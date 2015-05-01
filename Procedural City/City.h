/*
	Created by Panagiotis Roubatsis
	Description: The class that handles generating the city,
	including the roads and positioning of the various tiles
	that make up the city.
*/

#ifndef CITY_H
#define CITY_H

#define CITY_X 32
#define CITY_Y 32

#include <irrlicht.h>
#include "ProceduralTile.h"
#include "Random.h"
#include "IDRequester.h"

class City
{
private:
	enum TileType
	{
		EMPTY,
		ROAD_SIX_LANE,
		ROAD_TWO_LANE,
		SKYSCRAPER,
		APARTMENT,
		HOUSES,
		PARK
	};
	
	int _tiles[CITY_X][CITY_Y];	//Stores TileType values for what should be on any given tile

	irr::scene::ISceneNode* _citySceneNode;

	//Generates roads recursively
	void generateRoads(int ix, int iy, int ix2, int iy2, bool vertical, int count, const int& maxCount);
	
	//Insert a tile until it hits another tile, if vertical is false the tile will be horizontal
	void insertTiles(int ix, int iy, bool vertical, int type);

	//Create and add road graphics from the array
	void createRoadGraphics(irr::scene::ISceneManager* sceneManager);

	//Create and add graphics for all non-road tiles
	void createTileGraphics(irr::scene::ISceneManager* sceneManager);

	//Makes sure the given coordinate is not out of bounds before
	//returning the value (EMPTY if out of bounds otherwise returns value of the tile).
	int checkTile(int x, int y);
public:
	City(irr::scene::ISceneManager* sceneManager);

	//Add a tile to the city. Adjust it's position (X,Y) and it's rotation
	//(Z). The position will be multiplied by 32 to fit a tile.
	void addTile(irr::scene::ISceneNode* tileNode, irr::core::vector3di positionRotation);
};

#endif
