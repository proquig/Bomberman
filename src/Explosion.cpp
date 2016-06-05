//
// Created by cloquet
//

#include <zconf.h>
#include "Explosion.hpp"

Bomberman::Explosion::Explosion(float x, float y) : _irr(Bomberman::Irrlicht::instance()),
						    _x(x),
						    _y(y)
{

  this->node = this->_irr.getSmgr()->addMeshSceneNode(
	  this->_irr.getSmgr()->getMesh("./assets/Bomb/Blacksmith/Blacksmith.DAE"),
						       0, -1, irr::core::vector3df(this->_x, 1, this->_y),
						       irr::core::vector3df(0, 0 , 0),
						       irr::core::vector3df(1, 1, 1));
}

void 			Bomberman::Explosion::clear()
{
  node->remove();
}

Bomberman::Explosion::~Explosion()
{
}
