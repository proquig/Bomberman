//
// Bomb.cpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio
// 
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
// 
// Started on  Sat May 28 16:07:06 2016 Guillaume PROQUIN
// Last update Sat May 28 19:37:34 2016 Guillaume PROQUIN
//

#include "Irrlicht.hpp"
#include "Bomb.hpp"

Bomberman::Bomb::Bomb() :
	Bomberman::Obj::Obj("./assets/Bomb/Bomb.obj", "./assets/Bomb/plasma-grenade.jpg", 0, 0, BOMB)

{
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
}

void		Bomberman::Bomb::explode()
{
  this->reset();
  //ANIMATION
  //HIDE
  //RESET

  this->exp = new Explosion(this->_x, this->_y);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  delete (this->exp);
}
