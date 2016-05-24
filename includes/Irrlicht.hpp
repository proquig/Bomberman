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


namespace Bomberman
{
  class Irrlicht
  {
    // Singleton
   private:
    static Irrlicht _instance;

   public:
    static Irrlicht &instance();

   private:
    irr::IrrlichtDevice *_device;
    irr::video::IVideoDriver *_driver;
    irr::scene::ISceneManager *_smgr;

   public:

    irr::IrrlichtDevice *get_device() const;

    irr::video::IVideoDriver *get_driver() const;

    irr::scene::ISceneManager *get_smgr() const;

   private:
    Irrlicht();

    Irrlicht(const Irrlicht &) {}

    Irrlicht& operator=(const Irrlicht&);

    virtual ~Irrlicht();
  };
}


#endif //CPP_INDIE_STUDIO_IRRLICHT_HPP
