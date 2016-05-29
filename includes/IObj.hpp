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
      BOX,
      BRICK,
      PLAN,
      BOMB,
      CHARACTER
    };
  class IObj
  {
   public:
    virtual ~IObj();
    virtual Bomberman::IObj*		create(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type) = 0;
    virtual float 			getX() const = 0;
    virtual float 			getY() const = 0;
    virtual void			explode() = 0;
  };
};

#endif //CPP_INDIE_STUDIO_IOBJ_HPP
