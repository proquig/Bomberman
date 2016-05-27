//
// Created by cloquet on 25/05/16.
//

#ifndef CPP_INDIE_STUDIO_SONG_HPP
#define CPP_INDIE_STUDIO_SONG_HPP

#ifdef WIN32
#include <windows.h>
#include <conio.h>
inline void sleepSomeTime() { Sleep(100); }
#endif

#include <irrKlang.h>

#pragma comment(lib, "irrKlang.lib")

#include "Irrlicht.hpp"

#include "irrKlang.h"

namespace Bomberman
{
  class Sound
  {
   private:
    Bomberman::Irrlicht &irr;
    irrklang::ISoundEngine *_engine;

   public:
    Sound();

    ~Sound();
  };
}

#endif //CPP_INDIE_STUDIO_SONG_HPP
