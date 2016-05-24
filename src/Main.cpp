//
// Created by pogam-_g on 5/24/16.
//

#include <Menu.hpp>
#include "Main.hpp"

Bomberman::Main::Main() : _irrlicht(Irrlicht::instance())
{
  Menu menu;
  menu.run();
}

Bomberman::Main::~Main()
{

}
