//
// Created by cloquet on 10/05/16.
//

#include "Irrlicht.hpp"

Irrlicht::Irrlicht()
{
  video::E_DRIVER_TYPE driverType = video::EDT_OPENGL;
  IrrlichtDevice *device =
	  createDevice(driverType, core::dimension2d<u32>(640, 480));
  if (device == 0)

}