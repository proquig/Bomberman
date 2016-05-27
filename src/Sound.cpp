//
// Created by cloquet on 25/05/16.
//

#include "Sound.hpp"

Bomberman::Sound::Sound() : irr(Bomberman::Irrlicht::instance())
{
  this->_engine = irrklang::createIrrKlangDevice();

  if (this->_engine == nullptr)
    return;

  irrklang::ISound *music = this->_engine->play3D("./assets/sound/menusong.flac", irrklang::vec3df(0, 0, 0),
						  true, false, true);

  if (music == nullptr)
    return;

  music->setMinDistance(5.0f);
}

Bomberman::Sound::~Sound()
{
  if (this->_engine)
    this->_engine->drop();
}

