//
// AnimationEndCallback.cpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio/includes
// 
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
// 
// Started on  Sat May 28 14:34:23 2016 Guillaume PROQUIN
// Last update Sat May 28 14:57:22 2016 Guillaume PROQUIN
//

#ifndef		__ANIMATIONENDCALLBACK_CPP__
# define	__ANIMATIONENDCALLBACK_CPP__

#include	<irrlicht.h>

class		AnimationEndCallback : public irr::scene::IAnimationEndCallBack
{
public:
  AnimationEndCallback();
  ~AnimationEndCallback();
  void		OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode *node);
};

#endif
