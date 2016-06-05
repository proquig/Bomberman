//
// Created by cloquet on 28/05/16.
//

#include <Obj.hpp>
#include <Map.hpp>
#include <Game.hpp>
#include <Exception.hpp>

Bomberman::Obj::Obj(const std::string &mesh_path, const std::string &texture_path, float x, float y, TYPE type):
	_irr(Bomberman::Irrlicht::instance()),
	_type(type),
	_x(x),
	_y(y),
	_node(NULL),
	_animated_node(NULL),
	_explosion_time(0),
	_animation_time(0),
	_is_blocking(false),
	_is_destructible(true),
	_mesh_path(mesh_path),
	_texture_path(texture_path),
	_sound(Bomberman::MusicManager::instance()),
	_dead(0)
{
  std::map<Bomberman::TYPE, ObjMemFn> objFn = {
	  {Bomberman::CHARACTER, &Obj::createCharacter},
	  {Bomberman::BOMB, &Obj::createBomb},
	  {Bomberman::PLAN, &Obj::createPlan},
	  {Bomberman::BRICK, &Obj::createBrick},
	  {Bomberman::BOX, &Obj::createBox},
	  {Bomberman::BONUS, &Obj::createBonus},
	  {Bomberman::B_STAR, &Obj::createBonus},
	  {Bomberman::B_BOMB_R, &Obj::createBonus},
	  {Bomberman::B_BOMB_N, &Obj::createBonus},
	  {Bomberman::B_BOOT, &Obj::createBonus}
  };

  (this->*objFn[type])();
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

bool 				Bomberman::Obj::isBlocking() const
{
  return (this->_is_blocking);
}

void				Bomberman::Obj::remove()
{
  this->_dead = 1;
  if (this->_node)
    this->_node->setVisible(false);
  if (this->_animated_node)
    this->_animated_node->setVisible(false);
  this->_is_blocking = false;
  this->_is_destructible = false;
  if (Bomberman::Game::_bonus.find(this->getType()) != Bomberman::Game::_bonus.end())
    this->_type = BONUS;
  this->_x = -(BLOCKSIZE / 2);
  this->_y = -(BLOCKSIZE / 2);
/*      try
	{
	  if (_sound.getPlay() == 0)
	    {
	      _sound.setSong("./assets/sound/Boom.flac");
	      _sound.startMusic();
	    }
	}catch (exception &e)
	{
	  std::cerr << e.what() << std::endl;
	}*/

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
  this->_is_blocking = false;
  this->_is_destructible = false;
}
*/
irr::u32  Bomberman::Obj::getAnimation_time() const
{
  return _animation_time;
}

std::string	Bomberman::Obj::getMeshName() const
{
  return this->_mesh_path;
}

std::string	Bomberman::Obj::getTextureName() const
{
  return this->_texture_path;
}

void Bomberman::Obj::createBrick()
{
  if ((this->_mesh = this->_irr.getSmgr()->getMesh(this->_mesh_path.c_str())) == NULL)
    throw (exception("Where is our assets ?"));
  this->_node = this->_irr.getSmgr()->addMeshSceneNode(this->_mesh, 0, -1, irr::core::vector3df(this->_x, 12.5, this->_y), irr::core::vector3df(0, 0, 0),
						       irr::core::vector3df(1.7, 1.7, 1.7));
  this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->_node->setMaterialTexture(0, this->_irr.getDriver()->getTexture(this->_texture_path.c_str()));
  this->_node->setPosition(irr::core::vector3df(this->_x, 12.5, this->_y));
  this->_is_blocking = true;
  this->_is_destructible = false;
}

void Bomberman::Obj::createBox()
{
  if ((this->_mesh = this->_irr.getSmgr()->getMesh(this->_mesh_path.c_str())) == NULL)
    throw (exception("Where is our assets ?"));
  this->_node = this->_irr.getSmgr()->addMeshSceneNode(this->_mesh, 0, -1,
						       irr::core::vector3df(this->_x, 12.5, this->_y),
						       irr::core::vector3df(0, 90, 0),
						       irr::core::vector3df(1.7, 1.7, 1.7));
  this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->_is_blocking = true;
}

void Bomberman::Obj::createPlan()
{
  this->_mesh = this->_irr.getSmgr()->getGeometryCreator()
		    ->createPlaneMesh(irr::core::dimension2df(this->_x, this->_y),
				      irr::core::dimension2d<irr::u32>(1, 1), 0,
				      irr::core::dimension2df(1, 1));
  this->_node = this->_irr.getSmgr()->addMeshSceneNode(this->_mesh);
  this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->_irr.getSmgr()->getMeshManipulator()->makePlanarTextureMapping(this->_mesh, 0.04);
  this->_node->setMaterialTexture(0, this->_irr.getDriver()->getTexture(this->_texture_path.c_str()));
}

void Bomberman::Obj::createCharacter()
{
  if ((this->_animated_mesh = this->_irr.getSmgr()->getMesh(this->_mesh_path.c_str())) == NULL)
    throw (exception("Where is our assets ?"));
  this->_animated_node = this->_irr.getSmgr()
			     ->addAnimatedMeshSceneNode(this->_animated_mesh, 0, -1,
							irr::core::vector3df(this->_x, 0, this->_y),
							irr::core::vector3df(0, 0, 0),
							irr::core::vector3df(5, 5, 5));
  this->_animated_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->_animated_node->setMD2Animation(irr::scene::EMAT_STAND);
  this->_animated_node->setMaterialTexture(0, this->_irr.getDriver()->getTexture(this->_texture_path.c_str()));
  this->_animated_node->setAnimationSpeed(25.f);
}

void Bomberman::Obj::createBomb()
{
  this->_mesh_path = "./assets/Bomb/model.dae";
  if ((this->_animated_mesh = this->_irr.getSmgr()->getMesh(this->_mesh_path.c_str())) == NULL)
    throw (exception("Where is our assets ?"));
  this->_animated_node = this->_irr.getSmgr()
			     ->addAnimatedMeshSceneNode(this->_animated_mesh, 0, -1, irr::core::vector3df(this->_x, 0, this->_y),
							irr::core::vector3df(0, 0, 0),irr::core::vector3df(0.15, 0.15, 0.15));
  this->_animated_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->_animated_node->setAnimationSpeed(16.f);
  this->_animated_node->setVisible(false);

}

void Bomberman::Obj::createBonus()
{
  std::vector<std::pair<TYPE, std::pair<const std::string, const std::string>>> bonus = {
	  {Bomberman::B_STAR, {"./assets/BONUS/MarioStar/star.obj", ""}},
	  //{Bomberman::B_BOOT, {"./assets/BONUS/IronBoots/IronBoots.obj", ""}},
	  {Bomberman::B_BOMB_R, {"./assets/BONUS/AngryBirds/Red/Red_ColladaMax.DAE", ""}},
	  {Bomberman::B_BOMB_N, {"./assets/BONUS/AngryBirds/Red/Red_ColladaMax.DAE", ""}}
  };

  std::srand(std::time(0));
  unsigned int i = std::rand() % bonus.size();
  this->_type = bonus[i].first;
  this->_is_destructible = false;
  this->_mesh_path = bonus[i].second.first;
  this->_node = this->_irr.getSmgr()->addMeshSceneNode(this->_irr.getSmgr()->getMesh(this->_mesh_path.c_str()),
						       0, -1, irr::core::vector3df(this->_x, 1, this->_y),
						       irr::core::vector3df(90, 0 , 0),
						       irr::core::vector3df(1, 1, 1));
  this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

void Bomberman::Obj::die()
{

}
