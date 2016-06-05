//
// Character.cpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio/src
//
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
//
// Started on  Fri May 27 18:01:17 2016 Guillaume PROQUIN
// Last update Sun May 29 20:23:04 2016 Guillaume PROQUIN
//

#include <Map.hpp>
#include <Game.hpp>
#include "IA.hpp"

Bomberman::Character::Character(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type) :
	Bomberman::Obj::Obj(mesh_path, texture_path, x, y, Bomberman::CHARACTER), _ia(nullptr)
{
  this->_bombTime = 0;
  this->_godTime = 0;
  this->_speedTime = 1;
  this->_range = 2;
  this->_animated_node->setLoopMode(false);
  this->_animated_node->setFrameLoop(START_FRAME, START_FRAME);
}

Bomberman::Character::~Character()
{
  delete this->_ia;
}

void                                                        Bomberman::Character::set_pos(ACTION direction)
{
  this->_x += (Bomberman::Game::positions[direction][0] * this->_speed);
  this->_y += (Bomberman::Game::positions[direction][1] * this->_speed);
  this->set_orientation(direction);
  this->_animated_node->setPosition(irr::core::vector3df(this->_x, 0, this->_y));
  if (this->_animated_node->getStartFrame() == START_FRAME)
    {
      this->_animated_node->setFrameLoop(START_WALK_FRAME, END_WALK_FRAME);
      this->afk();
    }
}

void                                                        Bomberman::Character::set_orientation(ACTION direction)
{
  int orientation[4];

  orientation[GO_UP] = 0;
  orientation[GO_DOWN] = 180;
  orientation[GO_LEFT] = -90;
  orientation[GO_RIGHT] = 90;
  this->_animated_node->setRotation(irr::core::vector3df(0, orientation[direction], 0));
}

void                                                        Bomberman::Character::add_bomb(Bomberman::Bomb *bomb)
{
  bomb->setRange(&this->_range);
  this->_bombs.push_back(bomb);
}

void                                                        Bomberman::Character::put_bomb(ACTION action)
{
  int i;

  i = -1;
  if (this->_irr.getDevice()->getTimer()->getTime() > this->_bombTime)
    {
      while (++i < this->_bombs.size() && this->_bombs[i]->getExplosionTime());
      if (i < this->_bombs.size())
	{
	  this->_bombTime = (this->_irr.getDevice()->getTimer()->getTime() + 250);
	  this->_bombs[i]->put(this->_x, this->_y);
	}
    }
}

void                                                        Bomberman::Character::afk()
{
  AnimationEndCallback *callback = new AnimationEndCallback();
  this->_animated_node->setAnimationEndCallback(callback);
}

void                                                        Bomberman::Character::jump(ACTION action)
{
  if (this->_animated_node->getStartFrame() == START_FRAME)
    {
      this->_animated_node->setFrameLoop(146, 158);
      this->afk();
    }
}

void                                                        Bomberman::Character::do_action(ACTION action)
{
  CharMemFn actions[] = {
	  &Character::set_pos,
	  &Character::set_pos,
	  &Character::set_pos,
	  &Character::set_pos,
	  &Character::put_bomb,
	  &Character::jump,
  };
  (this->*actions[action])(action);
}

void                                                        Bomberman::Character::setBombRange()
{
  this->_range++;
}

irr::u32                                                Bomberman::Character::getGodTime() const
{
  return (this->_godTime);
}

void                                                        Bomberman::Character::setGodTime(irr::u32 time)
{
  this->_is_destructible = (!time);
  this->_godTime = time;
}

irr::u32                                                Bomberman::Character::getSpeedTime() const
{
  return (this->_speedTime);
}

void                                                        Bomberman::Character::setSpeedTime(irr::u32 time)
{
  this->_speed = time ? 2 : 1;
  this->_speedTime = time;
}

int Bomberman::Character::getSpeed() const
{
  return (this->_speed);
}

void Bomberman::Character::setIa(Bomberman::IA *ia)
{
  this->_ia = ia;
}

void Bomberman::Character::die()
{
  if (this->_ia != nullptr)
    this->_ia->die();
}
