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

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "irrKlang.lib")
#endif

#include <irrKlang.h>
#include "Irrlicht.hpp"

namespace Bomberman
{
  class MusicManager
  {
   private:
    static MusicManager _instance;
    Bomberman::Irrlicht &_irr;
    irrklang::ISoundEngine *_engine;
    irrklang::ISound *_music;
    int 		_play;

   public:
    static MusicManager &instance();

   private:
    MusicManager();

    MusicManager(const MusicManager &sound);

    MusicManager &operator=(const MusicManager &sound);

    ~MusicManager();

   public:
    void setMusic(const std::string &path);

    void setSong(const std::string &path);

    void stopMusic();

    bool isMusicPlayed();

    void pauseMusic();

    void startMusic();

    int getPlay() const;

    void setPlay(int play);

  };
}

#endif //CPP_INDIE_STUDIO_SONG_HPP
