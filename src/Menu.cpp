//
// Created by cloquet on 24/05/16.
//

#include <zconf.h>
#include "Menu.hpp"


Menu::Menu()
	:irr()
{
  this->texture.push_back(std::make_pair(irr->getDriver()->getTexture("../media/Menu/Gauntlet_Menu1.png"), 0));
  this->texture.push_back(std::make_pair(irr->getDriver()->getTexture("../media/Menu/Gauntlet_Menu2.png"), 1));
  this->texture.push_back(std::make_pair(irr->getDriver()->getTexture("../media/Menu/Gauntlet_Menu3.png"), 2));
  this->it = texture.begin();
}

Menu::~Menu()
{

}

void		Menu::run()
{
  while (irr->getDevice()->run())
    {
      usleep(100000);
      if (irr->event.IsKeyDown(irr::KEY_KEY_Z))
	{
	  if (it == texture.begin())
	    {
	      it = texture.end();
	      it--;
	    }
	  else
	    it--;
	}
      else if (irr->event.IsKeyDown(irr::KEY_KEY_S))
	{
	  it++;
	  if (it == texture.end()--)
	    it = texture.begin();
	}
      irr->getDriver()->beginScene(true, true, video::SColor(255, 120, 102, 136));
      irr->getDriver()->draw2DImage(it->first, core::rect<s32>(0, 0, 1920, 1080),
			  core::rect<s32>(0, 0, 1920, 1080));
      core::position2d <s32> m = irr->getDevice()->getCursorControl()->getPosition();
      irr->getDriver()->endScene();
    }
  irr->getDevice()->drop();
}