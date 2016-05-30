//
// Created by cloquet on 28/05/16.
//

#ifndef CPP_INDIE_STUDIO_IOBJ_HPP
#define CPP_INDIE_STUDIO_IOBJ_HPP

#include "Irrlicht.hpp"
#include "xml/tinyxml2.h"

namespace Bomberman
{
  enum TYPE
    {
      BOX,
      BRICK,
      PLAN,
      BOMB,
      CHARACTER
    };
  class IObj
  {
   public:
    virtual ~IObj(){};
    virtual float 			getX() const = 0;
    virtual float 			getY() const = 0;
    virtual irr::u32 			getExplosionTime() const = 0;
    virtual void 			explode() = 0;
    virtual tinyxml2::XMLElement 	*serialize() = 0;
    virtual void deserialize(tinyxml2::XMLElement *element) = 0;
  };
};

#endif //CPP_INDIE_STUDIO_IOBJ_HPP
