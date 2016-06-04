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
  sleep(5);
  sel::State state{true};
  state.Load("./lua/main.lua");

  state["ia"].SetObj(*this,
		     "get_case_content", &IA::getCaseContent,
		     "dead", &IA::_dead,
		     "move", &IA::move,
		     "put_bomb", &IA::putBomb
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
  const std::map<Bomberman::TYPE, std::string> types =
	  {
		  {BOMB, "BOMB"},
		  {BOX, "BOX"},
		  {BRICK, "BRICK"},
		  {CHARACTER, "CHARACTER"},
		  {PLAN, "PLAN"}
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

void Bomberman::IA::move(std::string direction)
{
  if (this->_dead)
    return;

  const std::map<std::string, int> dirs = {
	  {"TOP", 0},
	  {"BOTTOM", 1},
	  {"LEFT", 2},
	  {"RIGHT", 3}
  };

  if (this->_map->checkPosition(
	  this->_character->getX() + Bomberman::Game::positions[dirs.at(direction)][0],
	  this->_character->getY() + Bomberman::Game::positions[dirs.at(direction)][1],
	  float(BLOCKSIZE - 0.1)))
    this->_character->do_action(Character::GO_LEFT);
  usleep(35000);
}

void Bomberman::IA::putBomb()
{
  if (this->_dead)
    return;
  this->_character->put_bomb(Character::PUT_BOMB);
}
