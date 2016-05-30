//
// Created by cloquet on 24/05/16.
//

#include <zconf.h>
#include "Exception.hpp"
#include "Menu.hpp"
#include "sound/MusicManager.hpp"
#include <IGUIButton.h>
# define WINDOWSIZE_X 1920
# define WINDOWSIZE_Y 1080

Bomberman::Menu::Menu() : _irr(Bomberman::Irrlicht::instance())
{
  irr::gui::IGUISkin * skin = _irr.getGui()->getSkin();

  skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255,255,255,255));

  irr::gui::IGUIFont* font = _irr.getGui()->getFont("./assets/fonthaettenschweiler.bmp");

  if (font)
    {
      skin->setFont(font);
    }
  skin->setFont(_irr.getGui()->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);

/* Add Condition pour lui
  */
  irr::gui::IGUIButton *button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100,WINDOWSIZE_Y / 2, WINDOWSIZE_X / 2 + 100, WINDOWSIZE_Y / 2 + 32), 0,
							  Menu::GUI_ID_NEW_WINDOW_BUTTON, L"Load Game", L"Opens a file");
      button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _button.push_back(std::make_pair(button, Menu::LOAD_SINGLE_GAME));

  button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100, WINDOWSIZE_Y / 2 + 40, WINDOWSIZE_X/ 2 + 100, WINDOWSIZE_Y / 2  + 40 + 32), 0,
							  Menu::GUI_ID_QUIT_BUTTON, L"Play New Game", 0);
  button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _button.push_back(std::make_pair(button, Menu::NEW_SINGLE_GAME));

  button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100,WINDOWSIZE_Y / 2 + 80, WINDOWSIZE_X / 2 + 100, WINDOWSIZE_Y / 2 + 80 + 32), 0, Menu::GUI_ID_FILE_OPEN_BUTTON,
			   L"2 Players",0);
  button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _button.push_back(std::make_pair(button, Menu::MULTIPLAYER_GAME));

  button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100, WINDOWSIZE_Y / 2 + 120, WINDOWSIZE_X/ 2 + 100, WINDOWSIZE_Y / 2  + 120 + 32), 0, Menu::GUI_ID_QUIT_BUTTON,
			  L"Options", 0);
  button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _button.push_back(std::make_pair(button, Menu::OPTION));

  button = _irr.getGui()->addButton(irr::core::rect<irr::s32>(WINDOWSIZE_X / 2 - 100,WINDOWSIZE_Y / 2 + 160, WINDOWSIZE_X / 2 + 100, WINDOWSIZE_Y / 2 + 160 + 32), 0, Menu::GUI_ID_FILE_OPEN_BUTTON,
			   L"Exit", 0);
  button->setImage(_irr.getDriver()->getTexture("./assets/Menu/color.jpg"));
  _button.push_back(std::make_pair(button, Menu::QUIT));

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
    for (button::iterator it = _button.begin(); it != _button.end(); ++it)
      {
	if (it->first->isPressed())
	  return(it->second);
      }
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
