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

# define			MAPSIZE_X 120 * 5
# define			MAPSIZE_Y 80 * 5
# define			BLOCKSIZE 25
# define			WALLOBJ "./assets/Box/ItmBox01.dae"
# define			WALLTEXT "./assets/Box/ItmBox01_00.png"
# define			BOXOBJ "./assets/Box/ItmCarrierBox00.obj"
# define			BOXTEXT "./assets/Box/ItmCommonBoxB00.png"
# define			FLOORTEXT "./assets/Floor/grass2.jpg"

namespace			Bomberman
{
  class				Map
  {
   private:
    typedef Bomberman::Obj	*(Map::*ObjPtr)(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type);
    std::vector<Bomberman::Obj*> _objs;
    Bomberman::Irrlicht		&_irr;
    irr::video::SMaterial	_material;
    irr::scene::ISceneNode	*_scene;
    std::map<int, std::map<int, Bomberman::Obj*>>	_plan;

   public:
    Map();
    ~Map();
    bool			checkPosition(float x, float y, float range, bool all = false);
    void 			createMap();

    template <typename T>
    Obj		*create(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type)
    {
      return (new T(mesh_path, texture_path, x, y, type));
    }
    std::vector<Bomberman::Obj*>	getObjs() const;
    Bomberman::Obj		*createObj(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type);
    Bomberman::Obj		*createObjSomewhere(const std::string &mesh_path, const std::string &texture_path, Bomberman::TYPE type);
    bool			checkObjectPosition(Obj *obj, float x, float y, float range);
    std::map<int, std::map<int, Obj *>> getPlan() const;
    static int 			getRoundPosition(float axis);
    bool 			checkObjOnPlan(int x, int y);
    Bomberman::Obj*		getObjOnPlan(int x, int y);
    void			createPlan();
    //void			checkBonus(Bomberman::Character *player, Bomberman::Character::ACTION action);
  };
}
#endif //CPP_INDIE_STUDIO_MAP_HPP
