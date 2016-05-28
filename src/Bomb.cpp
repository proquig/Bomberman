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

Bomberman::Bomb::Bomb() : _irr(Bomberman::Irrlicht::instance())
{
  this->_x = 0;
  this->_y = 0;
  this->_state = AWAITING;
  this->_scene = this->_irr.getSmgr()->getMesh("./assets/Bomb/Bomb.obj");
  this->_bomb = this->_irr.getSmgr()->addAnimatedMeshSceneNode(this->_scene, 0, -1, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(1.025f, 1.025f, 1.025f));
  this->_bomb->setVisible(false);
  this->_bomb->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  this->_bomb->setMD2Animation(irr::scene::EMAT_STAND);
  this->_bomb->setMaterialTexture(0, this->_irr.getDriver()->getTexture("./assets/Bomb/plasma-grenade.jpg"));
}

Bomberman::Bomb::Bomb(float x, float y) : Bomb::Bomb()
{
  this->_x = x;
  this->_y = y;
}

Bomberman::Bomb::~Bomb()
{
  //this->explosion();
  //this->_state = EXPLODED;
  //delete this->_bomb;
  //delete this->_scene;
}

float		Bomberman::Bomb::getX() const
{
  return (this->_x);
}

float		Bomberman::Bomb::getY() const
{
  return (this->_y);
}

void		Bomberman::Bomb::reset()
{
  this->_state = AWAITING;
  this->_explosion_time = 0;
  this->_bomb->setVisible(false);
}

void		Bomberman::Bomb::put(float x, float y)
{
  this->_x = x;
  this->_y = y;
  this->_bomb->setPosition(irr::core::vector3df(this->_x, 0, this->_y));
  this->_bomb->setVisible(true);
  this->_state = POSED;
  this->_explosion_time = (this->_irr.getDevice()->getTimer()->getTime() + 2000);
}

irr::u32	Bomberman::Bomb::getExplosionTime() const
{
  return (this->_explosion_time);
}

void		Bomberman::Bomb::explode()
{
  this->reset();
  //ANIMATION
  //HIDE
  //RESET
  //std::cout << "Boom !" << std::endl;
}
