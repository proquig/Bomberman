//
// Created by cloquet on 28/05/16.
//

#ifndef CPP_INDIE_STUDIO_OBJ_HPP
#define CPP_INDIE_STUDIO_OBJ_HPP

#include <xml/tinyxml2.h>
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

    Bomberman::TYPE 			_type;
    float				_x;
    float 				_y;
    irr::u32 				_explosion_time;
    irr::u32 				_animation_time;
    bool 				_is_blockable;
    bool 				_is_destructible;

   public:
    Obj(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type);
    virtual ~Obj();
    Bomberman::TYPE 			getType() const;
    float 				getX() const;
    float 				getY() const;
    irr::u32 				getExplosionTime() const;
    irr::u32 				getAnimation_time() const;
    bool				isBlockable() const;
    bool 				isDestructible() const;
    void				remove();
    void				reset();


    virtual tinyxml2::XMLElement	*serialize() override;

    virtual void deserialize(tinyxml2::XMLElement *element) override;
  };
};

#endif //CPP_INDIE_STUDIO_OBJ_HPP
