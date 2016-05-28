//
// Created by pogam-_g on 5/28/16.
//

#ifndef CPP_INDIE_STUDIO_SOUNDMANAGER_HPP
#define CPP_INDIE_STUDIO_SOUNDMANAGER_HPP

#ifdef WIN32
#include <windows.h>
#include <conio.h>
inline void sleepSomeTime() { Sleep(100); }
#endif

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "irrKlang.lib")
#endif

#include <map>
#include <irrKlang.h>
#include "Irrlicht.hpp"

namespace Bomberman
{
  class SoundManager
  {
    static SoundManager _instance;
    Bomberman::Irrlicht &_irr;
    irrklang::ISoundEngine *_engine;
    std::map<std::string, irrklang::ISound *> _sounds;

   public:
    static SoundManager instance();

   private:
    SoundManager();
    SoundManager(const SoundManager &);
    SoundManager &operator=(const SoundManager &);
    ~SoundManager();

   public:
    void registerSound(const std::string &id, const std::string &path);

    bool playSound(const std::string &id);
  };
}

#endif //CPP_INDIE_STUDIO_SOUNDMANAGER_HPP
