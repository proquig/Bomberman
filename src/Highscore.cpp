//
// Created by cloquet on 04/06/16.
//

#include <string>
#include <fstream>
#include <Exception.hpp>
#include <zconf.h>
#include "Highscore.hpp"

Bomberman::Highscore::Highscore() : _name("highscores")
{
  std::string			line;

  try {
      std::ifstream file(this->_name);
      while (std::getline(file, line))
	this->_score.push_back(line);
    } catch (exception &e) {
      e.what();
    }
}

Bomberman::Highscore::~Highscore()
{
}

void 				Bomberman::Highscore::writeScore(size_t score)
{
  try
    {
      std::ofstream file(this->_name);
      file << getlogin() << " - " << score << "\n";
    } catch (exception &e) {
      e.what();
    }
}

std::vector<std::string>	Bomberman::Highscore::getScore() const
{
  return this->_score;
}
