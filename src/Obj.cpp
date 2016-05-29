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
  if (type == CHARACTER)
    {
      this->_animated_mesh = this->_irr.getSmgr()->getMesh(mesh_path.c_str());
      this->_animated_node = this->_irr.getSmgr()
				 ->addAnimatedMeshSceneNode(this->_animated_mesh, 0, -1, irr::core::vector3df(x, 0, y),
							    irr::core::vector3df(0, 0, 0),irr::core::vector3df(1.0f, 1.0f, 1.0f));
      this->_animated_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->_animated_node->setMD2Animation(irr::scene::EMAT_STAND);
      this->_animated_node->setMaterialTexture(0, this->_irr.getDriver()->getTexture(texture_path.c_str()));
      this->_animated_node->setAnimationSpeed(25.f);
    }

  if (type == BOMB)
    {
      this->_animated_mesh = this->_irr.getSmgr()->getMesh("/home/cloquet/Documents/cpp/cpp_indie_studio/assets/Bomb/model.dae");//mesh_path.c_str());
      this->_animated_node = this->_irr.getSmgr()
				 ->addAnimatedMeshSceneNode(this->_animated_mesh, 0, -1, irr::core::vector3df(x, 0, y),
							    irr::core::vector3df(0, 0, 0),irr::core::vector3df(0.03f, 0.03f, 0.03f));
      this->_animated_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->_animated_node->setAnimationSpeed(16.f);
    }

  if (type == BRICK)
    {
      this->_mesh = this->_irr.getSmgr()->getMesh(mesh_path.c_str());
      this->_node = this->_irr.getSmgr()->addMeshSceneNode(this->_mesh, 0, -1, irr::core::vector3df(x, 2.5, y), irr::core::vector3df(0, 90, 0),
							   irr::core::vector3df(0.4f, 0.4f, 0.4f));
      this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->_node->setMaterialTexture(0, this->_irr.getDriver()->getTexture(texture_path.c_str()));
      this->_node->setPosition(irr::core::vector3df(x, 2.5, y));
    }

  if (type == BOX)
    {
      this->_mesh = this->_irr.getSmgr()->getMesh(mesh_path.c_str());
      this->_node = this->_irr.getSmgr()->addMeshSceneNode(this->_mesh, 0, -1, irr::core::vector3df(x, 2.5, y), irr::core::vector3df(0, 0, 0),
							   irr::core::vector3df(0.4f, 0.4f, 0.4f));
      this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
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
      this->_irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(this->_mesh, 0.51f);
      this->_node->setMaterialTexture(0, this->_irr.getDriver()->getTexture(texture_path.c_str()));
    }
}

Bomberman::Obj::~Obj()
{
}

Bomberman::IObj*		Bomberman::Obj::create(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type)
{
  std::map<Bomberman::TYPE, (Bomberman::Obj*)(const std::string&, const std::string&, float, float, Bomberman::TYPE)>	objs = {
    {BRICK, &Bomberman::Obj::create},
    {BOX, &Bomberman::Obj::create},
    {PLAN, &Bomberman::Obj::create},
  };
  if (objs.at(type))
    (*objs.at(type)->second())();
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
