//
// Created by pogam-_g on 5/29/16.
//

#ifndef CPP_INDIE_STUDIO_SCORE_HPP
#define CPP_INDIE_STUDIO_SCORE_HPP

#include <string>
#include <ctime>

namespace Bomberman
{
class Score
{
  const std::string &name;
  const time_t &gameStart;
  const time_t &gameEnd;
  const int &score;

 public:
  Score(const std::string &name, const time_t &gameStart, const time_t &gameEnd,
	const int score);

  const std::string &getName() const;

  const long &getGameStart() const;

  const long &getGameEnd() const;

  const int &getScore() const;
};
}

#endif //CPP_INDIE_STUDIO_SCORE_HPP
