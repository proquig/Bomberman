//
// Created by cloquet on 28/05/16.
//

#include "Map.hpp"

Bomberman::Map::Map() : _irr(Bomberman::Irrlicht::instance())
{
}

Bomberman::Map::~Map()
{
}

void                Bomberman::Map::createMap()
{
  _material.Lighting = true;

  _scene = this->_irr.getSmgr()->getRootSceneNode();

  irr::scene::IMesh *plan = this->_irr.getSmgr()->getGeometryCreator()
    ->createPlaneMesh(irr::core::dimension2df(X, Y), irr::core::dimension2d<irr::u32>(1, 1), 0,
		      irr::core::dimension2df(1.f, 1.f));
  this->_meshScene = this->_irr.getSmgr()->addMeshSceneNode(plan);
  this->_meshScene->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  this->_irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(plan, 0.01f);
  this->_meshScene->setMaterialTexture(0, this->_irr.getDriver()->getTexture("./assets/Te/brick.jpg"));

  for (int wallnbr = 0; wallnbr <= X; wallnbr += 5)
    {
      createWall(X / 2 - wallnbr, Y / 2);
      createWall(X / 2 - wallnbr, -Y / 2);
    }

  for (int wallnbr = 0; wallnbr <= Y; wallnbr += 5)
    {
      createWall(X / 2, Y / 2 - wallnbr);
      createWall(-X / 2, Y / 2 - wallnbr);
      //scene::ISceneNodeAnimator *r = this->_irr.getSmgr()->createCollisionResponseAnimator(wall->getTriangleSelector(), _scene);
    }
}

irr::scene::IMeshSceneNode *Bomberman::Map::createBreakableWall(int x, int y) const
{
  irr::scene::IMeshSceneNode *wall;

  irr::scene::IMesh *cube = this->_irr.getSmgr()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(5.f, 5.f, 5.f));
  wall = this->_irr.getSmgr()->addMeshSceneNode(cube, _meshScene);
  wall->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  this->_irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(cube, 0.0001f);
  wall->setMaterialTexture(0, this->_irr.getDriver()->getTexture("./assets/Te/water_ice.jpg"));
  wall->setPosition(irr::core::vector3df(0, 2.5,0));

  return wall;
}

void Bomberman::Map::createWall(int x, int y) const
{
  irr::scene::IMeshSceneNode *wall;

  irr::scene::IMesh *cube = this->_irr.getSmgr()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(5.f, 5.f, 5.f));
  wall = this->_irr.getSmgr()->addMeshSceneNode(cube, this->_meshScene);
  wall->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->_irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(cube, 0.0001f);
  wall->setMaterialTexture(0, this->_irr.getDriver()->getTexture("./assets/Te/wall.jpg"));
  wall->setPosition(irr::core::vector3df(x, 2.5, y));
}
