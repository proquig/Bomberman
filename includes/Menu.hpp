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
      QUIT
    };

   private:
    typedef void (Menu::*ptr)();

    Bomberman::Irrlicht &					_irr;
    std::vector<std::pair<irr::video::ITexture *, ptr> >	_button;
    std::vector<std::pair<irr::video::ITexture *, ptr> > 	_options;
    Bomberman::MusicManager					&_music;
    int 							_sound;
    int 							_size_map;

    void							launchGame();
    void							loadGame();
    void							launchMulti();
    void							launchOption();
    void							quit();
    void							setSound();
    void							nothing(){};
    void							displayCredit();

   public:
    Menu();
    ~Menu();
    void							intro();
    void							setMenu();
    void							splash();
    Action							run();
  };
}


#endif //CPP_INDIE_STUDIO_MENU_HPP
