//
// Created by cloquet on 24/05/16.
//

#include "Game.hpp"
#include <IGeometryCreator.h>

Bomberman::Game::Game() : irr(Bomberman::Irrlicht::instance())
{
  _material.Lighting = false;

//  scene::IMesh
  scene::IMesh *plan = irr.getSmgr()->getGeometryCreator()->createPlaneMesh(core::dimension2df(0.1,0.1), core::dimension2d<u32>(1,1), 0, core::dimension2df(1,1));

  _scene = irr.getSmgr()->addMeshSceneNode(plan);
  //_scene->setPosition(0);
}

Bomberman::Game::~Game()
{
}

void 		Bomberman::Game::run()
{
  irr.getSmgr()->addCameraSceneNode(0, core::vector3df(50, 0, 0), core::vector3df(0,0,0));

  while (irr.getDevice()->run())
    {
      irr.getDriver()->beginScene(true, true, video::SColor(255, 0, 0, 0));
      irr.getSmgr()->drawAll();
      irr.getGui()->drawAll();
      irr.getDriver()->endScene();
    }
}