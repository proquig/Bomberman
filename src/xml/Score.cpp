//
// Created by pogam-_g on 5/29/16.
//

#include "Score.hpp"

Bomberman::Score::Score(const std::string &name, const time_t &gameStart, const time_t &gameEnd, const int score)
	: name(name), gameStart(gameStart), gameEnd(gameEnd), score(score)
{
}

const std::string &Bomberman::Score::getName() const
{
  return name;
}

const long &Bomberman::Score::getGameStart() const
{
  return gameStart;
}

const long &Bomberman::Score::getGameEnd() const
{
  return gameEnd;
}

const int &Bomberman::Score::getScore() const
{
  return score;
}
