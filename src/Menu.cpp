//
// Created by cloquet on 24/05/16.
//

#include <zconf.h>
#include "Menu.hpp"


Bomberman::Menu::Menu() : irr(Bomberman::Irrlicht::instance())
{
  this->texture.push_back(std::make_pair(irr.getDriver()->getTexture("../media/Menu/Gauntlet_Menu.png"), NEW_SINGLE_GAME));
  this->texture.push_back(std::make_pair(irr.getDriver()->getTexture("../media/Menu/Gauntlet_Menu1.png"), LOAD_SINGLE_GAME));
  this->texture.push_back(std::make_pair(irr.getDriver()->getTexture("../media/Menu/Gauntlet_Menu2.png"), MULTIPLAYER_GAME));
  this->texture.push_back(std::make_pair(irr.getDriver()->getTexture("../media/Menu/Gauntlet_Menu3.png"), QUIT));
  this->it = texture.begin();
}

Bomberman::Menu::~Menu()
{

}

Bomberman::Menu::Action Bomberman::Menu::run()
{
  while (irr.getDevice()->run())
    {
      usleep(100000);
      if (irr.event.IsKeyDown(irr::KEY_KEY_Z))
	{
	  if (it == texture.begin())
	    {
	      it = texture.end();
	      it--;
	    }
	  else
	    it--;
	}
      else if (irr.event.IsKeyDown(irr::KEY_KEY_S))
	{
	  it++;
	  if (it == texture.end()--)
	    it = texture.begin();
	}
      if (irr.event.IsKeyDown(irr::KEY_RETURN))
	return it->second;
      irr.getDriver()->beginScene(true, true, video::SColor(255, 120, 102, 136));
      irr.getDriver()->draw2DImage(it->first, core::rect<s32>(0, 0, 1920, 1080),
				   core::rect<s32>(0, 0, 1920, 1080));
      core::position2d<s32> m = irr.getDevice()->getCursorControl()->getPosition();
      irr.getDriver()->endScene();
    }
  irr.getDevice()->drop();
  return QUIT;
}
