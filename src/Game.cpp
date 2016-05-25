//
// Created by cloquet on 24/05/16.
//

#include "Game.hpp"
#include <IGeometryCreator.h>

Bomberman::Game::Game() : irr(Bomberman::Irrlicht::instance())
{
  _material.Lighting = true;

 // scene::IMesh *plan = irr.getSmgr()->getGeometryCreator()->createPlaneMesh(core::dimension2df(70, 60), core::dimension2d<u32>(1, 1), 0, core::dimension2df(1.f,1.f));
  scene::IMesh *cube = irr.getSmgr()->getGeometryCreator()->createCubeMesh(core::vector3df(5.f,5.f,5.f));
  //_scene = irr.getSmgr()->addMeshSceneNode(plan);
  _scene = irr.getSmgr()->addMeshSceneNode(cube);

}

Bomberman::Game::~Game()
{
}

void 		Bomberman::Game::run()
{
  irr.getSmgr()->addCameraSceneNode(0, core::vector3df(0, 40, -40), core::vector3df(0,5,0));

  //irr.getSmgr()->addCameraSceneNodeFPS();
  while (irr.getDevice()->run())
    {
      irr.getDriver()->beginScene(true, true, video::SColor(255,100,101,140));
      irr.getSmgr()->drawAll();
      irr.getGui()->drawAll();
      irr.getDriver()->endScene();
    }
}