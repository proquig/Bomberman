//
// Created by cloquet on 24/05/16.
//

#include <zconf.h>
#include "Exception.hpp"
#include "Menu.hpp"
#include "sound/MusicManager.hpp"
#include "Save.hpp"
#include <IGUIButton.h>
#include <Game.hpp>
#include <sstream>

# define WINDOWSIZE_X 1920
# define WINDOWSIZE_Y 1080

Bomberman::Menu::~Menu()
{

}

Bomberman::Menu::Menu() : _irr(Bomberman::Irrlicht::instance()),
			  _music(Bomberman::MusicManager::instance())
{
  this->_sound = 1;
}

void 	Bomberman::Menu::splash()
{
  irr::video::ITexture *back = _irr.getDriver()->getTexture("./assets/Menu/splash.png");
  _irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
  _irr.getDriver()->draw2DImage(back, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
				irr::core::rect<irr::s32>(0, 0, 1920, 1080));
  _irr.getDriver()->endScene();
  sleep(1);
}

void	Bomberman::Menu::intro()
{
  int 	i = 0;
  int 	y = 0;
  int 	j = 0;
  Bomberman::MusicManager &s = Bomberman::MusicManager::instance();
  s.setMusic("./assets/sound/game.mp3");
  try
    {
      s.startMusic();
    }
  catch (exception e)
    {
      std::cerr << e.what() << std::endl;
    }
  irr::video::ITexture *back = _irr.getDriver()->getTexture("./assets/Menu/intro.png");
  irr::video::ITexture *head = _irr.getDriver()->getTexture("./assets/Menu/head.png");
  irr::video::ITexture *titre = _irr.getDriver()->getTexture("./assets/Menu/Bomberman_Logo.png");

  while (_irr.getDevice()->run() && i != 1000)
    {
      _irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
      _irr.getDriver()->draw2DImage(back, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
				    irr::core::rect<irr::s32>(0, 0, 1920, 1080));
      _irr.getDriver()->draw2DImage(head, irr::core::rect<irr::s32>(y, y, i, i),
				    irr::core::rect<irr::s32>(y, y, i, i), 0, 0, true);
      _irr.getDriver()->draw2DImage(titre, irr::core::rect<irr::s32>(1920 / 2, j / 2,
								     1920 / 2 + 247, j / 2 + 63),
				    irr::core::rect<irr::s32>(0, 0, 247, 63), 0, 0, true);

      _irr.getDriver()->endScene();
      j += 4;
      if (i / 500 != 1)
	i += 4;
      else
	{
	  y += 4;
	  i += 4;
	}
      if (_irr.event.IsKeyDown(irr::KEY_SPACE))
	i = 1000;
    }
}

void Bomberman::Menu::setMenu()
{
  _button.push_back(std::make_pair(_irr.getDriver()->getTexture("./assets/Menu/NewMenu.png"), &Menu::launchGame));
  _button.push_back(std::make_pair(_irr.getDriver()->getTexture("./assets/Menu/MultiMenu.png"), &Menu::launchMulti));
  _button.push_back(std::make_pair(_irr.getDriver()->getTexture("./assets/Menu/LoadMenu.png"), &Menu::loadGame));
  _button.push_back(std::make_pair(_irr.getDriver()->getTexture("./assets/Menu/OptionsMenu.png"), &Menu::launchOption));
  _button.push_back(std::make_pair(_irr.getDriver()->getTexture("./assets/Menu/ExitMenu.png"), &Menu::quit));

  _options.push_back(std::make_pair(_irr.getDriver()->getTexture("./assets/Menu/Options1.png"), &Menu::setSound));
  _options.push_back(std::make_pair(_irr.getDriver()->getTexture("./assets/Menu/Options2.png"), &Menu::setSound));
  _options.push_back(std::make_pair(_irr.getDriver()->getTexture("./assets/Menu/Options4.png"), &Menu::quit));
  _options.push_back(std::make_pair(_irr.getDriver()->getTexture("./assets/Menu/Options 3.png"), &Menu::quit));
}

Bomberman::Menu::Action Bomberman::Menu::run()
{
  int i = 0;
  while (_irr.getDevice()->run())
    {
      usleep(90000);
      if (_irr.getDevice()->isWindowActive())
      {
	  _irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 120, 102, 136));
	  if (_irr.event.IsKeyDown(irr::KEY_DOWN))
	    i = (i + 1) % (int)_button.size();
	  else if (_irr.event.IsKeyDown(irr::KEY_UP))
	    i = (int) ((((i - 1) < 0) ? (_button.size() - 1) : (i - 1)) % (int)_button.size());
	  if (_irr.event.IsKeyDown(irr::KEY_RETURN))
	    (this->*_button[i].second)();

	  _irr.getDriver()->draw2DImage(_button[i].first, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
				      irr::core::rect<irr::s32>(0, 0, 1920, 1080));
	_irr.getDriver()->endScene();
      }
  }
  return QUIT;
}

void Bomberman::Menu::launchGame()
{
  this->_nb_player = 1;
  this->splash();
  Game G(1);
  Bomberman::Save(G.run());
  _irr.getSmgr()->clear();
}

void Bomberman::Menu::loadGame()
{
  this->splash();
  try {
      Game G("save.txt");
      Bomberman::Save(G.run());
      _irr.getSmgr()->clear();
  }catch(exception &e) {
    e.what();
  }
}

void Bomberman::Menu::launchMulti()
{
  this->splash();
  Game G(2);
  Bomberman::Save(G.run());
  _irr.getSmgr()->clear();
}

void Bomberman::Menu::launchOption()
{
  int i = 0;
  int x = 184;
  std::ostringstream str;

  irr::gui::IGUIFont *font = _irr.getGui()->getFont("./assets/myfont.xml");
  _irr.getGui()->getSkin()->setFont(font);

  while (_irr.getDevice()->run())
    {
      usleep(90000);
      str.str("");
      str << "<" << x << ">";
      if (_irr.getDevice()->isWindowActive())
	{
	  _irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 120, 102, 136));
	  if (_irr.event.IsKeyDown(irr::KEY_RIGHT) && i == 2)
	    x = (x + 1) > 200 ? 0 : x + 1;
	  if (_irr.event.IsKeyDown(irr::KEY_LEFT) && i == 2)
	    x = (x - 1) < 0 ? 200 : x - 1;

	  if (_irr.event.IsKeyDown(irr::KEY_DOWN))
	    i = (i + 1) % (int)_options.size();
	  else if (_irr.event.IsKeyDown(irr::KEY_UP))
	    i = (int) ((((i - 1) < 0) ? (_options.size() - 1) : (i - 1)) % (int)_options.size());

	  if (_irr.event.IsKeyDown(irr::KEY_RETURN))
	    (this->*_options[i].second)();
	  if (_irr.event.IsKeyDown(irr::KEY_ESCAPE))
	    return;
	  _irr.getDriver()->draw2DImage(_options[i].first, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
					irr::core::rect<irr::s32>(0, 0, 1920, 1080));
	  font->draw(str.str().c_str(), irr::core::rect<irr::s32>(1920 / 2 + 900, 1080 / 2 + 300,
								  1920 / 2, 1080 / 2),
		     irr::video::SColor(255, 255, 255, 255),
		     true, true);
	  _irr.getGui()->drawAll();
	  _irr.getDriver()->endScene();
	}
    }
}


void Bomberman::Menu::setSound()
{
  _sound = !_sound;
  _sound ? _music.startMusic() : _music.pauseMusic();
}

void Bomberman::Menu::displayCredit()
{
  std::vector<irr::core::stringw> v ={
	  {"proqui_g"},
	  {"cloque_b"}
  };

  int x = 100;
  int y = 20;
  for (std::vector<irr::core::stringw>::iterator it = v.begin(); it != v.end(); ++it)
      _irr.getGui()->addStaticText(it->c_str(), irr::core::rect<irr::s32>(x += 100, y += 20, 300, 60));
}

void Bomberman::Menu::quit()
{
  exit(0);
}


