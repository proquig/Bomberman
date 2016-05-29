//
// Created by cloquet on 24/05/16.
//

#include <Bomb.hpp>
#include <Menu.hpp>
#include "Game.hpp"
#include "Character.hpp"
#include "Map.hpp"

# define X 90
# define Y 70

Bomberman::Game::Game() : _irr(Bomberman::Irrlicht::instance())
{
  this->_map = new Bomberman::Map();
  this->_map->createMap();
/*
   for (int i = 0; i < 20; ++i)
   {
     this->_map->putObjSomewhere(Bomberman::Obj::BOX);
     this->_map->putObjSomewhere(Bomberman::Obj::BRICK);
   }
   */
}

Bomberman::Game::~Game()
{
}

void Bomberman::Game::run()
{
  Character lol(this->_map);
  irr::scene::ICameraSceneNode *camera = this->_irr.getSmgr()->addCameraSceneNode(0, irr::core::vector3df(0, 60, -20),
									   irr::core::vector3df(0, 0, 0));
  camera->setNearValue(10);
  irr::video::ITexture *background = this->_irr.getDriver()->getTexture("./assets/Te/sky-clouds.jpg");
  irr::u32 now = 0;
  lol.add_bomb();
  lol.add_bomb();



  int 	lastFPS = -1;
  while (this->_irr.getDevice()->run())
    {
      lol.handle_event();
      lol.catch_event(this->_irr.event.getKeys());
      if (this->_irr.event.IsKeyDown(irr::KEY_ESCAPE))
	{
	  Bomberman::Menu menu;
	  menu.run();
	}
     if (this->_irr.getDevice()->isWindowActive())
       {
	 this->_irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
	 this->_irr.getDriver()->draw2DImage(background, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
					     irr::core::rect<irr::s32>(0, 0, 1920, 1080));
	 this->_irr.getSmgr()->drawAll();
	 this->_irr.getDriver()->endScene();

	 int fps = this->_irr.getDriver()->getFPS();
	 if (lastFPS != fps)
	   {
	     irr::core::stringw str = "Bomberman | driver [";
	     str += this->_irr.getDriver()->getName();
	     str += "] FPS :";
	     str += fps;
	     this->_irr.getDevice()->setWindowCaption(str.c_str());
	     lastFPS = fps;
	   }
       }
    }
}
