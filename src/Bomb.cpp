//
// Bomb.cpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio
// 
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
// 
// Started on  Sat May 28 16:07:06 2016 Guillaume PROQUIN
// Last update Sun May 29 20:21:32 2016 Guillaume PROQUIN
//

#include <Exception.hpp>
#include "Irrlicht.hpp"
#include "Bomb.hpp"
#include "Map.hpp"

Bomberman::Bomb::Bomb(const std::string &mesh_path, const std::string &texture_path, float x, float y,
		      Bomberman::TYPE type) :
	Bomberman::Obj::Obj(mesh_path, texture_path, x, y, BOMB)
{
  this->_range = NULL;
  this->_is_destructible = true;
  this->_animated_node->setVisible(false);
}

Bomberman::Bomb::~Bomb()
{
}

float                Bomberman::Bomb::getRange() const
{
  return (*this->_range);
}

void                Bomberman::Bomb::setRange(float *range)
{
  this->_range = range;
}

void                Bomberman::Bomb::reset()
{
  this->_explosion_time = 0;
  this->_is_destructible = false;
  this->_animated_node->setVisible(false);
}

void                Bomberman::Bomb::put(float x, float y)
{
  this->_x = Bomberman::Map::getRoundPosition(x);
  this->_y = Bomberman::Map::getRoundPosition(y);
  this->_animated_node->setPosition(irr::core::vector3df(this->_x, 0, this->_y));
  this->_animated_node->setVisible(true);
  this->_explosion_time = (this->_irr.getDevice()->getTimer()->getTime() + 2000);
  //this->_animation_time = (this->_irr.getDevice()->getTimer()->getTime() + 2500);
  this->_is_destructible = true;
}

void                Bomberman::Bomb::explode()
{
  this->reset();
  try
    {
      if (_sound.getPlay() == 0)
	{
	  _sound.setSong("./assets/sound/Boom.flac");
	  _sound.startMusic();
	}
    }
  catch (exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
}

void                Bomberman::Bomb::clean()
{
}
