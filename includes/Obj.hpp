//
// Created by cloquet on 28/05/16.
//

#ifndef CPP_INDIE_STUDIO_OBJ_HPP
#define CPP_INDIE_STUDIO_OBJ_HPP

#include <sound/MusicManager.hpp>
#include "IObj.hpp"

namespace Bomberman
{
  class Obj : public IObj
  {
   protected:
    typedef void			(Obj::*ObjMemFn)();
    Bomberman::Irrlicht 		&_irr;
    irr::scene::IMesh 			*_mesh;
    irr::scene::IMeshSceneNode 		*_node;
    Bomberman::MusicManager		&_sound;
    irr::scene::IAnimatedMesh 		*_animated_mesh;
    irr::scene::IAnimatedMeshSceneNode 	*_animated_node;
    Bomberman::TYPE 			_type;
    float				_x;
    float 				_y;
    irr::u32 				_explosion_time;
    irr::u32 				_animation_time;
    bool 				_is_blocking;
    bool 				_is_destructible;
    std::string				_mesh_path;
    std::string				_texture_path;

   public:
    Obj(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type);
    virtual ~Obj();
    Bomberman::TYPE 			getType() const;
    float 				getX() const;
    float 				getY() const;
    std::string				getMeshName() const;
    std::string				getTextureName() const;
    irr::u32 				getExplosionTime() const;
    irr::u32 				getAnimation_time() const;
    bool				isBlocking() const;
    bool 				isDestructible() const;
    void				remove();
    //void				reset();
    virtual void die()			override;
    int 				_dead;

   private:
    void				createBrick();
    void				createBox();
    void				createPlan();
    void				createCharacter();
    void				createBomb();
    void				createBonus();
  };
};

#endif //CPP_INDIE_STUDIO_OBJ_HPP
