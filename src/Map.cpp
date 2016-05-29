//
// Created by cloquet on 28/05/16.
//

#include <list>
#include "Obj.hpp"
#include "Map.hpp"

Bomberman::Map::Map() : _irr(Bomberman::Irrlicht::instance())
{
}

Bomberman::Map::~Map()
{
}

bool						Bomberman::Map::checkPosition(float x, float y, float range)
{
  int						i;
  int						resx;
  int						resy;

  i = -1;
  while (++i < this->_objs.size())
    {
      resx = this->_objs[i]->getX() - x;
      resy = this->_objs[i]->getY() - y;
      if ((resx <= range && resx >= -range) && (resy <= range && resy >= -range))
	return (false);
    }
  return (true);
}

void                Bomberman::Map::createMap()
{
  _material.Lighting = true;
  _scene = this->_irr.getSmgr()->getRootSceneNode();
  Bomberman::Obj obj("", "./assets/Te/Sand_floor.jpg", X, Y, Bomberman::Obj::PLAN);

  for (int wallnbr = 0; wallnbr <= X; wallnbr += 5)
    {
      createWall(X / 2 - wallnbr, Y / 2);
      createWall(X / 2 - wallnbr, -Y / 2);
    }
  for (int wallnbr = 0; wallnbr <= Y; wallnbr += 5)
    {
      createWall(X / 2, Y / 2 - wallnbr);
      createWall(-X / 2, Y / 2 - wallnbr);
    }
}

Bomberman::Obj		   *Bomberman::Map::putObj(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::Obj::TYPE type)
{

  this->_objs.push_back(new Bomberman::Obj(mesh_path, texture_path, x, y, type));
  return (this->_objs.back());
}

irr::scene::IMeshSceneNode *Bomberman::Map::createBreakableWall()
{
 irr::scene::IMeshSceneNode *wall = 0;

  static int 		r = 1;
  srand((unsigned int) time(NULL));
  r  += rand() * rand();
  float x = 0;
  float y = 0;
  while (!this->checkPosition(x, y, 5.0))
    {
      x = (rand() + r) % (X / 2);
      y = (rand() + r) % (Y / 2);
    }

  putObj("./assets/Box/ItmBox00.obj", "./assets/Box/ItmBox01_00.png", x, y, Bomberman::Obj::BRICK);
  return wall;
}

void Bomberman::Map::createWall(int x, int y)
{
  putObj("./assets/Box/ItmCarrierBox00.obj", "./assets/Box/ItmCommonBoxB00.png", x, y, Bomberman::Obj::BRICK);
}
