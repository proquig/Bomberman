//
// Created by cloquet on 28/05/16.
//

#include "Map.hpp"

Bomberman::Map::Map() : irr(Bomberman::Irrlicht::instance())
{
}

void                Bomberman::Map::createMap()
{
  _material.Lighting = true;
  _scene = irr.getSmgr()->getRootSceneNode();
  irr::scene::IMesh *plan = irr.getSmgr()->getGeometryCreator()
    ->createPlaneMesh(irr::core::dimension2df(X, Y), irr::core::dimension2d<irr::u32>(1, 1), 0,
		      irr::core::dimension2df(1.f, 1.f));
  _m_scene = irr.getSmgr()->addMeshSceneNode(plan);
  _m_scene->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.01f);
  _m_scene->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/Sand_floor.jpg"));

  for (int wallnbr = 0; wallnbr <= X; wallnbr += 5)
    {
      irr::scene::IMesh *cube = irr.getSmgr()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(5.f, 5.f, 5.f));
      _wall = irr.getSmgr()->addMeshSceneNode(cube, _m_scene);
      _wall->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
      irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(cube, 0.0001f);
      _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/wall.jpg"));
      _wall->setPosition(irr::core::vector3df(X / 2 - wallnbr, 2.5, Y / 2));

      irr::scene::IMesh *cube2 = irr.getSmgr()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(5.f, 5.f, 5.f));
      _wall = irr.getSmgr()->addMeshSceneNode(cube2, _m_scene);
      _wall->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
      irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(cube2, 0.0001f);
      _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/wall.jpg"));
      _wall->setPosition(irr::core::vector3df(X / 2 - wallnbr, 2.5, -Y / 2));
    }

  for (int wallnbr = 0; wallnbr <= Y; wallnbr += 5)
    {
      irr::scene::IMesh *cube = irr.getSmgr()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(5.f, 5.f, 5.f));
      _wall = irr.getSmgr()->addMeshSceneNode(cube, _m_scene);
      _wall->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
      irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(cube, 0.0001f);
      _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/wall.jpg"));
      _wall->setPosition(irr::core::vector3df(X / 2, 2.5, Y / 2 - wallnbr));

      irr::scene::IMesh *cube2 = irr.getSmgr()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(5.f, 5.f, 5.f));
      _wall = irr.getSmgr()->addMeshSceneNode(cube2, _m_scene);
      _wall->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
      irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(cube2, 0.0001f);
      _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/wall.jpg"));
      _wall->setPosition(irr::core::vector3df(-X / 2, 2.5, Y / 2 - wallnbr));
    }
}

irr::scene::IMeshSceneNode *Bomberman::Map::creatBreakBlock()
{
  irr::scene::IMesh *cube = irr.getSmgr()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(5.f, 5.f, 5.f));
  _wall = irr.getSmgr()->addMeshSceneNode(cube, _m_scene);
  _wall->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(cube, 0.0001f);
  _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/water_ice.jpg"));
  _wall->setPosition(irr::core::vector3df(0, 2.5,0));
}

void Bomberman::Map::creatBlock()
{
  for (int wallnbr = 0; wallnbr <= Y; wallnbr += 5)
    {
      irr::scene::IMesh *cube = irr.getSmgr()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(5.f, 5.f, 5.f));
      _wall = irr.getSmgr()->addMeshSceneNode(cube, _m_scene);
      _wall->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
      irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(cube, 0.0001f);
      _wall->setMaterialTexture(0, irr.getDriver()->getTexture("./assets/Te/wall.jpg"));
      _wall->setPosition(irr::core::vector3df(X / 2 - wallnbr, 2.5, Y / 2 - wallnbr));
    }
}
