//
// Created by cloquet on 28/05/16.
//

#include <list>
#include <stdlib.h>
#include <zconf.h>
#include "Map.hpp"

Bomberman::Map::Map() : _irr(Bomberman::Irrlicht::instance())
{
}

Bomberman::Map::~Map()
{
}

bool 		Bomberman::Map::checkObjectPosition(Bomberman::Obj* obj, float x, float y, float range)
{
  float		resx;
  float		resy;

  resx = obj->getX() - x;
  resy = obj->getY() - y;
  return (!((obj->isBlockable() || obj->getType() == Bomberman::CHARACTER) && (resx <= range && resx >= -range) && (resy <= range && resy >= -range)));
}

bool		Bomberman::Map::checkPosition(float x, float y, float range, bool all)
{
  int 		i;

  i = -1;
  while (++i < this->_objs.size())
    if (all && !checkObjectPosition(this->_objs[i], x, y, range))
      return (false);
    else if (this->_objs[i]->getType() != Bomberman::CHARACTER && !checkObjectPosition(this->_objs[i], x, y, range))
      return (false);
  return (true);
}

void		Bomberman::Map::createMap()
{
  _material.Lighting = true;
  _scene = this->_irr.getSmgr()->getRootSceneNode();
  createObj("", FLOORTEXT, MAPSIZE_X, MAPSIZE_Y, Bomberman::PLAN);
  for (int wallnbr = 0; wallnbr <= MAPSIZE_X; wallnbr += 5)
    {
      createObj(WALLOBJ, WALLTEXT, MAPSIZE_X / 2 - wallnbr, MAPSIZE_Y / 2, Bomberman::BRICK);
      createObj(WALLOBJ, WALLTEXT, MAPSIZE_X / 2 - wallnbr, -MAPSIZE_Y / 2, Bomberman::BRICK);
    }
  for (int wallnbr = 0; wallnbr <= MAPSIZE_Y; wallnbr += 5)
    {
      createObj(WALLOBJ, WALLTEXT, MAPSIZE_X / 2, MAPSIZE_Y / 2 - wallnbr, Bomberman::BRICK);
      createObj(WALLOBJ, WALLTEXT, -MAPSIZE_X / 2, MAPSIZE_Y / 2 - wallnbr, Bomberman::BRICK);
    }
}

std::vector<Bomberman::Obj *>                        Bomberman::Map::getObjs() const
{
  return (this->_objs);
}

Bomberman::Obj *                Bomberman::Map::createObj(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type)
{
   std::map<Bomberman::TYPE, ObjPtr> objs = {
	   {BRICK, &Map::create<Obj>},
	   {BOX, &Map::create<Obj>},
	   {PLAN, &Map::create<Obj>},
	   {CHARACTER, &Map::create<Character>},
	   {BOMB, &Map::create<Bomb>}
   };
  for (std::map<Bomberman::TYPE, ObjPtr >::const_iterator it = objs.begin(); it != objs.end(); ++it)
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
  int x = 1;
  int y = 1;

  while (!(!(x % 5) && !(y % 5) && this->checkPosition(x, y, 2.5, true)))
    {
      x = 1;
      y = 1;
      while (x % 5)
	x = (rand() + rand()) % (MAPSIZE_X / 2);
      while (y % 5)
	y = (rand() + rand()) % (MAPSIZE_Y / 2);
    }
  return createObj(mesh_path, texture_path, float(x), (float)y, type);
}
