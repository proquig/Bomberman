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
    float 				getX() const;
    float 				getY() const;
    void				explode();
  };
};

#endif //CPP_INDIE_STUDIO_IOBJ_HPP
