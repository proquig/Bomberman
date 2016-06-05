//
// AnimationEndCallback.cpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio
// 
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
// 
// Started on  Sat May 28 14:56:18 2016 Guillaume PROQUIN
// Last update Sat May 28 15:48:39 2016 Guillaume PROQUIN
//

#include "AnimationEndCallback.hpp"
#include "Character.hpp"

AnimationEndCallback::AnimationEndCallback()
{
}

AnimationEndCallback::~AnimationEndCallback()
{
}

void        AnimationEndCallback::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode *node)
{
  node->setLoopMode(false);
  node->setFrameLoop(START_FRAME, START_FRAME);
}
