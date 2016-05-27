#include "Irrlicht.hpp"
#include "Bomb.hpp"

Bomb::Bomb() {
  _mesh = "media/bomb.3ds";
}

Bomb::~Bomb() {
  std::cout << "Boom!" << std::endl;
}

std::string Bomb::getMesh() const {
  return (_mesh);
}
