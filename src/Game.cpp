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

Bomberman::Game::Game() : irr(Bomberman::Irrlicht::instance())
{
  Bomberman::Map *map = new Map;
  map->createMap();

  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
  _wall.push_back(map->createBreakableWall());
}

Bomberman::Game::~Game()
{
}

void Bomberman::Game::run()
{
  Character lol(0, 0);
  irr::scene::ICameraSceneNode *camera = irr.getSmgr()->addCameraSceneNode(0, irr::core::vector3df(0, 60, -20),
									   irr::core::vector3df(0, 0, 0));
  irr::video::ITexture *background = irr.getDriver()->getTexture("./assets/Te/sky-clouds.jpg");
  irr::u32 now = 0;
  lol.add_bomb();
  lol.add_bomb();
  while (irr.getDevice()->run())
    {
      lol.handle_event();
      lol.catch_event(irr.event.getKeys());
      if (irr.event.IsKeyDown(irr::KEY_ESCAPE))
	{
	  Bomberman::Menu menu;
	  menu.run();
	}
      irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
      irr.getDriver()->draw2DImage(background, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
				   irr::core::rect<irr::s32>(0, 0, 1920, 1080));
      irr.getSmgr()->drawAll();
      irr.getGui()->drawAll();
      irr.getDriver()->endScene();
    }
}
