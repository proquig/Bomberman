//
// Created by cloquet on 04/06/16.
//

#ifndef CPP_INDIE_STUDIO_HIGHSCORE_HPP
#define CPP_INDIE_STUDIO_HIGHSCORE_HPP

#include <vector>

namespace Bomberman
{
  class Highscore
  {
   private:
    std::string			_name;
    std::vector <std::string> 	_score;

   public:
    Highscore();
    ~Highscore();
    void			writeScore(size_t);
    std::vector <std::string> 	getScore() const;
  };
}

#endif //CPP_INDIE_STUDIO_HIGHSCORE_HPP
