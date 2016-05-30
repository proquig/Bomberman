//
// Created by cloquet on 28/05/16.
//

#ifndef				CPP_INDIE_STUDIO_MAP_HPP
# define			CPP_INDIE_STUDIO_MAP_HPP

# include			"Irrlicht.hpp"
# include			"Obj.hpp"
# include			"Bomb.hpp"
# include			"Character.hpp"
# include			<random>
# include			<list>

# define			MAPSIZE_X 90
# define			MAPSIZE_Y 70

namespace			Bomberman
{
  class				Map
  {
   private:
//TODO::A voir avec BEN
/*
  template <typename T>
    typedef T (Map<T>::*ptr)(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type);
     template <typename T>
    T		create(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type)
    {
      return (new Obj(mesh_path, texture_path, x, y, type));
    }
    */
    typedef Bomberman::Obj		*(Map::*ptr)(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type);
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

    template <typename T>
    Obj		*create(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type)
    {
      return (new T(mesh_path, texture_path, x, y, type));
    }

    Bomberman::Obj		*createObj(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type);
    Bomberman::Obj		*createObjSomewhere(const std::string &mesh_path, const std::string &texture_path, Bomberman::TYPE type);
  };
}
#endif //CPP_INDIE_STUDIO_MAP_HPP
