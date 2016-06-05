//
// Created by pogam-_g on 6/1/16.
//

#ifndef CPP_INDIE_STUDIO_IA_HPP
#define CPP_INDIE_STUDIO_IA_HPP

#include "lua.hpp"
#include <Selene/selene.h>
#include "Character.hpp"
#include "Map.hpp"

namespace Bomberman
{
  class IA
  {
    Character	*_character;
    Map		*_map;
    std::thread	*_thread;
    bool	_dead;

   public:
    IA(Map *map, Character *character);

    virtual ~IA();

    void initIA();

    void die();

    std::string getCaseContent(int x, int y);

    static int getMapXSize();

    static int getMapYSize();

    int getBlockSize();

    bool move(const std::string &direction);

    bool move_top();

    bool move_bottom();

    bool move_left();

    bool move_right();

    int getX();

    int getY();

    int getRoundPosition(int i);

    void putBomb();

    bool isBlocked(int x, int y);
  };
}

#endif //CPP_INDIE_STUDIO_IA_HPP
