//
// Character.cpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio/src
//
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
//
// Started on  Fri May 27 18:01:17 2016 Guillaume PROQUIN
// Last update Sat May 28 19:36:37 2016 Guillaume PROQUIN
//

#include "Character.hpp"

const std::map<irr::EKEY_CODE, Bomberman::Character::ACTION>			Bomberman::Character::_events = {
  {irr::KEY_KEY_Z, GO_UP},
  {irr::KEY_KEY_S, GO_DOWN},
  {irr::KEY_KEY_Q, GO_LEFT},
  {irr::KEY_KEY_D, GO_RIGHT},
  {irr::KEY_UP, GO_UP},
  {irr::KEY_DOWN, GO_DOWN},
  {irr::KEY_LEFT, GO_LEFT},
  {irr::KEY_RIGHT, GO_RIGHT},
  {irr::KEY_KEY_U, JUMP},
  {irr::KEY_SPACE, PUT_BOMB}
};

Bomberman::Character::Character() :
	Bomberman::Obj::Obj("./assets/ninja/ninja.b3d", "./assets/ninja/nskinrd.jpg", 0, 0, CHARACTER)
{
  this->_animated_node->setLoopMode(false);
  this->_animated_node->setFrameLoop(START_FRAME, START_FRAME);
  this->add_bomb();
}

Bomberman::Character::Character(float x, float y) :	Bomberman::Character::Character()
{
  this->_x = x;
  this->_y = y;
}

Bomberman::Character::~Character()
{
}

void							Bomberman::Character::set_pos(ACTION direction)
{
  float	position[][2] =
    {
      {0, 0.2f},
      {0, -0.2f},
      {-0.2f, 0},
      {0.2f, 0}
    };

  this->_x += position[direction][0];
  this->_y += position[direction][1];
  this->set_orientation(direction);
  this->_animated_node->setPosition(irr::core::vector3df(this->_x, 0, this->_y));
  if (this->_animated_node->getStartFrame() == START_FRAME)
    {
      this->_animated_node->setFrameLoop(START_WALK_FRAME, END_WALK_FRAME);
      this->afk();
    }
}

void							Bomberman::Character::set_orientation(ACTION direction)
{
  int			orientation[4];

  orientation[GO_UP] = 0;
  orientation[GO_DOWN] = 180;
  orientation[GO_LEFT] = -90;
  orientation[GO_RIGHT] = 90;
  this->_animated_node->setRotation(irr::core::vector3df(0, orientation[direction], 0));
}

void							Bomberman::Character::add_bomb()
{
  this->_bombs.push_back(new Bomberman::Bomb());
}

void							Bomberman::Character::put_bomb(ACTION action)
{
  std::vector<Bomberman::Bomb*>::iterator		it;

  it = this->_bombs.begin();
  while (it != this->_bombs.end() && (*it)->getExplosionTime())
    ++it;
  if (it != this->_bombs.end())
    (*it)->put(this->_x, this->_y);
}

void							Bomberman::Character::afk()
{
  AnimationEndCallback	*callback = new AnimationEndCallback();
  this->_animated_node->setAnimationEndCallback(callback);
}

void							Bomberman::Character::jump(ACTION action)
{
  if (this->_animated_node->getStartFrame() == START_FRAME)
    {
      this->_animated_node->setFrameLoop(145, 157);
      this->afk();
    }
}

void							Bomberman::Character::do_action(ACTION action)
{
  CharMemFn					actions[] = {
    &Character::set_pos,
    &Character::set_pos,
    &Character::set_pos,
    &Character::set_pos,
    &Character::put_bomb,
    &Character::jump,
  };

  (this->*actions[action])(action);
}

void							Bomberman::Character::catch_event(std::vector<bool> keys)
{
  std::map<irr::EKEY_CODE, ACTION>::const_iterator	it;

  for (std::map<irr::EKEY_CODE, ACTION>::const_iterator it = this->_events.begin(); it != this->_events.end(); ++it)
    if (keys[it->first])
      this->do_action(it->second);
}
