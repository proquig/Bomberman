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

# define WINDOWSIZE_X 1920
# define WINDOWSIZE_Y 1080

Bomberman::Menu::Menu() : _irr(Bomberman::Irrlicht::instance())
{
  irr::gui::IGUISkin * skin = _irr.getGui()->getSkin();
  skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255,255,255,255));
  irr::gui::IGUIFont* font = _irr.getGui()->getFont("./assets/fonthaettenschweiler.bmp");
  if (font)
      skin->setFont(font);
  skin->setFont(_irr.getGui()->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
  _strings.push_back("New Game");
  _strings.push_back("New Game");


//TODO::Check si une save est la
/* Add Condition pour lui*/
  irr::gui::IGUIButton *button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100,WINDOWSIZE_Y / 2,
										    WINDOWSIZE_X / 2 + 100, WINDOWSIZE_Y / 2 + 32), 0, 0, L"Load Game", L"Opens a file");
      button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _action.insert(std::make_pair(button, &Menu::loadGame));
/**********************************************************************/


  for (std::vector<irr::core::stringw>::iterator i = _strings.begin(); i < _strings.end() ; ++i)
    {
      button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100, WINDOWSIZE_Y / 2 + 40,
								  WINDOWSIZE_X/ 2 + 100, WINDOWSIZE_Y / 2  + 40 + 32), 0, 0, L"Play New Game", 0);
      button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));

    }
  _action.insert(std::make_pair(button, &Menu::launchGame));
  button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100,WINDOWSIZE_Y / 2 + 80,
							      WINDOWSIZE_X / 2 + 100, WINDOWSIZE_Y / 2 + 80 + 32), 0, 0, L"2 Players",0);
  button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _action.insert(std::make_pair(button, &Menu::launchMulti));
  button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100, WINDOWSIZE_Y / 2 + 120,
							      WINDOWSIZE_X/ 2 + 100, WINDOWSIZE_Y / 2  + 120 + 32), 0, 0, L"Options", 0);
  button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _action.insert(std::make_pair(button, &Menu::launchOption));
  button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100,WINDOWSIZE_Y / 2 + 160,
							      WINDOWSIZE_X / 2 + 100, WINDOWSIZE_Y / 2 + 160 + 32), 0, 0, L"Exit", 0);
  button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _action.insert(std::make_pair(button, &Menu::quit));

  button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100,WINDOWSIZE_Y / 2 + 160,
							      WINDOWSIZE_X / 2 + 100, WINDOWSIZE_Y / 2 + 160 + 32), 0, 0, L"Credits", 0);
  button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _action.insert(std::make_pair(button, &Menu::displayCredit));

  _background = _irr.getDriver()->getTexture("./assets/Menu/Menu.png");

}

Bomberman::Menu::~Menu()
{

}


Bomberman::Menu::Action Bomberman::Menu::run()
{
  /*Bomberman::MusicManager &s = Bomberman::MusicManager::instance();
  s.setMusic("./assets/sound/menusong.flac");

  try
    {
      s.startMusic();
    }
  catch (exception e)
    {
      std::cerr << e.what() << std::endl;
    }
*/

while (_irr.getDevice()->run())
  {
/*u32 time = device->getTimer()->getTime();
    driver->draw2DImage(ITEXTUREHERE, position2d<s32>((driver->getScreenSize().Width - ITEXTUREHERE->getOriginalSize().Width)/2,
						      ((time/20)%(driver->getScreenSize().Height+ITEXTUREHERE->getOriginalSize().Height))
						      -ITEXTUREHERE->getOriginalSize().Height));*/
    for (button::iterator it = _action.begin(); it != _action.end(); ++it)
      if (it->first->isPressed())
	(this->*(it->second))();
    if (_irr.getDevice()->isWindowActive())
      {
	_irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 120, 102, 136));
	_irr.getDriver()->draw2DImage(_background, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
				      irr::core::rect<irr::s32>(0, 0, 1920, 1080));
	_irr.getGui()->drawAll();
	_irr.getDriver()->endScene();
      }
  }
  return QUIT;
}

void Bomberman::Menu::launchGame()
{
  this->_nb_player = 1;
  Game G(1);
  Bomberman::Save(G.run());
  _irr.getSmgr()->clear();
}

void Bomberman::Menu::loadGame()
{
  Game G("save.txt");
  Bomberman::Save(G.run());
  _irr.getSmgr()->clear();
}

void Bomberman::Menu::launchMulti()
{
  this->_nb_player = 2;

  Game G(2);
  Bomberman::Save(G.run());
  _irr.getSmgr()->clear();
}

void Bomberman::Menu::launchOption()
{
  //_irr.getGui()->addComboBox(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100, WINDOWSIZE_Y / 2 + 40, WINDOWSIZE_X/ 2 + 100, WINDOWSIZE_Y / 2  + 40 + 32));
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


