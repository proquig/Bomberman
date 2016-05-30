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
   public:
    static const float				positions[][2];
   private:
    Bomberman::Irrlicht				&_irr;
    Bomberman::Map				*_map;
    size_t 					_nbPlayer;
    std::vector<Bomberman::Character*>		_players;
    static const std::map<irr::EKEY_CODE, std::pair<int, Bomberman::Character::ACTION>> _events[];

   public:
    Game(size_t);
    ~Game();
    void					run();

    void handleEvents();

    void handleMovements();

    void handleActions();

    void handleTime();

  };
}

#endif						//CPP_INDIE_STUDIO_GAME_HPP
