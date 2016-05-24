//
// Created by cloquet on 24/05/16.
//

#ifndef CPP_INDIE_STUDIO_MENU_HPP
#define CPP_INDIE_STUDIO_MENU_HPP

#include "Irrlicht.hpp"

#include <list>

namespace Bomberman
{
  class Menu
  {
   public:
    enum Action {
      NEW_SINGLE_GAME,
      LOAD_SINGLE_GAME,
      MULTIPLAYER_GAME,
      QUIT
    };

   private:
    typedef std::list<std::pair<irr::video::ITexture *, Action>> t_texture_list;

    Bomberman::Irrlicht &irr;
    t_texture_list texture;
    t_texture_list::iterator it;

   public:
    Menu();

    Action run();

    ~Menu();
  };
}


#endif //CPP_INDIE_STUDIO_MENU_HPP
