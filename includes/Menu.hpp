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
   private:
    typedef std::list<std::pair<irr::video::ITexture *, unsigned int>> t_texture_list;

    Bomberman::Irrlicht &irr;
    t_texture_list texture;
    t_texture_list::iterator it;

   public:
    Menu();

    void run();

    ~Menu();
  };
}


#endif //CPP_INDIE_STUDIO_MENU_HPP
