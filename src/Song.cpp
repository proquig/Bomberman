//
// Created by cloquet on 25/05/16.
//

#include "Song.hpp"

Bomberman::Song::Song() : irr(Bomberman::Irrlicht::instance())
{
  irrklang::ISoundEngine *engine = irrklang::createIrrKlangDevice();
  irrklang::ISound *music = engine->play3D("media/Song/menuSong.mp3", irrklang::vec3df(0, 0, 0), \
  true, false, true);

  music->setMinDistance(5.0f);
}

Bomberman::Song::~Song()
{

}

