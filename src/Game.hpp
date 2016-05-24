//
// Created by cloquet on 24/05/16.
//

#ifndef CPP_INDIE_STUDIO_GAME_HPP
#define CPP_INDIE_STUDIO_GAME_HPP

namespace Bomberman
{
  class Game
  {
   private:
    Bomberman::Irrlicht &irr;

   public:
    Game();
    void run();
    ~Game();
  };
}

#endif //CPP_INDIE_STUDIO_GAME_HPP
