//
// Character.hpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio/includes
// 
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
// 
// Started on  Fri May 27 18:46:24 2016 Guillaume PROQUIN
// Last update Fri May 27 19:06:40 2016 Guillaume PROQUIN
//

#ifndef				__CHARACTER_HPP__
# define			__CHARACTER_HPP__

#include			"Irrlicht.hpp"

enum DIRECTION
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class				Character
{
private:
  Bomberman::Irrlicht		&_irr;
  scene::IAnimatedMesh		*_scene;
  scene::IAnimatedMeshSceneNode	*_character;
  float				_x;
  float				_y;
public:
  Character();
  Character(float x, float y);
  ~Character();
  float				get_x() const;
  float				get_y() const;
  scene::IAnimatedMeshSceneNode	*get_character() const;
  void				set_pos(DIRECTION direction);
  void				set_orientation(DIRECTION direction);
  void				test();
  void				u();
  void				base();
};

#endif
