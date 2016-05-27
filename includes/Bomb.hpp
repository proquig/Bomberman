//
// Created by joris_a
//

#include "Irrlicht.hpp"


class		Bomb {
public:
  Bomb();
  ~Bomb();
  std::string getMesh() const;
  
private:
  std::string _mesh;
};
