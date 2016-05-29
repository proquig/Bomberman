//
// Created by cloquet on 28/05/16.
//

#ifndef CPP_INDIE_STUDIO_IOBJ_HPP
#define CPP_INDIE_STUDIO_IOBJ_HPP

#include "Irrlicht.hpp"

namespace Bomberman
{
  class IObj
  {
   public:
    virtual ~IObj();
    virtual Bomberman::IObj*		create() = 0;
    virtual float 			getX() const = 0;
    virtual float 			getY() const = 0;
    virtual void			explode() = 0;
  };
};

#endif //CPP_INDIE_STUDIO_IOBJ_HPP
