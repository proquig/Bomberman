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
    Bomberman::Irrlicht		&_irr;
    irr::video::SMaterial	_material;
    irr::scene::IMeshSceneNode	*_meshScene;
    irr::scene::ISceneNode	*_scene;

   public:
    Map();

    ~Map();

    void 			createMap();
    irr::scene::IMeshSceneNode	*createBreakableWall(int x, int y) const;

   private:
    void createWall(int x, int y) const;
  };
}
#endif //CPP_INDIE_STUDIO_MAP_HPP
