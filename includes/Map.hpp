//
// Created by cloquet on 28/05/16.
//

#ifndef				CPP_INDIE_STUDIO_MAP_HPP
#define				CPP_INDIE_STUDIO_MAP_HPP

#include			"Irrlicht.hpp"
#include			<random>
#include			<list>

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

    typedef std::list<std::pair<int, int>> t_Wall;

    t_Wall			_wallBreak;

   public:
    Map();

    ~Map();

    void 			createMap();
    irr::scene::IMeshSceneNode	*createBreakableWall();

   private:
    void createWall(int x, int y) const;
  };
}
#endif //CPP_INDIE_STUDIO_MAP_HPP
