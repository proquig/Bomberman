//
// Created by pogam-_g on 6/1/16.
//

#include <unistd.h>
#include <Game.hpp>
#include "IA.hpp"

Bomberman::IA::IA(Map *map, Character *character) : _map(map), _character(character), _dead(false)
{
  this->_thread = new std::thread(&Bomberman::IA::initIA, this);
}

Bomberman::IA::~IA()
{
  this->_thread->join();
}

void Bomberman::IA::initIA()
{
  sleep(3);
  sel::State state{true};
  state.Load("./lua/main.lua");

  state["ia"].SetObj(*this,
		     "get_case_content", &IA::getCaseContent,
		     "dead", &IA::_dead,
		     "move_top", &IA::move_top,
		     "move_bottom", &IA::move_bottom,
		     "move_left", &IA::move_left,
		     "move_right", &IA::move_right,
		     "put_bomb", &IA::putBomb,
		     "get_x", &IA::getX,
		     "get_y", &IA::getY,
		     "get_block_size", &IA::getBlockSize,
		     "get_round_position", &IA::getRoundPosition,
		     "is_blocked", &IA::isBlocked
  );

  state["get_map_x_size"] = &getMapXSize;
  state["get_map_y_size"] = &getMapYSize;

  state["main"]();
}

void Bomberman::IA::die()
{
  this->_dead = true;
}

std::string Bomberman::IA::getCaseContent(int x, int y)
{
  if (this->_dead)
    return "";

  const std::map<Bomberman::TYPE, std::string> types =
	  {
		  {BOMB, "BOMB"},
		  {BOX, "BOX"},
		  {BRICK, "BRICK"},
		  {CHARACTER, "CHARACTER"},
		  {PLAN, "PLAN"},
		  {BONUS, "BONUS"},
		  {B_STAR, "B_STAR"},
		  {B_BOMB_R, "B_BOMB_R"},
		  {B_BOMB_N, "B_BOMB_N"},
		  {B_BOOT, "B_BOOT"}
	  };

  Obj *obj = this->_map->getObjOnPlan(x, y);

  if (obj)
    return types.at(obj->getType());
  else
    return "";
}

int Bomberman::IA::getMapXSize()
{
  return MAPSIZE_X / 5;
}

int Bomberman::IA::getMapYSize()
{
  return MAPSIZE_Y / 5;
}

int Bomberman::IA::getBlockSize()
{
  return BLOCKSIZE;
}

bool Bomberman::IA::move(const std::string &direction)
{
  if (this->_dead)
    return false;

  const std::map<std::string, Character::ACTION> dirs = {
	  {"TOP", Character::GO_UP},
	  {"BOTTOM", Character::GO_DOWN},
	  {"LEFT", Character::GO_LEFT},
	  {"RIGHT", Character::GO_RIGHT}
  };

  bool moved;
  if (this->_map->checkPosition(
	  this->_character->getX() + Bomberman::Game::positions[dirs.at(direction)][0],
	  this->_character->getY() + Bomberman::Game::positions[dirs.at(direction)][1],
	  float(BLOCKSIZE - 0.1)))
    {
      this->_character->do_action(dirs.at(direction));
      moved = true;
    }
  else
    moved = false;

  usleep(30000);
  return (moved);
}

void Bomberman::IA::putBomb()
{
  if (this->_dead)
    return;

  this->_character->put_bomb(Character::PUT_BOMB);
}

bool Bomberman::IA::move_top()
{
  return move("TOP");
}

bool Bomberman::IA::move_bottom()
{
  return move("BOTTOM");
}

bool Bomberman::IA::move_left()
{
  return move("LEFT");
}

bool Bomberman::IA::move_right()
{
  return move("RIGHT");
}

int Bomberman::IA::getX()
{
  if (this->_dead)
    return 0;

  return this->_map->getRoundPosition(this->_character->getX());
}

int Bomberman::IA::getY()
{
  if (this->_dead)
    return 0;

  return this->_map->getRoundPosition(this->_character->getY());
}

int Bomberman::IA::getRoundPosition(int i)
{
  if (this->_dead)
    return i;

  return this->_map->getRoundPosition(i);
}

bool Bomberman::IA::isBlocked(int x, int y)
{

  if (this->_dead)
    return false;

  static int last_x = 0;
  static int last_y = 0;
  static time_t last_time = 0;
  static bool inited = false;
  time_t now;

  if (!inited)
    {
      last_x = this->getX();
      last_y = this->getY();
      time(&last_time);
      inited = true;
      return (false);
    }
  else
    {
      time(&now);
      return (last_x == x && last_y == y && now - last_time >= 2);
    }
}
