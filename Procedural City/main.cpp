#include "procedural_city.h"
#include <iostream>
#include <irrlicht.h>
#include "Random.h"
#include "TileBuilder.h"
#include "City.h"
#include "CLTextureBuilder.h"
#include <vector>
#include <time.h>

using namespace std;
using namespace irr;

void generateAllTextures(video::IVideoDriver* driver);

int main()
{
	const video::E_DRIVER_TYPE VIDEO_DRIVER = video::EDT_OPENGL;
	const bool FULLSCREEN = false;
	const bool VSYNC = false;
	const core::dimension2du WINDOW_DIMENSIONS(1280, 720);

	const wstring CAPTION = L"Procedural City";
	const video::SColor BACKGROUND_COLOR(255, 100, 200, 100);
	
	IrrlichtDevice* device = createDevice(VIDEO_DRIVER, WINDOW_DIMENSIONS, 16, FULLSCREEN, false, VSYNC, 0);

	if(!device)
	{
		cerr<<"Failed to create device!"<<endl;
		return -1;
	}

	device->setWindowCaption(CAPTION.c_str());

	//Sets the seed for the prng
	Random::setSeed(10);
	//Must call for the TileBuilder class to function correctly
	TileBuilder::initialize();

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* sceneManager = device->getSceneManager();
	gui::IGUIEnvironment* guiEnvironment = device->getGUIEnvironment();

	sceneManager->addCameraSceneNodeFPS();
	//sceneManager->addCameraSceneNode(sceneManager->getRootSceneNode(), core::vector3df(0, 0, 32), core::vector3df(0, 0, 0));
	sceneManager->setAmbientLight(irr::video::SColorf(0.8f, 0.8f, 0.8f, 1.0f));

	generateAllTextures(driver);
	City city(sceneManager);

	/*gui::IGUIFont* font = guiEnvironment->getFont("fonts/arial.xml");
	video::ITexture* rt = driver->addRenderTargetTexture(core::dimension2du(512,256), "km.tex");

	driver->setRenderTarget(rt);
	font->draw("Kwik-E-Mart", core::recti(0,0,512,256), video::SColor(255,255,0,0), true, true);
	driver->setRenderTarget(0);
	
	ScriptedNodeBuilder b("models/apartment/building");
	CustomNode* node = b.build(sceneManager, sceneManager->getRootSceneNode(), 534);
	//node->setScale(core::vector3df(30,10,15));

	node->drop();*/

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

	b.run(SIZE, SIZE, "bricks/red");
	b.getTexture(driver, "bricks.red.tex");
	b.run(SIZE, SIZE, "bricks/white");
	b.getTexture(driver, "bricks.white.tex");
	b.run(SIZE, SIZE, "bricks/brown");
	b.getTexture(driver, "bricks.brown.tex");

	b.run(SIZE, SIZE, "roof");
	b.getTexture(driver, "roof.tex");

	b.run(SIZE, SIZE, "plants/grass");
	b.getTexture(driver, "plants.grass.tex");

	b.run(SIZE, SIZE, "windows/window");
	b.getTexture(driver, "windows.window.tex");
	b.run(SIZE, SIZE, "windows/apartment");
	b.getTexture(driver, "windows.apartment.tex");
	b.run(SIZE, SIZE, "windows/skyscraper");
	b.getTexture(driver, "windows.skyscraper.tex");

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
