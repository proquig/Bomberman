//
// Bomb.cpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio
// 
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
// 
// Started on  Sat May 28 16:07:06 2016 Guillaume PROQUIN
// Last update Sun May 29 20:21:32 2016 Guillaume PROQUIN
//

#include "Irrlicht.hpp"
#include "Bomb.hpp"

Bomberman::Bomb::Bomb(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type) :
	Bomberman::Obj::Obj(mesh_path, texture_path, x, y, BOMB)

{
  this->_range = NULL;
  this->_state = AWAITING;
  this->_animated_node->setVisible(false);
}

Bomberman::Bomb::~Bomb()
{
  //this->explosion();
  //this->_state = EXPLODED;
  //delete this->_animated_node;
  //delete this->_scene;
}

/*Bomberman::Obj*	Bomberman::Bomb::create(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type)
{
  return (new Bomb(mesh_path, texture_path, x, y));
}
*/

float 		Bomberman::Bomb::getRange() const
{
  return (*this->_range);
}

void		Bomberman::Bomb::setRange(float *range)
{
  this->_range = range;
}

void		Bomberman::Bomb::reset()
{
  this->_state = AWAITING;
  this->_explosion_time = 0;
  this->_animated_node->setVisible(false);
}

void		Bomberman::Bomb::put(float x, float y)
{
  this->_x = x;
  this->_y = y;
  this->_animated_node->setPosition(irr::core::vector3df(this->_x, 0, this->_y));
  this->_animated_node->setVisible(true);
  this->_state = POSED;
  this->_explosion_time = (this->_irr.getDevice()->getTimer()->getTime() + 2000);
  this->_animation_time = this->_irr.getDevice()->getTimer()->getTime()  + 2500;
}

void		Bomberman::Bomb::explode()
{
  this->reset();
  this->exp = new Explosion(this->_x, this->_y);
}

void 		Bomberman::Bomb::clean()
{
  this->exp->clear();
  delete this->exp;
  this->_animation_time = 0;
}
