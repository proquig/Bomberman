//
// Created by cloquet on 28/05/16.
//

#ifndef CPP_INDIE_STUDIO_OBJ_HPP
#define CPP_INDIE_STUDIO_OBJ_HPP

#include "IObj.hpp"

namespace Bomberman
{
  class Obj : public IObj
  {
   protected:
    Bomberman::Irrlicht 		&_irr;
    irr::scene::IMesh 			*_mesh;
    irr::scene::IMeshSceneNode 		*_node;

    irr::scene::IAnimatedMesh 		*_animated_mesh;
    irr::scene::IAnimatedMeshSceneNode 	*_animated_node;

    float				_x;
    float 				_y;
    irr::u32 				_explosion_time;

   public:
    template <typename T>
    static T*				create(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type)
    {
      return new T(mesh_path, texture_path, x, y, type);
    }
    Obj(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type);
    virtual ~Obj();
    //static Bomberman::IObj*		create(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type);
    float 				getX() const;
    float 				getY() const;
    irr::u32 				getExplosionTime() const;
  };
};

#endif //CPP_INDIE_STUDIO_OBJ_HPP
