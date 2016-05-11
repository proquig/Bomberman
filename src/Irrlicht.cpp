//
// Created by cloquet on 10/05/16.
//

#include "Irrlicht.hpp"
#include "Exception.hpp"

Irrlicht::Irrlicht()
{
  video::E_DRIVER_TYPE driverType = video::EDT_OPENGL;
  IrrlichtDevice *device =
	  createDevice(driverType, core::dimension2d<u32>(1920, 1080));
  if (device == 0)
	throw (exception("Can't Load OpenGL"));
  device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* smgr = device->getSceneManager();

}

Irrlicht::~Irrlicht()
{
}