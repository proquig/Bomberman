//
// Created by cloquet on 24/05/16.
//

#include <zconf.h>
#include "Exception.hpp"
#include "Menu.hpp"
#include "sound/MusicManager.hpp"
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
//TODO::Check si une save est la
/* Add Condition pour lui*/
  irr::gui::IGUIButton *button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100,WINDOWSIZE_Y / 2,
										    WINDOWSIZE_X / 2 + 100, WINDOWSIZE_Y / 2 + 32), 0,
							  Menu::GUI_ID_NEW_WINDOW_BUTTON, L"Load Game", L"Opens a file");
      button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _action.insert(std::make_pair(button, &Menu::loadGame));
/**********************************************************************/
  button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100, WINDOWSIZE_Y / 2 + 40,
							      WINDOWSIZE_X/ 2 + 100, WINDOWSIZE_Y / 2  + 40 + 32), 0, Menu::GUI_ID_QUIT_BUTTON, L"Play New Game", 0);
  button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _action.insert(std::make_pair(button, &Menu::launchGame));
  button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100,WINDOWSIZE_Y / 2 + 80,
							      WINDOWSIZE_X / 2 + 100, WINDOWSIZE_Y / 2 + 80 + 32), 0, Menu::GUI_ID_FILE_OPEN_BUTTON, L"2 Players",0);
  button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _action.insert(std::make_pair(button, &Menu::launchMulti));
  button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100, WINDOWSIZE_Y / 2 + 120,
							      WINDOWSIZE_X/ 2 + 100, WINDOWSIZE_Y / 2  + 120 + 32), 0, Menu::GUI_ID_QUIT_BUTTON, L"Options", 0);
  button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _action.insert(std::make_pair(button, &Menu::launchOption));
  button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100,WINDOWSIZE_Y / 2 + 160,
							      WINDOWSIZE_X / 2 + 100, WINDOWSIZE_Y / 2 + 160 + 32), 0, Menu::GUI_ID_FILE_OPEN_BUTTON, L"Exit", 0);
  button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _action.insert(std::make_pair(button, &Menu::quit));

  button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100,WINDOWSIZE_Y / 2 + 160,
							      WINDOWSIZE_X / 2 + 100, WINDOWSIZE_Y / 2 + 160 + 32), 0, Menu::GUI_ID_FILE_OPEN_BUTTON, L"Credits", 0);
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
  Game G(1);
  G.run();
}

void Bomberman::Menu::loadGame()
{
  Game G(1);
  G.run();
}

void Bomberman::Menu::launchMulti()
{
  Game G(2);
  G.run();
}

void Bomberman::Menu::launchOption()
{
  _irr.getDevice()->drop();
}

void Bomberman::Menu::displayCredit()
{
  std::vector<std::string> v ={
	  {"proqui_g"},
	  {"cloque_b"}
  };
}

void Bomberman::Menu::quit()
{
  exit(0);
}
