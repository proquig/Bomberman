//
// Created by cloquet on 24/05/16.
//

#ifndef CPP_INDIE_STUDIO_GAME_HPP
#define CPP_INDIE_STUDIO_GAME_HPP

#include <Irrlicht.hpp>
#include <map>

namespace Bomberman
{
  class Game
  {
   private:

    Bomberman::Irrlicht &irr;

    irr::video::SMaterial _material;

    scene::IMeshSceneNode *_m_scene;
    scene::IMeshSceneNode *_wall;

    scene::ISceneNode *_scene;

    scene::IAnimatedMeshSceneNode *_perso;

   public:
    Game();

    void run();

    ~Game();

  };
}

#endif //CPP_INDIE_STUDIO_GAME_HPP
