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
    Explosion(int x, int y);
    ~Explosion();

  private:
    Bomberman::Irrlicht				&_irr;
    irr::scene::IParticleSystemSceneNode	*_ps;
    irr::scene::IParticleEmitter		*_em;
    irr::scene::IParticleAffector		*_paf;
  };
}


#endif 
