//
// Created by joris_a
//

#include "Irrlicht.hpp"


class		Bomb {
public:
  enum state {
    AWAITING,
    POSED,
    EXPLODED
  };
  Bomb();
  Bomb(int pX, int pY);
  ~Bomb();
  std::string getMesh() const;
  void	      setState(Bomb::state const& c);
  void	      explosion();

private:
  std::string _mesh;
  enum state _state;
  int		_px;
  int		_py;
};
