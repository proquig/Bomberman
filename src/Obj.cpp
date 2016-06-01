//
// Created by cloquet on 28/05/16.
//

#include <Map.hpp>

Bomberman::Obj::Obj(const std::string &mesh_path, const std::string &texture_path, float x, float y, TYPE type):
	_irr(Bomberman::Irrlicht::instance()),
	_type(type),
	_x(x),
	_y(y),
	_node(NULL),
	_animated_node(NULL),
	_explosion_time(0),
	_animation_time(0),
	_is_blockable(false),
	_is_destructible(true),
	_mesh_name(mesh_path),
	_texture_name(texture_path)
{
  if (type == CHARACTER)
    {
      this->_animated_mesh = this->_irr.getSmgr()->getMesh(mesh_path.c_str());
      this->_animated_node = this->_irr.getSmgr()
				 ->addAnimatedMeshSceneNode(this->_animated_mesh, 0, -1, irr::core::vector3df(x, 0, y),
							    irr::core::vector3df(0, 0, 0),irr::core::vector3df(5, 5, 5));
      this->_animated_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->_animated_node->setMD2Animation(irr::scene::EMAT_STAND);
      this->_animated_node->setMaterialTexture(0, this->_irr.getDriver()->getTexture(texture_path.c_str()));
      this->_animated_node->setAnimationSpeed(25.f);
    }

  if (type == BOMB)
    {
      this->_mesh_name = "./assets/Bomb/model.dae";
      this->_animated_mesh = this->_irr.getSmgr()->getMesh("./assets/Bomb/model.dae");
      this->_animated_node = this->_irr.getSmgr()
				 ->addAnimatedMeshSceneNode(this->_animated_mesh, 0, -1, irr::core::vector3df(x, 0, y),
							    irr::core::vector3df(0, 0, 0),irr::core::vector3df(0.15, 0.15, 0.15));
      this->_animated_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->_animated_node->setAnimationSpeed(16.f);
      this->_animated_node->setVisible(false);
    }

  if (type == BRICK)
    {
      this->_mesh = this->_irr.getSmgr()->getMesh(mesh_path.c_str());
      this->_node = this->_irr.getSmgr()->addMeshSceneNode(this->_mesh, 0, -1, irr::core::vector3df(x, 12.5, y), irr::core::vector3df(0, 90, 0),
							   irr::core::vector3df(2, 2, 2));
      this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->_node->setMaterialTexture(0, this->_irr.getDriver()->getTexture(texture_path.c_str()));
      this->_node->setPosition(irr::core::vector3df(x, 2.5, y));
      this->_is_blockable = true;
      this->_is_destructible = false;
    }

  if (type == BOX)
    {
      this->_mesh = this->_irr.getSmgr()->getMesh(mesh_path.c_str());
      this->_node = this->_irr.getSmgr()->addMeshSceneNode(this->_mesh, 0, -1, irr::core::vector3df(x, 12.5, y), irr::core::vector3df(0, 0, 0),
							   irr::core::vector3df(2, 2, 2));
      this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->_node->setPosition(irr::core::vector3df(x, 2.5, y));
      this->_is_blockable = true;
    }

  if (type == PLAN)
    {
      this->_mesh = this->_irr.getSmgr()->getGeometryCreator()
			->createPlaneMesh(irr::core::dimension2df(x, y), irr::core::dimension2d<irr::u32>(1, 1), 0,
					  irr::core::dimension2df(1.f, 1.f));
      this->_node = this->_irr.getSmgr()->addMeshSceneNode(this->_mesh);
      this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->_irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(this->_mesh, 2.5);
      this->_node->setMaterialTexture(0, this->_irr.getDriver()->getTexture(texture_path.c_str()));
    }
}

Bomberman::Obj::~Obj()
{
}

Bomberman::TYPE 		Bomberman::Obj::getType() const
{
  return (this->_type);
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

bool 				Bomberman::Obj::isBlockable() const
{
  return (this->_is_blockable);
}

void				Bomberman::Obj::remove()
{
  if (this->_node)
    this->_node->setVisible(false);
  if (this->_animated_node)
    this->_animated_node->setVisible(false);
  this->_is_blockable = false;
  this->_is_destructible = false;
}

tinyxml2::XMLElement *Bomberman::Obj::serialize(tinyxml2::XMLDocument *doc)
{
  time_t current_time;

  time(&current_time);
  tinyxml2::XMLElement *element = doc->NewElement("object");
  element->SetAttribute("type", this->_type);
  element->SetAttribute("x", this->_x);
  element->SetAttribute("y", this->_y);
  element->SetAttribute("explosionDelay", (int) (this->_explosion_time - current_time));
  element->SetAttribute("is_blockable", this->_is_blockable);
  element->SetAttribute("is_destructible", this->_is_destructible);
  return nullptr;
}

void Bomberman::Obj::deserialize(tinyxml2::XMLElement *element)
{
  time_t current_time;

  time(&current_time);
  this->_type = (TYPE) std::stoi(element->Attribute("type"));
  this->_x = std::stof(element->Attribute("x"));
  this->_y = std::stof(element->Attribute("y"));
  this->_explosion_time = (irr::u32) (current_time + std::stoi(element->Attribute("explosionDelay")));
  this->_is_blockable = element->Attribute("is_blockable") == "true";
  this->_is_destructible = element->Attribute("is_destructible") == "true";
}

bool Bomberman::Obj::isDestructible() const
{
  return (this->_is_destructible);
}

/*
void Bomberman::Obj::reset()
{
  if (this->_node)
    {
      this->_node->setPosition(irr::core::vector3df(this->_x, 0, this->_y));
      this->_node->setVisible(true);
    }
  if (this->_animated_node)
    {
      this->_animated_node->setPosition(irr::core::vector3df(this->_x, 0, this->_y));
      this->_animated_node->setVisible(true);
    }
  this->_is_blockable = false;
  this->_is_destructible = false;
}
*/
irr::u32  Bomberman::Obj::getAnimation_time() const
{
  return _animation_time;
}

std::string	Bomberman::Obj::getMeshName() const
{
  return this->_mesh_name;
}

std::string	Bomberman::Obj::getTextureName() const
{
  return this->_texture_name;
}



