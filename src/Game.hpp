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
    Bomberman::Irrlicht &irr;

    irr::video::SMaterial _material;

    scene::IMeshSceneNode *_scene;


   public:
    Game();
    void run();
    ~Game();
  };
}

#endif //CPP_INDIE_STUDIO_GAME_HPP
