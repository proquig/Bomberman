//
// Created by pogam-_g on 6/1/16.
//

#ifndef CPP_INDIE_STUDIO_IA_HPP
#define CPP_INDIE_STUDIO_IA_HPP

#include <lua.hpp>
#include <Selene/selene.h>
#include "Character.hpp"
#include "Map.hpp"

namespace Bomberman
{
  class IA
  {
    Character *_character;
    Map *_map;
    std::thread *_thread;
    bool _dead;

   public:
    IA(Map *map, Character *character);

    virtual ~IA();

    void initIA();

    void die();

    std::string getCaseContent(int x, int y);

    static int getMapXSize();

    static int getMapYSize();

    void move(std::string direction = "LEFT");

    void putBomb();
  };
}

#endif //CPP_INDIE_STUDIO_IA_HPP
