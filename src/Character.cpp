//
// Character.cpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio/src
// 
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
// 
// Started on  Fri May 27 18:01:17 2016 Guillaume PROQUIN
// Last update Fri May 27 19:23:03 2016 Guillaume PROQUIN
//

#include <unistd.h>
#include "Character.hpp"

Character::Character() : _irr(Bomberman::Irrlicht::instance())
{
  this->_x = 0;
  this->_y = 0;
  //this->_scene = this->_irr.getSmgr()->getMesh("./assets/Test/ninja.b3d");
  this->_scene = this->_irr.getSmgr()->getMesh("./assets/ninja/ninja.b3d");
  this->_character = this->_irr.getSmgr()->addAnimatedMeshSceneNode(this->_scene, 0, -1, core::vector3df(0 ,0 ,0), core::vector3df(0, 0, 0), core::vector3df(1.025f, 1.025f, 1.025f));
  this->_character->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  this->_character->setMD2Animation(scene::EMAT_STAND);
  this->_character->setMaterialTexture(0, this->_irr.getDriver()->getTexture("./assets/ninja/nskinrd.jpg"));
  this->_character->setAnimationSpeed(8.f);
  //TODO: géré les bon bails :D
  this->_character->setFrameLoop(0, 14);
}

Character::Character(float x, float y) : Character::Character()
{
  this->_x = x;
  this->_y = y;
}

Character::~Character()
{
}

float	Character::get_x() const
{
  return (this->_x);
}

float	Character::get_y() const
{
  return (this->_y);
}

void	Character::set_pos(DIRECTION direction)
{
  float	position[][2] =
    {
      {0, 0.2},
      {0, -0.2},
      {-0.2, 0},
      {0.2, 0}
    };

  this->_x += position[direction][0];
  this->_y += position[direction][1];
  this->set_orientation(direction);
  this->_character->setPosition(irr::core::vector3df(this->_x, 0, this->_y));
}

void		Character::u()
{
  this->_character->setFrameLoop(145, 157);
}

void		Character::base()
{
  this->_character->setFrameLoop(0, 14);
}

void	Character::test()
{
  static int status = 0;

  this->_character->setFrameLoop(status, status + 1);
  std::cout << "STATUS: " << status << std::endl;
  status++;
}

void	Character::set_orientation(DIRECTION direction)
{
  int	orientation[4];

  orientation[UP] = 0;
  orientation[DOWN] = 180;
  orientation[LEFT] = -90;
  orientation[RIGHT] = 90;
  this->_character->setRotation(irr::core::vector3df(0, orientation[direction], 0));
}
