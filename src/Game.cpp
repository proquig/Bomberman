//
// Created by cloquet on 24/05/16.
//

#include "Game.hpp"
#include <IGeometryCreator.h>

Bomberman::Game::Game() : irr(Bomberman::Irrlicht::instance())
{
  x = 0;
  y = 0;
  _material.Lighting = true;

  _scene = irr.getSmgr()->getRootSceneNode();

  scene::IMesh *plan = irr.getSmgr()->getGeometryCreator()->createPlaneMesh(core::dimension2df(70, 60), core::dimension2d<u32>(1, 1), 0, core::dimension2df(1.f,1.f));
  _m_scene = irr.getSmgr()->addMeshSceneNode(plan);
  _m_scene->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.5f);
  _m_scene->setMaterialTexture(0, irr.getDriver()->getTexture("./media/Te/Wall_Normal.JPG"));

  scene::IMesh *cube = irr.getSmgr()->getGeometryCreator()->createCubeMesh(core::vector3df(5.f,5.f,5.f));
  _wall = irr.getSmgr()->addMeshSceneNode(cube, _m_scene);
  _wall->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.5f);
  _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./media/Te/Wall.png"));
  _wall->setPosition(irr::core::vector3df(70/ 2 ,0, 60/ 2));


  scene::IMesh *cube2 = irr.getSmgr()->getGeometryCreator()->createCubeMesh(core::vector3df(5.f,5.f,5.f));
  _wall = irr.getSmgr()->addMeshSceneNode(cube, _m_scene);
  _wall->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.5f);
  _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./media/Te/Wall.png"));
  _wall->setPosition(irr::core::vector3df((70/ 2) - 5 ,0, 60/ 2));

  scene::IMesh *cube3 = irr.getSmgr()->getGeometryCreator()->createCubeMesh(core::vector3df(5.f,5.f,5.f));
  _wall = irr.getSmgr()->addMeshSceneNode(cube, _m_scene);
  _wall->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.5f);
  _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./media/Te/Wall.png"));
  _wall->setPosition(irr::core::vector3df((70/ 2) - 10 ,0, 60/ 2));




  scene::IAnimatedMesh  * man = irr.getSmgr()->getMesh("./media/Bomberman/BomberMan.3ds");
  irr.getSmgr()->getParameters()->setAttribute(scene::CSM_TEXTURE_PATH, "./media/Bomberman");
  _scene = irr.getSmgr()->addAnimatedMeshSceneNode(man, _m_scene, -1, core::vector3df(x ,0 ,y), core::vector3df(-90, 0, 0), core::vector3df(0.025f, 0.025f, 0.025f));

}

int Bomberman::Game::right()
{
  x += 0.2;
  _scene->setPosition(irr::core::vector3df(x ,0,y));
  return (0);
}

int Bomberman::Game::left()
{
  x -= 0.2;
  _scene->setPosition(irr::core::vector3df(x, 0, y));
  return (0);
}

int Bomberman::Game::up()
{
  y += 0.2;
  _scene->setPosition(irr::core::vector3df(x , 0,y));
  return (0);
}

int Bomberman::Game::down()
{
  y -= 0.2;
  _scene->setPosition(irr::core::vector3df(x, 0, y));
  return (0);
}


Bomberman::Game::~Game()
{
}

void 		Bomberman::Game::run()
{
  irr.getSmgr()->addCameraSceneNode(0, core::vector3df(0, 40, -40), core::vector3df(0,5,0));

  while (irr.getDevice()->run())
    {

    if (irr.event.IsKeyDown(irr::KEY_KEY_Z))
      Bomberman::Game::up();
    if (irr.event.IsKeyDown(irr::KEY_KEY_S))
      Bomberman::Game::down();
    if (irr.event.IsKeyDown(irr::KEY_KEY_Q))
      Bomberman::Game::left();
    if (irr.event.IsKeyDown(irr::KEY_KEY_D))
      Bomberman::Game::right();
      irr.getDriver()->beginScene(true, true, video::SColor(255,100,101,140));
      irr.getSmgr()->drawAll();
      irr.getGui()->drawAll();
      irr.getDriver()->endScene();
    }
}