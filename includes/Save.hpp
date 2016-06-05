//
// Created by cloquet on 01/06/16.
//

#ifndef CPP_INDIE_STUDIO_SAVE_HPP
#define CPP_INDIE_STUDIO_SAVE_HPP

#include "Obj.hpp"
#include "Map.hpp"

namespace Bomberman
{
  class Save
  {
   private:
    std::string _name;

   public:
    Save(Bomberman::Map *);
    ~Save();
  };
}
#endif //CPP_INDIE_STUDIO_SAVE_HPP
