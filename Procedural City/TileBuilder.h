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
	static ScriptedNodeBuilder _houseBuilders[1];
	static ScriptedNodeBuilder _skyScraperBuilders[1];
	static ScriptedNodeBuilder _apartmentBuilders[1];

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