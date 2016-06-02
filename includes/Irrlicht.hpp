//
// Created by cloquet on 10/05/16.
//

#ifndef CPP_INDIE_STUDIO_IRRLICHT_HPP
#define CPP_INDIE_STUDIO_IRRLICHT_HPP

#include <irrlicht.h>
#include <cstdlib>
#include <ctime>
#include <map>
#include "driverChoice.h"
#include "EventReceiver.hpp"

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

   public:
    EventReceiver			event;
    irr::IrrlichtDevice 		*getDevice() const;
    irr::video::IVideoDriver 		*getDriver() const;
    irr::gui::IGUIEnvironment 		*getGui() const;
    irr::scene::ISceneManager 		*getSmgr() const;

   private:
    Irrlicht();

    Irrlicht(const Irrlicht &) {}

    Irrlicht& operator=(const Irrlicht&);

    virtual ~Irrlicht();
  };

}


#endif //CPP_INDIE_STUDIO_IRRLICHT_HPP
