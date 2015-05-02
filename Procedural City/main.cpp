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
	Description: A procedurally generated city. The textures are
	generated using OpenCL, the models are generated using lua scripts.
	The roads and city layout are generated using the City class.
*/

#if _DEBUG
#include <vld.h>
#endif

#include <iostream>
#include <irrlicht.h>
#include "Random.h"
#include "TileBuilder.h"
#include "City.h"
#include "CLTextureBuilder.h"
#include <time.h>

using namespace std;
using namespace irr;

//Uses CLTextureBuilder to load and run all the OpenCL files
//to generate the textures that are to be used in the city.
void generateAllTextures(video::IVideoDriver* driver);

int main()
{
	//Configure irrlicht device
	const video::E_DRIVER_TYPE VIDEO_DRIVER = video::EDT_OPENGL;
	const bool FULLSCREEN = false;
	const bool VSYNC = false;
	const core::dimension2du WINDOW_DIMENSIONS(1280, 720);

	const wstring CAPTION = L"Procedural City - By: Panagiotis Roubatsis";
	const video::SColor BACKGROUND_COLOR(255, 100, 200, 100);
	
	IrrlichtDevice* device = createDevice(VIDEO_DRIVER, WINDOW_DIMENSIONS, 16, FULLSCREEN, false, VSYNC, 0);

	if(!device)
	{
		cerr<<"Failed to create device!"<<endl;
		return -1;
	}

	device->setWindowCaption(CAPTION.c_str());

	//Sets the seed for the prng
	Random::setSeed(time(NULL));
	//Must call for the TileBuilder class to function correctly
	TileBuilder::initialize();

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* sceneManager = device->getSceneManager();
	gui::IGUIEnvironment* guiEnvironment = device->getGUIEnvironment();

	//Add a first person camera that is controllable using the mouse and arrow keys
	sceneManager->addCameraSceneNodeFPS();
	sceneManager->setAmbientLight(irr::video::SColorf(0.8f, 0.8f, 0.8f, 1.0f));

	generateAllTextures(driver);
	City city(sceneManager);

	while(device->run())
	{
		driver->beginScene(true, true, BACKGROUND_COLOR);

		sceneManager->drawAll();
		guiEnvironment->drawAll();

		driver->endScene();
	}
	
	device->drop();
	return 0;
}

void generateAllTextures(video::IVideoDriver* driver)
{
	CLTextureBuilder b;

	const int SIZE = 512;

	//Bricks
	b.run(SIZE, SIZE, "bricks/red");
	b.getTexture(driver, "bricks.red.tex");
	b.run(SIZE, SIZE, "bricks/white");
	b.getTexture(driver, "bricks.white.tex");
	b.run(SIZE, SIZE, "bricks/brown");
	b.getTexture(driver, "bricks.brown.tex");

	//Roof
	b.run(SIZE, SIZE, "roof");
	b.getTexture(driver, "roof.tex");

	//Plants
	b.run(SIZE, SIZE, "plants/grass");
	b.getTexture(driver, "plants.grass.tex");

	//Windows
	b.run(SIZE, SIZE, "windows/window");
	b.getTexture(driver, "windows.window.tex");
	b.run(SIZE, SIZE, "windows/apartment");
	b.getTexture(driver, "windows.apartment.tex");

	//Skyscrapers
	b.run(SIZE, SIZE, "windows/skyscraper");
	b.getTexture(driver, "windows.skyscraper.tex");
	b.run(SIZE, SIZE, "windows/skyscraper2");
	b.getTexture(driver, "windows.skyscraper2.tex");

	//Roads
	b.run(SIZE, SIZE, "roads/4_way_intersection");
	b.getTexture(driver, "road.4_way_intersection.tex");
	b.run(SIZE, SIZE, "roads/6_6_T_intersection");
	b.getTexture(driver, "road.6_6_T_intersection.tex");
	b.run(SIZE, SIZE, "roads/standard_six_lane");
	b.getTexture(driver, "road.standard_six_lane.tex");
	b.run(SIZE, SIZE, "roads/standard_two_lane");
	b.getTexture(driver, "road.standard_two_lane.tex");
	b.run(SIZE, SIZE, "roads/T_intersection");
	b.getTexture(driver, "road.T_intersection.tex");
	b.run(SIZE, SIZE, "roads/sidewalk");
	b.getTexture(driver, "road.sidewalk.tex");
}
