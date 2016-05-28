//
// Created by cloquet on 28/05/16.
//

#ifndef CPP_INDIE_STUDIO_MAP_HPP
#define CPP_INDIE_STUDIO_MAP_HPP

#include "Irrlicht.hpp"

# define X 90
# define Y 70

namespace Bomberman
{
  class Map
  {
   private:
    Bomberman::Irrlicht &irr;
    irr::video::SMaterial _material;
    scene::IMeshSceneNode *_m_scene;
    scene::IMeshSceneNode *_wall;
    scene::ISceneNode *_scene;

   public:
    Map();
    void 			createMap();
    void 			creatBlock();
    scene::IMeshSceneNode 	*creatBreakBlock();
    ~Map()
    {
    }
  };
}
#endif //CPP_INDIE_STUDIO_MAP_HPP
