//
// Created by cloquet on 28/05/16.
//

#include <list>
#include <stdlib.h>
#include <zconf.h>
#include "Map.hpp"

std::map<int, std::map<int, Bomberman::Obj*>>	_plan;

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

std::map<int, std::map<int, Bomberman::Obj*>>	Bomberman::Map::getPlan() const
{
  return (this->_plan);
}

void		Bomberman::Map::createPlan()
{
  std::vector<Bomberman::Obj*>::iterator it;
  int x;
  int y;

  this->_plan.clear();
  for (it = this->_objs.begin(); it != this->_objs.end(); ++it)
    if ((*it)->isBlockable() || (*it)->getType() == Bomberman::CHARACTER)
      {
	x = this->getRoundPosition((int)(*it)->getX());
	y = this->getRoundPosition((int)(*it)->getY());
	this->_plan[x][y] = (*it);
	//if ((*it)->getType() == Bomberman::CHARACTER)
	  //std::cout << "getX = " << (int)(*it)->getX() << " & getY = " << (int)(*it)->getY() << " x = " << x << " & y = " << y << " type = " << this->_plan[x][y]->getType() << std::endl;
      }

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
  std::cerr << mesh_path << "-" << texture_path << "-" << x << "-" << y << std::endl;
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
	x = (rand() - rand()) % (MAPSIZE_X / 2);
      while (y % 5)
	y = (rand() - rand()) % (MAPSIZE_Y / 2);
    }
  return createObj(mesh_path, texture_path, float(x), float(y), type);
}

bool Bomberman::Map::checkObjOnPlan(int x, int y)
{
  return (this->_plan.find(x) != this->_plan.end() && this->_plan[x].find(y) != this->_plan[x].end());
}

Bomberman::Obj *Bomberman::Map::getObjOnPlan(int x, int y)
{
  return (this->checkObjOnPlan(x, y) ? this->_plan[x][y] : NULL);
}

int Bomberman::Map::getRoundPosition(float axis)
{

  //if ((int)axis % 5 < (5/ 2))
    return (((((int)axis + (int)(axis > 0) * (5 - 1)) / 5) * 5));
  //return (((((int)axis + (5 - 1)) / 5) * 5));
  /*
  if (axis < 0)
    return (axis - ((int)axis % 5));
  return (axis + (5 - (int)axis % 5));
   */
  //if (axis > 0)
  //return (((((int)axis + (int)(axis > 0) * (5 - 1)) / 5) * 5));
  //return (((((int)axis) / 5) * 5));
  //return ((((axis + /*(int)(axis > 0) **/ (5 - 1)) / 5) * 5));
  /*if (axis < 0)
    return ((int)axis - ((int)axis % 5));
  else
    return ((int)axis - ((int)axis % 5));
    */
  //return ((((int)axis + 5 / 2) / 5) * 5);
  //std::cout << "x = " << axis << " & new x = " << (((axis + (int)(axis > 0) * (5 - 1)) / 5) * 5) << std::endl;
  //return ((((axis + /*(int)(axis > 0) **/ (5 - 1)) / 5) * 5));
  //return (((((int)axis + (int)(axis > 0) * (5 - ((int)axis % 5))) / 5) * 5));

}
