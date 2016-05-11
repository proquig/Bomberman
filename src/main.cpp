//
// Created by cloquet on 04/05/16.
//

#include <irrlicht.h>
#include <vector>
#include <list>
#include <zconf.h>
#include "driverChoice.h"

using namespace irr;
using namespace gui;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.a")
#endif


class MyEventReceiver : public IEventReceiver
{
 public:
  // This is the one method that we have to implement
  virtual bool OnEvent(const SEvent& event)
  {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return false;
  }

  virtual bool IsKeyDown(EKEY_CODE keyCode) const
  {
    return KeyIsDown[keyCode];
  }

  MyEventReceiver()
  {
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
      KeyIsDown[i] = false;
  }
 private:
  bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main()
{
  video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL;
  MyEventReceiver receiver;
  IrrlichtDevice *device =
	  createDevice(driverType, core::dimension2d<u32>(1920, 1080), 16,
		       false, false, false, &receiver);
  if (device == 0)
  	return (-1);
  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* smgr = device->getSceneManager();

  std::list<video::ITexture *> texture;
  std::list<video::ITexture *>::iterator it;

  texture.push_back(driver->getTexture("../media/Gauntlet_Menu1.png"));
  texture.push_back(driver->getTexture("../media/Gauntlet_Menu2.png"));
  texture.push_back(driver->getTexture("../media/Gauntlet_Menu3.png"));

  it = texture.begin();
  driver->makeColorKeyTexture(*it, core::position2d<s32>(0,0));
  while(device->run())
    {
      usleep(100000);
      u32 now = device->getTimer()->getTime();

      if(receiver.IsKeyDown(irr::KEY_KEY_Z))
	{
	  if (it == texture.begin())
	    {
	      it = texture.end();
	      it--;
	    }
	  else
	    it--;
	}
      else if(receiver.IsKeyDown(irr::KEY_KEY_S))
	{
	  it++;
	  if (it == texture.end()--)
	    it = texture.begin();
	}
      if(receiver.IsKeyDown(irr::KEY_ESCAPE))
	exit(0);
      driver->beginScene(true, true, video::SColor(255,120,102,136));
      driver->draw2DImage(*it, core::rect<s32>(0,0,1920,1080),
			  core::rect<s32>(0,0,1920,1080));
      core::position2d<s32> m = device->getCursorControl()->getPosition();
      driver->endScene();
    }
  device->drop();
  return 0;
}