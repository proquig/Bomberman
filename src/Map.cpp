//
// Created by cloquet on 28/05/16.
//

#include <list>
#include <stdlib.h>
#include "Map.hpp"

Bomberman::Map::Map() : _irr(Bomberman::Irrlicht::instance())
{
}

Bomberman::Map::~Map()
{
}

bool		Bomberman::Map::checkPosition(float x, float y, float range)
{
  int 		i;
  float		resx;
  float		resy;

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

void		Bomberman::Map::createMap()
{
  _material.Lighting = true;
  _scene = this->_irr.getSmgr()->getRootSceneNode();
  createObj("", "./assets/Floor/grass2.jpg", MAPSIZE_X, MAPSIZE_Y, Bomberman::PLAN);
  for (int wallnbr = 0; wallnbr <= MAPSIZE_X; wallnbr += 5)
    {
      createObj("./assets/Box/ItmCarrierBox00.obj", "./assets/Box/ItmCommonBoxB00.png", MAPSIZE_X / 2 - wallnbr, MAPSIZE_Y / 2, Bomberman::BRICK);
      createObj("./assets/Box/ItmCarrierBox00.obj", "./assets/Box/ItmCommonBoxB00.png", MAPSIZE_X / 2 - wallnbr, -MAPSIZE_Y / 2, Bomberman::BRICK);
    }
  for (int wallnbr = 0; wallnbr <= MAPSIZE_Y; wallnbr += 5)
    {
      createObj("./assets/Box/ItmCarrierBox00.obj", "./assets/Box/ItmCommonBoxB00.png", MAPSIZE_X / 2, MAPSIZE_Y / 2 - wallnbr, Bomberman::BRICK);
      createObj("./assets/Box/ItmCarrierBox00.obj", "./assets/Box/ItmCommonBoxB00.png", -MAPSIZE_X / 2, MAPSIZE_Y / 2 - wallnbr, Bomberman::BRICK);
    }
}

Bomberman::Obj *                Bomberman::Map::createObj(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type)
{
   std::map<Bomberman::TYPE, ptr> objs = {
	   {BRICK, &Map::create<Obj>},
	   {BOX, &Map::create<Obj>},
	   {PLAN, &Map::create<Obj>},
	   {CHARACTER, &Map::create<Character>},
	   {BOMB, &Map::create<Obj>}
   };
  for (std::map<Bomberman::TYPE, ptr >::const_iterator it = objs.begin(); it != objs.end(); ++it)
    if (it->first == type)
      {
	this->_objs.push_back((Obj *const &) (this->*(it->second))(mesh_path, texture_path, x, y, type));
	return (this->_objs.back());
      };
  return (NULL);
}

Bomberman::Obj *		Bomberman::Map::createObjSomewhere(const std::string &mesh_path, const std::string &texture_path, Bomberman::TYPE type)
{
  static int r = 1;
  srand((unsigned int) time(NULL));
  r += rand() * rand();
  float x = 0;
  float y = 0;
  while (!this->checkPosition(x, y, 5.0))
    {
      x = (rand() + r) % (MAPSIZE_X / 2);
      y = (rand() + r) % (MAPSIZE_Y / 2);
    }
  return createObj(mesh_path, texture_path, x, y, type);
}
