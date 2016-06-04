//
// Created by cloquet on 25/05/16.
//

#include "Exception.hpp"
#include "sound/MusicManager.hpp"

Bomberman::MusicManager Bomberman::MusicManager::_instance = Bomberman::MusicManager();

Bomberman::MusicManager &Bomberman::MusicManager::instance()
{
  return _instance;
}

Bomberman::MusicManager::MusicManager() : _irr(Bomberman::Irrlicht::instance()),
					  _engine(irrklang::createIrrKlangDevice()),
					  _music(nullptr),
					  _play(1)
{}

Bomberman::MusicManager::MusicManager(const Bomberman::MusicManager &sound) : _irr(sound._irr)
{}

Bomberman::MusicManager &Bomberman::MusicManager::operator=(const Bomberman::MusicManager &sound)
{
  return *this;
}

Bomberman::MusicManager::~MusicManager()
{
  if (this->_music)
    this->stopMusic();
  if (this->_engine)
    this->_engine->drop();
}

void Bomberman::MusicManager::setMusic(const std::string &path)
{
  this->_music = this->_engine->play3D(path.c_str(), irrklang::vec3df(0, 0, 0), true, true, true);
}

void Bomberman::MusicManager::setSong(const std::string &path)
{
  this->_music = this->_engine->play3D(path.c_str(), irrklang::vec3df(0, 0, 0), false, true, true);
}


void Bomberman::MusicManager::stopMusic()
{
  this->_music->stop();
  this->_music->drop();
}

bool Bomberman::MusicManager::isMusicPlayed()
{
  return this->_music->getIsPaused();
}

void Bomberman::MusicManager::pauseMusic()
{
  this->_music->setIsPaused(true);
}

void Bomberman::MusicManager::startMusic()
{
     if (this->_music)
       this->_music->setIsPaused(false);
     else
       throw exception("Music cannot be loaded");
}

int Bomberman::MusicManager::getPlay() const
{
  return _play;
}

void Bomberman::MusicManager::setPlay(int play)
{
  _play = play;
}
