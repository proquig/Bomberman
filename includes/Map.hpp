//
// Created by cloquet on 28/05/16.
//

#ifndef				CPP_INDIE_STUDIO_MAP_HPP
# define			CPP_INDIE_STUDIO_MAP_HPP

# include			"Irrlicht.hpp"
# include			"Obj.hpp"
# include			<random>
# include			<list>

# define			MAPSIZE_X 90
# define			MAPSIZE_Y 70

namespace			Bomberman
{
  class				Map
  {
   private:
    std::vector<Bomberman::Obj *> _objs;
    Bomberman::Irrlicht		&_irr;
    irr::video::SMaterial	_material;
    irr::scene::ISceneNode	*_scene;
    typedef std::list<std::pair<int, int>> t_Wall;
    t_Wall			_wallBreak;

   public:
    Map();
    ~Map();
    bool			checkPosition(float x, float y, float range);
    void 			createMap();
    Bomberman::Obj 		*putObjSomewhere(Bomberman::Obj::TYPE type);
    Bomberman::Obj		*putObj(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::Obj::TYPE type);

   private:
    void			createWall(int x, int y);

  };
}
#endif //CPP_INDIE_STUDIO_MAP_HPP
