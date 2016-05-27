//
// Created by cloquet on 24/05/16.
//

#ifndef CPP_INDIE_STUDIO_GAME_HPP
#define CPP_INDIE_STUDIO_GAME_HPP

#include <Irrlicht.hpp>

namespace Bomberman
{
  class Game
  {
   private:
  /* pour classe personnage */
  float x;
    float y;

    Bomberman::Irrlicht &irr;

    irr::video::SMaterial _material;

    scene::IMeshSceneNode *_m_scene;

    scene::IMeshSceneNode *_wall;

    scene::ISceneNode *_scene;


   public:
    Game();
    void run();
    ~Game();
    int right();
    int left();
    int up();
    int down();
  };
}

#endif //CPP_INDIE_STUDIO_GAME_HPP
