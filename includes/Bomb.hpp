//
// Created by joris_a
//

#ifndef					__BOMB_HPP__
# define				__BOMB_HPP__

#include <sound/MusicManager.hpp>
#include <sound/SoundManager.hpp>
# include				"Irrlicht.hpp"
# include				"Obj.hpp"
# include				"Explosion.hpp"

namespace				Bomberman
{
  class					Bomb : public Bomberman::Obj
  {
  /*public:
    enum				STATE
      {
	AWAITING,
	POSED,
      };
      */
  private:
    float 				*_range;
    //STATE				_state;
    Bomberman::Explosion		*exp;
    
  public:
     Bomb(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type);
    ~Bomb();
    void				reset();
    void				put(float x, float y);
    void				explode();
    float				getRange() const;
    void				setRange(float *range);
    void				clean();
  };
}

#endif
