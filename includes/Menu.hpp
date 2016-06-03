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

   private:
    typedef void (Menu::*ptr)();
    typedef std::map<irr::gui::IGUIButton *, ptr> button;


    Bomberman::Irrlicht &					_irr;
    std::vector<std::pair<irr::video::ITexture *, ptr> >	_button;
    irr::video::ITexture 					*_background;
    std::map<irr::gui::IGUIButton *, ptr> 			_action;
    std::vector<irr::core::stringw>  				_strings;
    int 							_nb_player;

   public:
    Menu();

    void intro();
    void setMenu();
    void splash();
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
