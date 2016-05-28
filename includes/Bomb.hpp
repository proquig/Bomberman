//
// Created by joris_a
//

#include "Irrlicht.hpp"

namespace Bomberman
{
  class Bomb
  {
   public:
    enum state
    {
      AWAITING,
      POSED,
      EXPLODED
    };

    Bomb();

    Bomb(int pX, int pY);

    ~Bomb();

    void setState(Bomb::state const &c);

    void explosion();

   private:

    scene::IAnimatedMesh *_bomb;
    scene::IAnimatedMeshSceneNode *_scene;
    Bomberman::Irrlicht &_irr;
    enum state _state;
    int _px;
    int _py;
  };
}