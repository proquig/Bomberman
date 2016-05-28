//
// Character.hpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio/includes
// 
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
// 
// Started on  Fri May 27 18:46:24 2016 Guillaume PROQUIN
// Last update Sat May 28 16:27:07 2016 Guillaume PROQUIN
//

#ifndef						__CHARACTER_HPP__
# define					__CHARACTER_HPP__

#include					"Irrlicht.hpp"
#include					"AnimationEndCallback.hpp"

# define					START_FRAME 0
# define					START_WALK_FRAME 1
# define					END_WALK_FRAME 10

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
  irr::scene::IAnimatedMesh			*_scene;
  irr::scene::IAnimatedMeshSceneNode		*_character;
  float						_x;
  float						_y;
  static const std::map<irr::EKEY_CODE, ACTION>	_events;
public:
  Character();
  Character(float x, float y);
  ~Character();
  irr::scene::IAnimatedMeshSceneNode		*get_node() const;
  float						get_x() const;
  float						get_y() const;
  void						set_pos(ACTION direction);
  void						set_orientation(ACTION direction);
  void						add_bomb();
  void						put_bomb(ACTION action);
  void						do_action(ACTION action);
  void						jump(ACTION action);
  void						afk();
  void						catch_event(std::vector<bool> keys);
};

#endif
