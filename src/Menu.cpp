//
// Created by cloquet on 24/05/16.
//

#include <zconf.h>
#include "Exception.hpp"
#include "Menu.hpp"
#include "sound/MusicManager.hpp"

Bomberman::Menu::Menu() : _irr(Bomberman::Irrlicht::instance())
{
  this->_texture.push_back(std::make_pair(_irr.getDriver()->getTexture("./assets/Menu/Gauntlet_Menu.png"), NEW_SINGLE_GAME));
  this->_texture.push_back(std::make_pair(_irr.getDriver()->getTexture("./assets/Menu/Gauntlet_Menu1.png"), LOAD_SINGLE_GAME));
  this->_texture.push_back(std::make_pair(_irr.getDriver()->getTexture("./assets/Menu/Gauntlet_Menu2.png"), MULTIPLAYER_GAME));
  this->_texture.push_back(std::make_pair(_irr.getDriver()->getTexture("./assets/Menu/Gauntlet_Menu3.png"), QUIT));
}

Bomberman::Menu::~Menu()
{

}

Bomberman::Menu::Action Bomberman::Menu::run()
{
  Bomberman::MusicManager &s = Bomberman::MusicManager::instance();
  s.setMusic("./assets/sound/menusong.flac");

  try
    {
      s.startMusic();
    }
  catch (exception e)
    {
      std::cerr << e.what() << std::endl;
    }

  t_texture_list::iterator it = _texture.begin();

  while (_irr.getDevice()->run())
    {
      usleep(100000);
      if (_irr.event.IsKeyDown(irr::KEY_UP))
	{
	  if (it == _texture.begin())
	    {
	      it = _texture.end();
	      it--;
	    }
	  else
	    it--;
	}
      else if (_irr.event.IsKeyDown(irr::KEY_DOWN))
	{
	  it++;
	  if (it == _texture.end()--)
	    it = _texture.begin();
	}

      if (_irr.event.IsKeyDown(irr::KEY_RETURN))
	return it->second;

      _irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 120, 102, 136));
      _irr.getDriver()->draw2DImage(it->first, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
				    irr::core::rect<irr::s32>(0, 0, 1920, 1080));
      _irr.getDriver()->endScene();
    }
  return QUIT;
}
