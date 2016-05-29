//
// Bomb.cpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio
// 
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
// 
// Started on  Sat May 28 16:07:06 2016 Guillaume PROQUIN
// Last update Sat May 28 19:37:34 2016 Guillaume PROQUIN
//

#include "Irrlicht.hpp"
#include "Bomb.hpp"

Bomberman::Bomb::Bomb() :
	Bomberman::Obj::Obj("./assets/Bomb/Bomb.obj", "./assets/Bomb/plasma-grenade.jpg", 0, 0, BOMB)

{
  this->_state = AWAITING;
  this->_animated_node->setVisible(false);
}

Bomberman::Bomb::~Bomb()
{
  //this->explosion();
  //this->_state = EXPLODED;
  //delete this->_animated_node;
  //delete this->_scene;
}

void		Bomberman::Bomb::reset()
{
  this->_state = AWAITING;
  this->_explosion_time = 0;
  this->_animated_node->setVisible(false);
}

void		Bomberman::Bomb::put(float x, float y)
{
  this->_x = x;
  this->_y = y;
  this->_animated_node->setPosition(irr::core::vector3df(this->_x, 0, this->_y));
  this->_animated_node->setVisible(true);
  this->_state = POSED;
  this->_explosion_time = (this->_irr.getDevice()->getTimer()->getTime() + 2000);
}

void		Bomberman::Bomb::explode()
{
  this->reset();
  //ANIMATION
  //HIDE
  //RESET
  this->_ps = this->_irr.getSmgr()->addParticleSystemSceneNode(false);
  this->_em = _ps->createBoxEmitter(irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7), irr::core::vector3df(0.0f,0.06f,0.0f), 80, 100, irr::video::SColor(0,255,255,255), irr::video::SColor(0,255,255,255), 800,2000,0, irr::core::dimension2df(10.f,10.f), irr::core::dimension2df(20.f,20.f));
  _ps->setEmitter(this->_em);
  _em->drop();

  irr::scene::IParticleAffector* paf = _ps->createFadeOutParticleAffector();

  _ps->addAffector(paf); // same goes for the affector
  paf->drop();

  _ps->setPosition(irr::core::vector3df(-70,60,40));
  _ps->setScale(irr::core::vector3df(2,2,2));
  _ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  _ps->setMaterialTexture(0, _irr.getDriver()->getTexture("./assets/Bomb/Explosion.jpg"));
  _ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
  
  std::cout << "Boom !" << std::endl;
}
