//
// Created by cloquet on 28/05/16.
//

#include "Obj.hpp"

Bomberman::Obj::Obj(const std::string &mesh_path, const std::string &texture_path, float x, float y, TYPE type):
	_irr(Bomberman::Irrlicht::instance()),
	_x(x),
	_y(y),
	_explosion_time(0)
{
  if (type == CHARACTER || type == BOMB)
    {
      this->_animated_mesh = this->_irr.getSmgr()->getMesh(mesh_path.c_str());
      this->_animated_node = this->_irr.getSmgr()
				 ->addAnimatedMeshSceneNode(this->_animated_mesh, 0, -1, irr::core::vector3df(x, 0, y),
							    irr::core::vector3df(0, 0, 0),irr::core::vector3df(1.0f, 1.0f, 1.0f));
      this->_animated_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->_animated_node->setMD2Animation(irr::scene::EMAT_STAND);
      this->_animated_node->setMaterialTexture(0, this->_irr.getDriver()->getTexture(texture_path.c_str()));
      this->_animated_node->setAnimationSpeed(8.f);
    }

  if (type == BRICK)
    {
      this->_mesh = this->_irr.getSmgr()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(5.f, 5.f, 5.f));
      this->_node = this->_irr.getSmgr()->addMeshSceneNode(this->_mesh);
      this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->_irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(this->_mesh, 0.0001f);
      this->_node->setMaterialTexture(0, this->_irr.getDriver()->getTexture(texture_path.c_str()));
      this->_node->setPosition(irr::core::vector3df(x, 2.5, y));
    }

  if (type == PLAN)
    {
      this->_mesh = this->_irr.getSmgr()->getGeometryCreator()
			->createPlaneMesh(irr::core::dimension2df(x, y), irr::core::dimension2d<irr::u32>(1, 1), 0,
					  irr::core::dimension2df(1.f, 1.f));
      this->_node = this->_irr.getSmgr()->addMeshSceneNode(this->_mesh);
      this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->_irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(this->_mesh, 0.01f);
      this->_node->setMaterialTexture(0, this->_irr.getDriver()->getTexture(texture_path.c_str()));
    }



/*
  this->_mesh = this->_irr.getSmgr()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(5.f, 5.f, 5.f));
  this->_node = this->_irr.getSmgr()->addMeshSceneNode(this->_mesh);
  this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->_irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(this->_mesh, 0.0001f);
  this->_node->setMaterialTexture(0, this->_irr.getDriver()->getTexture(texture_path));
  this->_node->setPosition(irr::core::vector3df(x, 2.5, y));
*/
}

Bomberman::Obj::~Obj()
{

}

float 				Bomberman::Obj::getX() const
{
  return (this->_x);
}

float 				Bomberman::Obj::getY() const
{
  return (this->_y);
}

irr::u32 			Bomberman::Obj::getExplosionTime() const
{
  return (this->_explosion_time);
}

void				Bomberman::Obj::explode()
{

}
