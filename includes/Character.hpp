//
// Character.hpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio/includes
// 
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
// 
// Started on  Fri May 27 18:46:24 2016 Guillaume PROQUIN
// Last update Sat May 28 13:00:07 2016 Guillaume PROQUIN
//

#ifndef						__CHARACTER_HPP__
# define					__CHARACTER_HPP__

#include					"Irrlicht.hpp"

enum						ACTION
{
  GO_UP,
  GO_DOWN,
  GO_LEFT,
  GO_RIGHT,
  PUT_BOMB,
  JUMP
};

class						Character;

typedef						void (Character::*CharMemFn)(ACTION);

class						Character
{
private:
  Bomberman::Irrlicht				&_irr;
  scene::IAnimatedMesh				*_scene;
  scene::IAnimatedMeshSceneNode			*_character;
  float						_x;
  float						_y;
  static const std::map<EKEY_CODE, ACTION>	_events;
public:
  Character();
  Character(float x, float y);
  ~Character();
  float						get_x() const;
  float						get_y() const;
  void						set_pos(ACTION direction);
  void						set_orientation(ACTION direction);
  void						put_bomb(ACTION action);
  void						do_action(ACTION action);
  void						jump(ACTION action);
  void						catch_event(std::vector<bool> keys);
};

#endif
