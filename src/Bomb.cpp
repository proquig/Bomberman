//
// Created by joris_a
//


#include "Irrlicht.hpp"
#include "Bomb.hpp"

Bomberman::Bomb::Bomb() : _irr(Bomberman::Irrlicht::instance())
{
  this->_state = AWAITING;
}

Bomberman::Bomb::Bomb(int pX, int pY) : _irr(Bomberman::Irrlicht::instance())
{
  this->_bomb = this->_irr.getSmgr()->getMesh("./assets/Bomb/Bomb.obj");
  this->_scene = this->_irr.getSmgr()->addAnimatedMeshSceneNode(this->_bomb, 0, -1, core::vector3df(pX, 0, pY),
								    core::vector3df(0, 0, 0),
								    core::vector3df(1.025f, 1.025f, 1.025f));
  this->_scene->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
  this->_scene->setMD2Animation(scene::EMAT_STAND);
  this->_scene->setMaterialTexture(0, this->_irr.getDriver()->getTexture("./assets/ninja/nskinrd.jpg"));
  this->_state = POSED;
  this->_px = pX;
  this->_py = pY;
}

Bomberman::Bomb::~Bomb()
{
  this->explosion();
  this->_state = EXPLODED;
}

void                Bomberman::Bomb::explosion()
{
  std::cout << "Boom !" << std::endl;
}

void                Bomberman::Bomb::setState(Bomberman::Bomb::state const &c)
{
  this->_state = c;
}

