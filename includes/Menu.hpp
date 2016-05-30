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
      OPTION,
      QUIT
    };
    enum
    {
      GUI_ID_QUIT_BUTTON = 101,
      GUI_ID_NEW_WINDOW_BUTTON,
      GUI_ID_FILE_OPEN_BUTTON,
      GUI_ID_TRANSPARENCY_SCROLL_BAR
    };

   private:
    typedef std::list<std::pair<irr::video::ITexture *, Action>> t_texture_list;
    typedef std::list<std::pair<irr::gui::IGUIButton *, Action>> button;

    Bomberman::Irrlicht &_irr;
    button		_button;
    irr::video::ITexture *_background;

   public:
    Menu();

    Action run();

    ~Menu();
  };
}


#endif //CPP_INDIE_STUDIO_MENU_HPP
