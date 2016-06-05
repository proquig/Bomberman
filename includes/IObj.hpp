//
// Created by cloquet on 28/05/16.
//

#ifndef CPP_INDIE_STUDIO_IOBJ_HPP
#define CPP_INDIE_STUDIO_IOBJ_HPP

#include "Irrlicht.hpp"

namespace Bomberman
{
  enum TYPE
    {
      BOX = 0,
      BRICK = 1,
      PLAN = 2,
      BOMB = 3,
      CHARACTER = 4,
      BONUS = 5,
      B_STAR = 6,
      B_BOMB_R = 7,
      B_BOMB_N = 8,
      B_BOOT = 9
    };

  class IObj
  {
   public:
    virtual ~IObj(){};
    virtual float 			getX() const = 0;
    virtual float 			getY() const = 0;
    virtual irr::u32 			getExplosionTime() const = 0;
    virtual Bomberman::TYPE		getType() const = 0;
    virtual bool 			isBlocking() const = 0;
    virtual bool 			isDestructible() const = 0;
    //virtual void			remove() const = 0;
    virtual void			die() = 0;
  };
};

#endif //CPP_INDIE_STUDIO_IOBJ_HPP
