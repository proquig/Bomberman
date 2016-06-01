//
// Created by pogam-_g on 5/24/16.
//

#include <Menu.hpp>
#include "Main.hpp"
#include "Game.hpp"

Bomberman::Main::Main() : _irrlicht(Irrlicht::instance())
{
  Menu menu;

  Bomberman::Menu::Action action = menu.run();
  if (action == Bomberman::Menu::NEW_SINGLE_GAME)
    {
      Game G(1);
      G.run();

    }
  if (action == Bomberman::Menu::MULTIPLAYER_GAME)
    {
      Game G(2);
      G.run();
    }
  if (action == Bomberman::Menu::OPTION)
    {
      _irrlicht.getDevice()->drop();
    }
  if (action == Bomberman::Menu::QUIT)
    {
      _irrlicht.getDevice()->drop();
    }
}

Bomberman::Main::~Main()
{

}
