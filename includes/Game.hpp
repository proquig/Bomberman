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
    std::vector<scene::IMeshSceneNode *> _wall;

   public:
    Game();

    void run();

    ~Game();

  };
}

#endif //CPP_INDIE_STUDIO_GAME_HPP
