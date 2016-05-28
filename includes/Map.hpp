//
// Created by cloquet on 28/05/16.
//

#ifndef				CPP_INDIE_STUDIO_MAP_HPP
#define				CPP_INDIE_STUDIO_MAP_HPP

#include			"Irrlicht.hpp"

# define			X 90
# define			Y 70

namespace			Bomberman
{
  class				Map
  {
   private:
    Bomberman::Irrlicht		&irr;
    irr::video::SMaterial	_material;
    irr::scene::IMeshSceneNode	*_m_scene;
    irr::scene::IMeshSceneNode	*_wall;
    irr::scene::ISceneNode	*_scene;

   public:
    Map();
    void 			createMap();
    void 			creatBlock();
    irr::scene::IMeshSceneNode 	*creatBreakBlock();
    ~Map();
  };
}
#endif //CPP_INDIE_STUDIO_MAP_HPP
