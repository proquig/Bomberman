//
// Created by pogam-_g on 5/28/16.
//

#include "sound/SoundManager.hpp"

Bomberman::SoundManager Bomberman::SoundManager::_instance = Bomberman::SoundManager();

Bomberman::SoundManager Bomberman::SoundManager::instance()
{
  return _instance;
}

Bomberman::SoundManager::SoundManager() : _irr(Bomberman::Irrlicht::instance()),
					  _engine(irrklang::createIrrKlangDevice())
{
}

Bomberman::SoundManager::SoundManager(const Bomberman::SoundManager &s) : _irr(s._irr),
									  _engine(s._engine)
{
}

Bomberman::SoundManager &Bomberman::SoundManager::operator=(const Bomberman::SoundManager &)
{
  return *this;
}

Bomberman::SoundManager::~SoundManager()
{
}

void Bomberman::SoundManager::registerSound(const std::string &key, const std::string &path)
{
  irrklang::ISound *sound = this->_engine->play3D(path.c_str(), irrklang::vec3df(0, 0, 0), true, true, true);

  this->_sounds.insert(std::pair<std::string, irrklang::ISound *>(key, sound));
}

bool Bomberman::SoundManager::playSound(const std::string &id)
{
  std::map<std::string, irrklang::ISound *>::iterator sound;

  sound = this->_sounds.find(id);
  if (sound != this->_sounds.end())
    {
      sound->second->setIsPaused(false);
      return true;
    }
  else
    return false;
}
