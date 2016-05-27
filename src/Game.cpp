//
// Created by cloquet on 24/05/16.
//

#include "Game.hpp"
#include "Character.hpp"

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
  _m_scene->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/Wall_Normal.JPG"));

  for (int wallnbr = 0; wallnbr <= 70; wallnbr += 5)
    {
    scene::IMesh *cube = irr.getSmgr()->getGeometryCreator()->createCubeMesh(core::vector3df(5.f, 5.f, 5.f));
    _wall = irr.getSmgr()->addMeshSceneNode(cube, _m_scene);
    _wall->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
    irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.5f);
    _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/Wall.png"));
    _wall->setPosition(irr::core::vector3df(70 / 2 - wallnbr, 0, 60 / 2));

    scene::IMesh *cube2 = irr.getSmgr()->getGeometryCreator()->createCubeMesh(core::vector3df(5.f, 5.f, 5.f));
    _wall = irr.getSmgr()->addMeshSceneNode(cube2, _m_scene);
    _wall->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
    irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.5f);
    _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/Wall.png"));
    _wall->setPosition(irr::core::vector3df(70 / 2 - wallnbr, 0, -60 / 2));
    }

  for (int wallnbr = 0; wallnbr <= 60; wallnbr += 5)
    {
    scene::IMesh *cube = irr.getSmgr()->getGeometryCreator()->createCubeMesh(core::vector3df(5.f, 5.f, 5.f));
    _wall = irr.getSmgr()->addMeshSceneNode(cube, _m_scene);
    _wall->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
    irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.5f);
    _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/Wall.png"));
    _wall->setPosition(irr::core::vector3df(70 / 2, 0, 60 / 2 - wallnbr));

    scene::IMesh *cube2 = irr.getSmgr()->getGeometryCreator()->createCubeMesh(core::vector3df(5.f, 5.f, 5.f));
    _wall = irr.getSmgr()->addMeshSceneNode(cube2, _m_scene);
    _wall->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
    irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.5f);
    _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/Wall.png"));
    _wall->setPosition(irr::core::vector3df(-70 / 2, 0, 60 / 2 -wallnbr));
    }


  /* claase perso
  scene::IAnimatedMesh  *man = irr.getSmgr()->getMesh("./media/Test/ninja.b3d");
  _perso = irr.getSmgr()->addAnimatedMeshSceneNode(man, _scene, -1, core::vector3df(x ,0 ,y), core::vector3df(0, 0, 0), core::vector3df(1.025f, 1.025f, 1.025f));
  _perso->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  _perso->setMD2Animation(scene::EMAT_STAND);
  _perso->getMaterial(0).NormalizeNormals = true;
  _perso->getMaterial(0).Lighting = true;
  _perso->setAnimationSpeed(8.f);
*/
}

Bomberman::Game::~Game()
{
}

void 		Bomberman::Game::run()
{
  irr.getSmgr()->addCameraSceneNode(_m_scene, core::vector3df(0, 45, -10), core::vector3df(0,0,0));
  //_perso->setFrameLoop(0, 60);
  Character lol;
  while (irr.getDevice()->run())
    {

    if (irr.event.IsKeyDown(irr::KEY_KEY_Z))
      lol.set_pos(UP);
    if (irr.event.IsKeyDown(irr::KEY_KEY_S))
      lol.set_pos(DOWN);
    if (irr.event.IsKeyDown(irr::KEY_KEY_Q))
      lol.set_pos(LEFT);
    if (irr.event.IsKeyDown(irr::KEY_KEY_D))
      lol.set_pos(RIGHT);

      irr.getDriver()->beginScene(true, true, video::SColor(255,100,101,140));
      irr.getSmgr()->drawAll();
      irr.getGui()->drawAll();
      irr.getDriver()->endScene();
    }
}