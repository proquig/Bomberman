//
// Created by pogam-_g on 5/24/16.
//

#include <Menu.hpp>
#include "Main.hpp"
#include "Game.hpp"

Bomberman::Main::Main() : _irrlicht(Irrlicht::instance())
{
  Menu menu;

  menu.intro();
  menu.setMenu();
  Bomberman::Menu::Action action = menu.run();
}

Bomberman::Main::~Main()
{

}
