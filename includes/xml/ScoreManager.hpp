//
// Created by pogam-_g on 5/29/16.
//

#ifndef CPP_INDIE_STUDIO_SAVEMANAGER_HPP
#define CPP_INDIE_STUDIO_SAVEMANAGER_HPP

#include <string>
#include <vector>
#include "xml/tinyxml2.h"
#include "xml/Score.hpp"

namespace Bomberman
{
  class ScoreManager
  {
    std::string _path;
    tinyxml2::XMLDocument _doc;

   public:
    ScoreManager(const std::string &path);

    std::vector<Score> loadScores();

    void SaveScore(const Score &score);
  };
}

#endif //CPP_INDIE_STUDIO_SAVEMANAGER_HPP
