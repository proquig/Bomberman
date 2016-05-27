//
// Created by cloquet on 25/05/16.
//

#include "Song.hpp"

Bomberman::Song::Song() : irr(Bomberman::Irrlicht::instance())
{
  this->_engine = irrklang::createIrrKlangDevice();
  if (!this->_engine)
    return;
  irrklang::ISound *music = this->_engine->play3D("./assets/song/menusong.flac", irrklang::vec3df(0, 0, 0), \
  true, false, true);

  music->setMinDistance(5.0f);
}

Bomberman::Song::~Song()
{
  if (this->_engine)
    this->_engine->drop();
}

