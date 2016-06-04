//
// Created by joris_a
//

#include <zconf.h>
#include "Explosion.hpp"

Bomberman::Explosion::Explosion(float x, float y) : _irr(Bomberman::Irrlicht::instance()),
						    _x(x),
						    _y(y)
{
  std::cout << "B2!" << std::endl;
  this->getScene();
}


void 			Bomberman::Explosion::getScene()
{
  irr::video::ITexture *titre = _irr.getDriver()->getTexture("./assets/Bomb/Explosion.jpg");

  _irr.getDriver()->draw2DImage(titre, irr::core::rect<irr::s32>(_x - 10, _y - 5,
								 _x + 10, _y + 5),
				irr::core::rect<irr::s32>(_x - 10, _y - 5, _x + 10, _y + 5), 0, 0, true);
  //this->_ps = this->_irr.getSmgr()->addParticleSystemSceneNode(false);
  //  this->_em = _ps->createBoxEmitter(irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7),
  //				    irr::core::vector3df(0.0f,0.0f,0.0f), 10, 50,
  //				    irr::video::SColor(0,255,255,255),	\
  //				    irr::video::SColor(0,255,255,255), 800, 2000, 0,
  //				    irr::core::dimension2df(1.f,1.f), irr::core::dimension2df(2.f,2.f));
  //  _ps->setEmitter(this->_em);
  //  _em->drop();
  //  _paf = _ps->createFadeOutParticleAffector();
  //  _ps->addAffector(_paf);
  //  _paf->drop();
  //  _ps->setPosition(irr::core::vector3df(this->_x, 0, this->_y));
  //  _ps->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
  //  _ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  //  _ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  //  _ps->setMaterialTexture(0, _irr.getDriver()->getTexture("./assets/Bomb/Explosion.jpg"));
  //  _ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
  std::cout << "Boom !" << std::endl;
}

Bomberman::Explosion::~Explosion()
{
}
