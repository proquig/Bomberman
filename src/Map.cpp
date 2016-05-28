//
// Created by cloquet on 28/05/16.
//

#include <list>
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

irr::scene::IMeshSceneNode *Bomberman::Map::createBreakableWall()
{
  irr::scene::IMeshSceneNode *wall;
  static int 		r = 1;
  srand((unsigned int) time(NULL));

  r  += rand() * rand();
  int x = (rand() + r) % X / 2;
  int y = (rand() + r)% Y / 2;
  for (t_Wall::iterator it = this->_wallBreak.begin(); it != this->_wallBreak.end(); ++it)
    {
    for (int wallnbr = 0; wallnbr <= X; wallnbr += 5)
	{
	  if ( it->first == X / 2 - wallnbr && it->second == Y / 2 ||
		  it->first == X / 2 - wallnbr && it->second == -Y / 2)
	    {
	      it = this->_wallBreak.begin();
	      x = (rand() + r) % X / 2;
	      y = (rand() + r) % Y / 2;
	    }
	}

      for (int wallnbr = 0; wallnbr <= Y; wallnbr += 5)
	{

	  if ( it->first == X / 2 && it->second == Y / 2 - wallnbr ||
		  it->first == X / 2 - wallnbr && it->second == -Y / 2)
	  {
	    it = this->_wallBreak.begin();
	    x = (rand() + r) % X / 2;
	    y = (rand() + r) % Y / 2;
	  }
	}
      if ((it->first == x) && (it->second == y))
	{
	  it = this->_wallBreak.begin();
	  x = (rand() + r) % X / 2;
	  y = (rand() + r)% Y / 2;
	}
    }
  this->_wallBreak.push_back(std::make_pair(x, y));

  irr::scene::IMesh *cube = this->_irr.getSmgr()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(5.f, 5.f, 5.f));
  wall = this->_irr.getSmgr()->addMeshSceneNode(cube, _meshScene);
  wall->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  this->_irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(cube, 0.0001f);
  wall->setMaterialTexture(0, this->_irr.getDriver()->getTexture("./assets/Te/water_ice.jpg"));
  wall->setPosition(irr::core::vector3df(x, 2.5, y));

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
