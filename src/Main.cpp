//
// Created by pogam-_g on 5/24/16.
//

#include <Menu.hpp>
#include "Main.hpp"
#include "Game.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
  new Bomberman::Main();
}

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
