//
// Created by cloquet on 24/05/16.
//

#include <Bomb.hpp>
#include "Game.hpp"
#include "Character.hpp"
#include "Map.hpp"

# define X 90
# define Y 70

Bomberman::Game::Game() : irr(Bomberman::Irrlicht::instance())
{
  Bomberman::Map *map = new Map;
  map->createMap();

  //_wall.push_back(map->createBreakableWall());
}

Bomberman::Game::~Game()
{
}

void Bomberman::Game::run()
{
  Character lol;
  scene::ICameraSceneNode *camera = irr.getSmgr()->addCameraSceneNode(0, core::vector3df(0, 60, -20),
								      core::vector3df(0, 0, 0));
  irr::video::ITexture *background = irr.getDriver()->getTexture("./assets/Te/sky-clouds.jpg");
  u32 now = 0;
  while (irr.getDevice()->run())
    {
      lol.catch_event(irr.event.getKeys());
      irr.getDriver()->beginScene(true, true, video::SColor(255, 100, 101, 140));
      irr.getDriver()->draw2DImage(background, core::rect<s32>(0, 0, 1920, 1080),
				   core::rect<s32>(0, 0, 1920, 1080));
      irr.getSmgr()->drawAll();
      irr.getGui()->drawAll();
      irr.getDriver()->endScene();
    }
}
