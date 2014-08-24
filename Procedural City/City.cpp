#include "City.h"
#include "PopulationMap.h"
#include <functional>

using namespace irr;

City::City(scene::ISceneManager* sceneManager)
{
	_citySceneNode = sceneManager->addEmptySceneNode(sceneManager->getRootSceneNode(), IDRequester::request());

	//Initialize city with no roads
	for(int x = 0; x < CITY_X; x++)
		for(int y = 0; y < CITY_Y; y++)
			_tiles[x][y] = EMPTY;

	//Surrond the edges of the city with roads
	for(int x = 0; x < CITY_X; x++)
	{
		if(x == 0 || x == CITY_X - 1)
		{
			for(int y = 0; y < CITY_Y; y++)
				_tiles[x][y] = ROAD_SIX_LANE;
		}else
		{
			_tiles[x][0] = ROAD_SIX_LANE;
			_tiles[x][CITY_Y-1] = ROAD_SIX_LANE;
		}
	}

	std::vector<std::vector<float> > populationMap = Procedural::Map::generatePopulationMap(CITY_X, CITY_Y);

	generateRoads(0, 0, CITY_X-1, CITY_Y-1, true, 0, 15);

	createRoadGraphics(sceneManager);

	for(int x = 0; x < CITY_X; x++)
	{
		for(int y = 0; y < CITY_Y; y++)
		{
			if(_tiles[x][y] == EMPTY)
			{
				float p = populationMap[y][x];
				float r = Random::nextFloat();
				if(p > 0.06f)
				{
					_tiles[x][y] = SKYSCRAPER;
				}else if(p > 0.03)
				{
					_tiles[x][y] = APARTMENT;
				}else if(p > 0.0)
				{
					if(r > 0.1)
					{
						_tiles[x][y] = HOUSES;
					}else
					{
						_tiles[x][y] = APARTMENT;
					}
				}else if(p > -0.02)
				{
					_tiles[x][y] = HOUSES;
				}else
				{
					_tiles[x][y] = PARK;
				}
			}
		}
	}

	createTileGraphics(sceneManager);

	//_citySceneNode->setScale(core::vector3df(10,10,10));
}

//Recursively divide the grid to generate streets
void City::generateRoads(int ix, int iy, int ix2, int iy2, bool vertical, int count, const int& maxCount)
{
	if(count >= maxCount)
		return;

	int type = ROAD_SIX_LANE;

	if(vertical)
	{
		if((ix2 - ix) + 1 < 5)	return;	//Too little space
		int r = Random::nextInt(ix + 2, ix2 - 2);

		if(iy2 - iy < 3 && Random::nextFloat() > 0.65f)
			type = ROAD_TWO_LANE;

		insertTiles(r, iy, vertical, type);
		generateRoads(ix, iy, r - 1, iy2, !vertical, count + 1, maxCount);
		generateRoads(r, iy, ix2, iy2, !vertical, count + 1, maxCount);
	}else
	{
		if((iy2 - iy) + 1 < 5) return;	//Too little space
		int r = Random::nextInt(iy + 2, iy2 - 2);

		if(ix2 - ix < 3 && Random::nextFloat() > 0.65f)
			type = ROAD_TWO_LANE;

		insertTiles(ix, r, vertical, type);
		generateRoads(ix, iy, ix2, r - 1, !vertical, count + 1, maxCount);
		generateRoads(ix, r, ix2, iy2, !vertical, count + 1, maxCount);
	}
}

void City::insertTiles(int ix, int iy, bool vertical, int type)
{
	if(vertical)
	{
		for(int y = iy + 1; _tiles[ix][y] == EMPTY; y++)
		{
			_tiles[ix][y] = type;
		}
	}else
	{
		for(int x = ix + 1; _tiles[x][iy] == EMPTY; x++)
		{
			_tiles[x][iy] = type;
		}
	}
}

void City::createRoadGraphics(scene::ISceneManager* sceneManager)
{
	for(int x = 0; x < CITY_X; x++)
	{
		for(int y = 0; y < CITY_Y; y++)
		{

			std::function<bool(int,int)> isRoad = [this] (int x, int y) -> bool {return checkTile(x,y) == ROAD_SIX_LANE || checkTile(x,y) == ROAD_TWO_LANE;};
			//Check for four way intersection
			if(isRoad(x,y) && isRoad(x+1,y) && isRoad(x-1,y) && isRoad(x,y+1) && isRoad(x,y-1))
			{
				addTile(Procedural::Tile::generateSixLaneIntersection(sceneManager), core::vector3di(x,y,0));
			}
			//Handle six lane roads (Including Six to Two Lane T-Intersections)
			else if(_tiles[x][y] == ROAD_SIX_LANE)
			{

				if(checkTile(x-1,y) == ROAD_SIX_LANE && checkTile(x+1,y) == ROAD_SIX_LANE)
				{

					if(checkTile(x,y+1) == ROAD_SIX_LANE)
					{
						//T-Intersection Open Down
						addTile(Procedural::Tile::generateSixToSixT(sceneManager), core::vector3di(x, y, 270));
					}else if(checkTile(x,y-1) == ROAD_SIX_LANE)
					{
						//T-Intersection Open Up
						addTile(Procedural::Tile::generateSixToSixT(sceneManager), core::vector3di(x, y, 90));
					}else if(checkTile(x,y+1) == ROAD_TWO_LANE)
					{
						//T-Intersection Open Down (To Two Lane)
						addTile(Procedural::Tile::generateSixToTwoT(sceneManager), core::vector3di(x, y, 270));
					}else if(checkTile(x,y-1) == ROAD_TWO_LANE)
					{
						//T-Intersection Open Up (To Two Lane)
						addTile(Procedural::Tile::generateSixToTwoT(sceneManager), core::vector3di(x, y, 90));
					}else
					{
						//Add normal road
						addTile(Procedural::Tile::generateSixLaneRoad(sceneManager), core::vector3di(x, y, 90));
					}

				}else if(checkTile(x,y+1)  == ROAD_SIX_LANE && checkTile(x,y-1) == ROAD_SIX_LANE)
				{

					if(checkTile(x+1,y) == ROAD_SIX_LANE)
					{
						//T-Intersection Open Right
						addTile(Procedural::Tile::generateSixToSixT(sceneManager), core::vector3di(x, y, 0));
					}else if(checkTile(x-1,y) == ROAD_SIX_LANE)
					{
						//T-Intersection Open Left
						addTile(Procedural::Tile::generateSixToSixT(sceneManager), core::vector3di(x, y, 180));
					}else if(checkTile(x+1,y) == ROAD_TWO_LANE)
					{
						//T-Intersection Open Right (To Two Lane)
						addTile(Procedural::Tile::generateSixToTwoT(sceneManager), core::vector3di(x, y, 0));
					}else if(checkTile(x-1,y) == ROAD_TWO_LANE)
					{
						//T-Intersection Open Left (To Two Lane)
						addTile(Procedural::Tile::generateSixToTwoT(sceneManager), core::vector3di(x, y, 180));
					}else
					{
						//Add normal road
						addTile(Procedural::Tile::generateSixLaneRoad(sceneManager), core::vector3di(x, y, 0));
					}

				}else if((checkTile(x-1,y) == ROAD_TWO_LANE || checkTile(x-1,y) == ROAD_SIX_LANE) && (checkTile(x+1,y) == ROAD_TWO_LANE || checkTile(x+1,y) == ROAD_SIX_LANE))
				{

					//Add normal road
					addTile(Procedural::Tile::generateSixLaneRoad(sceneManager), core::vector3di(x, y, 90));

				}else if((checkTile(x,y+1)  == ROAD_TWO_LANE || checkTile(x,y+1)  == ROAD_SIX_LANE) && (checkTile(x,y-1) == ROAD_TWO_LANE || checkTile(x,y-1) == ROAD_SIX_LANE))
				{

					//Add normal road
					addTile(Procedural::Tile::generateSixLaneRoad(sceneManager), core::vector3di(x, y, 0));

				}else if(checkTile(x-1,y) == ROAD_SIX_LANE && checkTile(x+1,y) == EMPTY)
				{

					if(checkTile(x,y+1))
					{
						//Add corner
						addTile(Procedural::Tile::generateSixLaneCorner(sceneManager), core::vector3di(x, y, 180));
					}else
					{
						//Add corner
						addTile(Procedural::Tile::generateSixLaneCorner(sceneManager), core::vector3di(x, y, 90));
					}

				}else if(checkTile(x+1,y) == ROAD_SIX_LANE && checkTile(x-1,y) == EMPTY)
				{
					
					if(checkTile(x,y+1))
					{
						//Add corner
						addTile(Procedural::Tile::generateSixLaneCorner(sceneManager), core::vector3di(x, y, 270));
					}else
					{
						//Add corner
						addTile(Procedural::Tile::generateSixLaneCorner(sceneManager), core::vector3di(x, y, 0));
					}

				}

			}
			//Handle two lane roads including two to six lane T-Intersections
			else if(_tiles[x][y] == ROAD_TWO_LANE)
			{

				if(checkTile(x-1,y) == ROAD_TWO_LANE && checkTile(x+1,y) == ROAD_TWO_LANE)
				{

					if(checkTile(x,y+1) == ROAD_TWO_LANE)
					{
						//T-Intersection Open Down
						addTile(Procedural::Tile::generateTwoToSixTAndHouses(sceneManager), core::vector3di(x, y, 270));
					}else if(checkTile(x,y-1) == ROAD_TWO_LANE)
					{
						//T-Intersection Open Up
						addTile(Procedural::Tile::generateTwoToSixTAndHouses(sceneManager), core::vector3di(x, y, 90));
					}else if(checkTile(x,y+1) == ROAD_SIX_LANE)
					{
						//T-Intersection Open Down (To Six Lane)
						addTile(Procedural::Tile::generateTwoToSixTAndHouses(sceneManager), core::vector3di(x, y, 270));
					}else if(checkTile(x,y-1) == ROAD_SIX_LANE)
					{
						//T-Intersection Open Up (To Six Lane)
						addTile(Procedural::Tile::generateTwoToSixTAndHouses(sceneManager), core::vector3di(x, y, 90));
					}else
					{
						//Add normal road
						addTile(Procedural::Tile::generateTwoLaneAndHouses(sceneManager), core::vector3di(x, y, 90));
					}

				}
				else if(checkTile(x,y+1)  == ROAD_TWO_LANE && checkTile(x,y-1) == ROAD_TWO_LANE)
				{

					if(checkTile(x+1,y) == ROAD_TWO_LANE)
					{
						//T-Intersection Open Right
						addTile(Procedural::Tile::generateTwoToSixTAndHouses(sceneManager), core::vector3di(x, y, 0));
					}else if(checkTile(x-1,y) == ROAD_TWO_LANE)
					{
						//T-Intersection Open Left
						addTile(Procedural::Tile::generateTwoToSixTAndHouses(sceneManager), core::vector3di(x, y, 180));
					}else if(checkTile(x+1,y) == ROAD_SIX_LANE)
					{
						//T-Intersection Open Right (To Six Lane)
						addTile(Procedural::Tile::generateTwoToSixTAndHouses(sceneManager), core::vector3di(x, y, 0));
					}else if(checkTile(x-1,y) == ROAD_SIX_LANE)
					{
						//T-Intersection Open Left (To Six Lane)
						addTile(Procedural::Tile::generateTwoToSixTAndHouses(sceneManager), core::vector3di(x, y, 180));
					}else
					{
						//Add normal road
						addTile(Procedural::Tile::generateTwoLaneAndHouses(sceneManager), core::vector3di(x, y, 0));
					}

				}else if((checkTile(x-1,y) == ROAD_TWO_LANE || checkTile(x-1,y) == ROAD_SIX_LANE) && (checkTile(x+1,y) == ROAD_TWO_LANE || checkTile(x+1,y) == ROAD_SIX_LANE))
				{

					//Add normal road
					addTile(Procedural::Tile::generateTwoLaneAndHouses(sceneManager), core::vector3di(x, y, 90));

				}else if((checkTile(x,y+1)  == ROAD_TWO_LANE || checkTile(x,y+1)  == ROAD_SIX_LANE) && (checkTile(x,y-1) == ROAD_TWO_LANE || checkTile(x,y-1) == ROAD_SIX_LANE))
				{

					//Add normal road
					addTile(Procedural::Tile::generateTwoLaneAndHouses(sceneManager), core::vector3di(x, y, 0));

				}

			}

		}
	}
}

void City::createTileGraphics(irr::scene::ISceneManager* sceneManager)
{
	for(int x = 0; x < CITY_X; x++)
	{
		for(int y = 0; y < CITY_Y; y++)
		{
			switch(_tiles[x][y])
			{
			case SKYSCRAPER:
				addTile(Procedural::Tile::generateSkyscraper(sceneManager), core::vector3di(x,y,0));
				break;
			case APARTMENT:
				addTile(Procedural::Tile::generateApartment(sceneManager), core::vector3di(x,y,0));
				break;
			case HOUSES:
				addTile(Procedural::Tile::generateHouses(sceneManager), core::vector3di(x,y,0));
				break;
			case PARK:
				addTile(Procedural::Tile::generatePark(sceneManager), core::vector3di(x,y,0));
				break;
			}
		}
	}
}

int City::checkTile(int x, int y)
{
	if(x < 0 || x >= CITY_X || y < 0 || y >= CITY_Y)
		return EMPTY;
	return _tiles[x][y];
}

void City::addTile(scene::ISceneNode* node, core::vector3di positionRotation)
{
	const float TILE_SIZE = 32;
	core::vector3df position(positionRotation.X * TILE_SIZE, 0, positionRotation.Y * TILE_SIZE);
	core::vector3df rotation(0, positionRotation.Z, 0);

	node->setPosition(position);
	node->setRotation(rotation);

	_citySceneNode->addChild(node);
}