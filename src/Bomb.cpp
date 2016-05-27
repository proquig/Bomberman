//
// Created by joris_a
//


#include "Irrlicht.hpp"
#include "Bomb.hpp"

Bomb::Bomb() {
  this->_state = AWAITING;
}

Bomb::Bomb(int pX, int pY) {
  
  this->_mesh = "media/bomb.3ds";
  this->_state = POSED;
  this->_px = pX;
  this->_py = pY;
}

Bomb::~Bomb() {
  this->explosion();
  this->_state = EXPLODED;
}

void		Bomb::explosion() {
  std::cout << "Boom !" << std::endl;
}

void		Bomb::setState(Bomb::state const& c) {
  this->_state = c;
}

std::string	Bomb::getMesh() const {
  return (_mesh);
}
