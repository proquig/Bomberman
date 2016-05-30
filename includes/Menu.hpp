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
    typedef void (Menu::*ptr)();
    typedef std::map<irr::gui::IGUIButton *, ptr> button;


    Bomberman::Irrlicht &_irr;
    button		_button;
    irr::video::ITexture *_background;
    std::map<irr::gui::IGUIButton *, ptr> _action;

   public:
    Menu();
    Action run();
    ~Menu();
    void launchGame();
    void loadGame();
    void launchMulti();
    void launchOption();
    void quit();
    void displayCredit();
  };
}


#endif //CPP_INDIE_STUDIO_MENU_HPP
