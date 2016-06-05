//
// Created by cloquet on 28/05/16.
//

#include <list>
#include <stdlib.h>
#include <zconf.h>
#include <Game.hpp>
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
  return (!((obj->isBlocking() || obj->getType() == Bomberman::CHARACTER)
	    && (resx <= range && resx >= -range)
	    && (resy <= range && resy >= -range)));
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
    if ((*it)->isBlocking()
	|| (*it)->getType() == Bomberman::CHARACTER
	|| ((*it)->getType() == Bomberman::BOMB && (*it)->isDestructible())
	|| Bomberman::Game::_bonus.find((*it)->getType()) != Bomberman::Game::_bonus.end())
    //if ((*it)->isDestructible())
      {
	x = this->getRoundPosition((*it)->getX());
	y = this->getRoundPosition((*it)->getY());
	this->_plan[x][y] = (*it);
      }
}

void		Bomberman::Map::createMap()
{
  _material.Lighting = true;
  _scene = this->_irr.getSmgr()->getRootSceneNode();
  createObj("", FLOORTEXT, MAPSIZE_X, MAPSIZE_Y, Bomberman::PLAN);
  for (int wallnbr = 0; wallnbr <= MAPSIZE_X; wallnbr += BLOCKSIZE)
    {
      createObj(WALLOBJ, WALLTEXT, ((MAPSIZE_X / 2) - wallnbr), (MAPSIZE_Y / 2), Bomberman::BRICK);
      createObj(WALLOBJ, WALLTEXT, ((MAPSIZE_X / 2) - wallnbr), (-(MAPSIZE_Y / 2)), Bomberman::BRICK);
    }
  for (int wallnbr = 0; wallnbr <= MAPSIZE_Y; wallnbr += BLOCKSIZE)
    {
      createObj(WALLOBJ, WALLTEXT, (MAPSIZE_X / 2), ((MAPSIZE_Y / 2) - wallnbr), Bomberman::BRICK);
      createObj(WALLOBJ, WALLTEXT, (-(MAPSIZE_X / 2)), ((MAPSIZE_Y / 2) - wallnbr), Bomberman::BRICK);
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
	   {BOMB, &Map::create<Bomb>},
	   {BONUS, &Map::create<Obj>},
	   {B_STAR, &Map::create<Obj>},
	   {B_BOMB_R, &Map::create<Obj>},
	   {B_BOMB_N, &Map::create<Obj>},
	   {B_BOOT, &Map::create<Obj>}
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
  int x = 1;
  int y = 1;

  std::srand(std::time(0));
  while (!(!(x % BLOCKSIZE) && !(y % BLOCKSIZE) && this->checkPosition(x, y, (BLOCKSIZE / 2), true)))
    {
      x = 1;
      y = 1;
      while (x % BLOCKSIZE)
	x = (std::rand() - std::rand()) % (MAPSIZE_X / 2);
      while (y % BLOCKSIZE)
	y = (std::rand() - std::rand()) % (MAPSIZE_Y / 2);
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
  return (((((int)axis + (int)(axis > 0) * (BLOCKSIZE - 1)) / BLOCKSIZE) * BLOCKSIZE));
}
