//
// Created by cloquet on 24/05/16.
//

#ifndef CPP_INDIE_STUDIO_MENU_HPP
#define CPP_INDIE_STUDIO_MENU_HPP

#include "Irrlicht.hpp"

#include <list>

class										Menu
{
 private:
  Bomberman::Irrlicht 								*irr;
  std::list<std::pair<irr::video::ITexture *, unsigned int  > >			texture;
  std::list<std::pair<irr::video::ITexture *, unsigned int  > >::iterator 	it;

 public:
  Menu();
  void		run();
  ~Menu();
};


#endif //CPP_INDIE_STUDIO_MENU_HPP
