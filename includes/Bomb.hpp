//
// Created by joris_a
//

#ifndef					__BOMB_HPP__
# define				__BOMB_HPP__

# include				"Irrlicht.hpp"
# include				"Obj.hpp"
# include				"Explosion.hpp"

namespace				Bomberman
{
  class					Bomb : public Bomberman::Obj
  {
  public:
    enum				STATE
      {
	AWAITING,
	POSED,
      };
  private:
    STATE				_state;
    Bomberman::Explosion		*exp;

  public:
    Bomb();
    ~Bomb();
    Bomberman::Obj*			create();
    void				reset();
    void				put(float x, float y);
    void				explode();
  };
}

#endif
