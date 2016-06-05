//
// Created by cloquet on 24/05/16.
//

#ifndef						CPP_INDIE_STUDIO_GAME_HPP
# define					CPP_INDIE_STUDIO_GAME_HPP

# include					<Irrlicht.hpp>
# include					<map>
# include					<algorithm>
# include					"Map.hpp"

namespace					Bomberman
{
  class						Game
  {
   public:
    static const float				positions[][2];
    typedef					void (Game::*BonusMemFn)(Bomberman::Character *player, Bomberman::Obj *obj);
    static const std::map<Bomberman::TYPE, Bomberman::Game::BonusMemFn> _bonus;
   private:
    Bomberman::Irrlicht				&_irr;
    Bomberman::Map				*_map;
    size_t 					_nb_players;
    std::vector<Bomberman::Character*>		_players;
    static const std::map<irr::EKEY_CODE, std::pair<int, Bomberman::Character::ACTION>> _events[];
    static const std::vector<std::pair<std::string, std::pair<int, int>>> _players_conf;
    int 					_pause;

   public:
    Game(size_t, int);
    Game(const std::string &);
    ~Game();
    Bomberman::Map					*run();
    int							handleEvents();
    void						handleMovements();
    void						handleActions();
    void						handleTime();
    void						explodeObj(Obj *obj);
    void						explodeObjs(Bomb *bomb);
    bool 						getBonus(Bomberman::Character *player, Bomberman::Character::ACTION action);
    void						handleBonus();
    void						bonus_bomb_range(Bomberman::Character *player, Bomberman::Obj *obj);
    void						bonus_bomb_nb(Bomberman::Character *player, Bomberman::Obj *obj);
    void						bonus_god(Bomberman::Character *player, Bomberman::Obj *obj);
    void						bonus_speed(Bomberman::Character *player, Bomberman::Obj *obj);
    void						printWin();
    void						printLose();
  };
}

#endif						//CPP_INDIE_STUDIO_GAME_HPP
