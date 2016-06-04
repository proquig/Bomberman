//
// Created by cloquet on 24/05/16.
//

#ifndef CPP_INDIE_STUDIO_MENU_HPP
#define CPP_INDIE_STUDIO_MENU_HPP

#include "Irrlicht.hpp"

#include <list>
#include <sound/MusicManager.hpp>

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
    std::vector<std::pair<irr::video::ITexture *, ptr> > 	_options;

    Bomberman::MusicManager					&_music;
    int 							_sound;
    int 							_size_map;

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

    void setSound();

    void displayCredit();
  };
}


#endif //CPP_INDIE_STUDIO_MENU_HPP
