//
// Created by cloquet on 24/05/16.
//

#ifndef						CPP_INDIE_STUDIO_GAME_HPP
# define					CPP_INDIE_STUDIO_GAME_HPP

# include					<Irrlicht.hpp>
# include					<map>
# include					"Map.hpp"

namespace					Bomberman
{
  class						Game
  {
   private:
    Bomberman::Irrlicht				&_irr;
    Bomberman::Map				*_map;
    size_t 					_nbPlayer;

   public:
    Game(size_t);
    ~Game();
    void					run();
  };
}

#endif						//CPP_INDIE_STUDIO_GAME_HPP
