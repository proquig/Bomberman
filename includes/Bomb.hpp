//
// Created by joris_a
//

#ifndef					__BOMB_HPP__
# define				__BOMB_HPP__

# include				"Irrlicht.hpp"

namespace				Bomberman
{
  class					Bomb
  {
  public:
    enum				STATE
      {
	AWAITING,
	POSED,
      };
  private:
    Bomberman::Irrlicht			&_irr;
    irr::scene::IAnimatedMesh		*_scene;
    irr::scene::IAnimatedMeshSceneNode	*_bomb;
    float				_x;
    float				_y;
    STATE				_state;
    irr::u32				_explosion_time;
  public:
    Bomb();
    Bomb(float x, float y);
    ~Bomb();
    float				getX() const;
    float				getY() const;
    void				reset();
    void				put(float x, float y);
    irr::u32				getExplosionTime() const;
    void				explode();
    void explosion();
  };
}

#endif
