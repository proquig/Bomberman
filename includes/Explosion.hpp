//
// Created by joris_a
//

#ifndef					__EXPLOSION_HPP__
# define				__EXPLOSION_HPP__

# include				"Irrlicht.hpp"
# include				"Obj.hpp"
# include				<chrono>
# include <thread>

namespace				Bomberman
{
  class					Explosion {
  public:
    Explosion(float x, float y);
    ~Explosion();
    void		clear();

   private:
    Bomberman::Irrlicht				&_irr;
    irr::scene::ISceneNode 			*node;
    float 					_x;
    float 					_y;
  };
}


#endif 
