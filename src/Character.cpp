//
// Character.cpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio/src
//
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
//
// Started on  Fri May 27 18:01:17 2016 Guillaume PROQUIN
// Last update Sat May 28 15:54:56 2016 Guillaume PROQUIN
//

#include "Character.hpp"

const std::map<EKEY_CODE, ACTION>	Character::_events = {
  {KEY_KEY_Z, GO_UP},
  {KEY_KEY_S, GO_DOWN},
  {KEY_KEY_Q, GO_LEFT},
  {KEY_KEY_D, GO_RIGHT},
  {KEY_KEY_U, JUMP}
};

Character::Character() : _irr(Bomberman::Irrlicht::instance())
{
  this->_x = 0;
  this->_y = 0;
  this->_scene = this->_irr.getSmgr()->getMesh("./assets/ninja/ninja.b3d");
  this->_character = this->_irr.getSmgr()->addAnimatedMeshSceneNode(this->_scene, 0, -1, core::vector3df(0 ,0 ,0), core::vector3df(0, 0, 0), core::vector3df(1.025f, 1.025f, 1.025f));
  this->_character->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  this->_character->setMD2Animation(scene::EMAT_STAND);
  this->_character->setMaterialTexture(0, this->_irr.getDriver()->getTexture("./assets/ninja/nskinrd.jpg"));
  this->_character->setAnimationSpeed(8.f);
  this->_character->setLoopMode(false);
  this->_character->setFrameLoop(START_FRAME, START_FRAME);
}

Character::Character(float x, float y) : Character::Character()
{
  this->_x = x;
  this->_y = y;
}

Character::~Character()
{
}

float			Character::get_x() const
{
  return (this->_x);
}

float			Character::get_y() const
{
  return (this->_y);
}

void			Character::set_pos(ACTION direction)
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
  this->_character->setPosition(irr::core::vector3df(this->_x, 0, this->_y));
  if (this->_character->getStartFrame() == START_FRAME)
    {
      this->_character->setFrameLoop(START_WALK_FRAME, END_WALK_FRAME);
      this->afk();
    }
}

void			Character::set_orientation(ACTION direction)
{
  int			orientation[4];

  orientation[GO_UP] = 0;
  orientation[GO_DOWN] = 180;
  orientation[GO_LEFT] = -90;
  orientation[GO_RIGHT] = 90;
  this->_character->setRotation(irr::core::vector3df(0, orientation[direction], 0));
}

void			Character::put_bomb(ACTION action)
{
}

void			Character::afk()
{
  AnimationEndCallback	*callback = new AnimationEndCallback();
  this->_character->setAnimationEndCallback(callback);
}

void			Character::jump(ACTION action)
{
  if (this->_character->getStartFrame() == START_FRAME)
    {
      this->_character->setFrameLoop(145, 157);
      this->afk();
    }
}

void				Character::do_action(ACTION action)
{
  CharMemFn			actions[] = {
    &Character::set_pos,
    &Character::set_pos,
    &Character::set_pos,
    &Character::set_pos,
    &Character::put_bomb,
    &Character::jump,
  };

  (this->*actions[action])(action);
}

void						Character::catch_event(std::vector<bool> keys)
{
  std::map<EKEY_CODE, ACTION>::const_iterator	it;
  u32						i;

  i = 0;
  for (std::map<EKEY_CODE, ACTION>::const_iterator it = this->_events.begin(); it != this->_events.end(); ++it)
    if (keys[it->first])
      this->do_action(it->second);
}
