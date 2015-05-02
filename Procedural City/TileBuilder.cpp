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

#include "TileBuilder.h"

ScriptedNodeBuilder TileBuilder::_flatBuilder;

std::vector<ScriptedNodeBuilder> TileBuilder::_houseBuilders(3);
std::vector<ScriptedNodeBuilder> TileBuilder::_skyScraperBuilders(2);
std::vector<ScriptedNodeBuilder> TileBuilder::_apartmentBuilders(3);

ScriptedNodeBuilder TileBuilder::_grass;

ScriptedNodeBuilder TileBuilder::_twoLaneRoadBuilder;
ScriptedNodeBuilder TileBuilder::_sixLaneRoadBuilder;
ScriptedNodeBuilder TileBuilder::_sixLaneCornerBuilder;

ScriptedNodeBuilder TileBuilder::_twoToSixTRoadBuilder;
ScriptedNodeBuilder TileBuilder::_sixToTwoTRoadBuilder;
ScriptedNodeBuilder TileBuilder::_sixToSixTRoadBuilder;

ScriptedNodeBuilder TileBuilder::_sixLaneIntersection;

void TileBuilder::initialize()
{
	//Load the various lua scripts required to build tiles
	_flatBuilder.load("models/flat_tile");

	_houseBuilders[0].load("models/houses/red_house");
	_houseBuilders[1].load("models/houses/white_house");
	_houseBuilders[2].load("models/houses/brown_house");

	_skyScraperBuilders[0].load("models/skyscrapers/skyscraper");
	_skyScraperBuilders[1].load("models/skyscrapers/skyscraper2");

	_apartmentBuilders[0].load("models/apartment/red");
	_apartmentBuilders[1].load("models/apartment/white");
	_apartmentBuilders[2].load("models/apartment/brown");

	_grass.load("models/plants/grass");

	_twoLaneRoadBuilder.load("models/road/standard_two_lane");
	_sixLaneRoadBuilder.load("models/road/standard_six_lane");
	_sixLaneCornerBuilder.load("models/road/corner_six_lane");

	_twoToSixTRoadBuilder.load("models/road/2_6_T_intersection");
	_sixToTwoTRoadBuilder.load("models/road/6_2_T_intersection");
	_sixToSixTRoadBuilder.load("models/road/6_6_T_intersection");

	_sixLaneIntersection.load("models/road/6_lane_intersection");
}

TileBuilder::TileBuilder(irr::scene::ISceneManager* sceneManager)
	: _sceneManager(sceneManager), TILE_SIZE(32)
{
	_idPool = IDRequester::requestPool(4096);
	_tileSceneNode = sceneManager->addEmptySceneNode(sceneManager->getRootSceneNode(), _idPool.request());
}

//Flat
void TileBuilder::addFlat(irr::core::vector3df position, float angle)
{
	irr::scene::ISceneNode* node = _flatBuilder.build(_sceneManager, _tileSceneNode, _idPool.request());
	_tileSceneNode->addChild(node);
	node->setRotation(irr::core::vector3df(0,angle,0));
	node->setPosition(position);
	node->drop();
}

//Buildings
void TileBuilder::addHouse(irr::core::vector3df position, float angle)
{
	irr::scene::ISceneNode* node = _houseBuilders[Random::nextInt(0,_houseBuilders.size()-1)].build(_sceneManager, _tileSceneNode, _idPool.request());
	_tileSceneNode->addChild(node);
	node->setScale(irr::core::vector3df(10,10,10));
	node->setRotation(irr::core::vector3df(0,angle,0));
	node->setPosition(position);
	node->drop();
}

void TileBuilder::addSkyScraper(irr::core::vector3df position, float angle)
{
	irr::scene::ISceneNode* node = _skyScraperBuilders[Random::nextInt(0, _skyScraperBuilders.size()-1)].build(_sceneManager, _tileSceneNode, _idPool.request());
	_tileSceneNode->addChild(node);
	node->setRotation(irr::core::vector3df(0,angle,0));
	node->setPosition(position);
	node->drop();
}

void TileBuilder::addApartment(irr::core::vector3df position, float angle)
{
	irr::scene::ISceneNode* node = _apartmentBuilders[Random::nextInt(0, _apartmentBuilders.size()-1)].build(_sceneManager, _tileSceneNode, _idPool.request());
	_tileSceneNode->addChild(node);
	node->setRotation(irr::core::vector3df(0,angle,0));
	node->setPosition(position);
	node->drop();
}

//Plants
void TileBuilder::addGrass(irr::core::vector3df position, float angle)
{
	irr::scene::ISceneNode* node = _grass.build(_sceneManager, _tileSceneNode, _idPool.request());
	_tileSceneNode->addChild(node);
	node->setRotation(irr::core::vector3df(0,angle,0));
	node->setPosition(position);
	node->drop();
}

//Roads
void TileBuilder::addTwoLaneRoad(irr::core::vector3df position, float angle)
{
	irr::scene::ISceneNode* node = _twoLaneRoadBuilder.build(_sceneManager, _tileSceneNode, _idPool.request());
	_tileSceneNode->addChild(node);
	node->setRotation(irr::core::vector3df(0,angle,0));
	node->setPosition(position);
	node->drop();
}

void TileBuilder::addSixLaneRoad(irr::core::vector3df position, float angle)
{
	irr::scene::ISceneNode* node = _sixLaneRoadBuilder.build(_sceneManager, _tileSceneNode, _idPool.request());
	_tileSceneNode->addChild(node);
	node->setRotation(irr::core::vector3df(0,angle,0));
	node->setPosition(position);
	node->drop();
}

void TileBuilder::addSixLaneCornerRoad(irr::core::vector3df position, float angle)
{
	irr::scene::ISceneNode* node = _sixLaneCornerBuilder.build(_sceneManager, _tileSceneNode, _idPool.request());
	_tileSceneNode->addChild(node);
	node->setRotation(irr::core::vector3df(0,angle,0));
	node->setPosition(position);
	node->drop();
}

//T-Intersections
void TileBuilder::addTwoToSixTRoad(irr::core::vector3df position, float angle)
{
	irr::scene::ISceneNode* node = _twoToSixTRoadBuilder.build(_sceneManager, _tileSceneNode, _idPool.request());
	_tileSceneNode->addChild(node);
	node->setRotation(irr::core::vector3df(0,angle,0));
	node->setPosition(position);
	node->drop();
}

void TileBuilder::addSixToTwoTRoad(irr::core::vector3df position, float angle)
{
	irr::scene::ISceneNode* node = _sixToTwoTRoadBuilder.build(_sceneManager, _tileSceneNode, _idPool.request());
	_tileSceneNode->addChild(node);
	node->setRotation(irr::core::vector3df(0,angle,0));
	node->setPosition(position);
	node->drop();
}

void TileBuilder::addSixToSixTRoad(irr::core::vector3df position, float angle)
{
	irr::scene::ISceneNode* node = _sixToSixTRoadBuilder.build(_sceneManager, _tileSceneNode, _idPool.request());
	_tileSceneNode->addChild(node);
	node->setRotation(irr::core::vector3df(0,angle,0));
	node->setPosition(position);
	node->drop();
}

//4-Way Intersections
void TileBuilder::addSixLaneIntersection(irr::core::vector3df position, float angle)
{
	irr::scene::ISceneNode* node = _sixLaneIntersection.build(_sceneManager, _tileSceneNode, _idPool.request());
	_tileSceneNode->addChild(node);
	node->setRotation(irr::core::vector3df(0,angle,0));
	node->setPosition(position);
	node->drop();
}

irr::scene::ISceneNode* TileBuilder::getNode()
{
	return _tileSceneNode;
}