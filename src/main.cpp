//
// Created by cloquet on 04/05/16.
//

#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;
using namespace gui;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.a")
#endif


int main()
{
  video::E_DRIVER_TYPE driverType = video::EDT_OPENGL;
  IrrlichtDevice *device =
	  createDevice(driverType, core::dimension2d<u32>(1920, 1080));
  if (device == 0)
  	return (-1);
  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* smgr = device->getSceneManager();

  video::ITexture* images = driver->getTexture("../media/Gauntlet_Menu.png");
  driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));

  while(device->run())
    {
      if (device->isWindowActive())
	{
	  u32 time = device->getTimer()->getTime();

	  driver->beginScene(true, true, video::SColor(255,120,102,136));
	  driver->enableMaterial2D();
	  driver->draw2DImage(images, core::rect<s32>(10,10,108,48),
			      core::rect<s32>(354,87,442,118));
	  driver->enableMaterial2D(false);
	  core::position2d<s32> m = device->getCursorControl()->getPosition();
	  driver->endScene();
	}
    }

  device->drop();

  return 0;
}