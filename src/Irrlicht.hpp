//
// Created by cloquet on 10/05/16.
//

#ifndef CPP_INDIE_STUDIO_IRRLICHT_HPP
#define CPP_INDIE_STUDIO_IRRLICHT_HPP

#include <irrlicht.h>
#include "driverChoice.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.a")
#endif

class 			Irrlicht
{
 private:
  IrrlichtDevice 	*_device;
  video::IVideoDriver	*driver;
  scene::ISceneManager	*smgr;

 public:
  Irrlicht();
  virtual ~Irrlicht();
};


#endif //CPP_INDIE_STUDIO_IRRLICHT_HPP
