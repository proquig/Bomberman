//
// Created by cloquet on 24/05/16.
//

#include <Bomb.hpp>
#include <Menu.hpp>
#include <fstream>
#include <Exception.hpp>
#include <sstream>
#include "Game.hpp"
#include "Character.hpp"
#include "Map.hpp"

const std::vector<std::pair<std::string, std::pair<int, int>>> Bomberman::Game::_players_conf = {
	{"./assets/ninja/nskinwh.jpg", {(MAPSIZE_X / 2) - 20, -((MAPSIZE_Y / 2) - 20)}},
	{"./assets/ninja/nskinbl.jpg", {-((MAPSIZE_X / 2) - 20), (MAPSIZE_Y / 2) - 20}}
};

const float Bomberman::Game::positions[4][2] = {
	{0, 0.2f},
	{0, -0.2f},
	{-0.2f, 0},
	{0.2f, 0}
};

const std::map<irr::EKEY_CODE, std::pair<int, Bomberman::Character::ACTION>> Bomberman::Game::_events[] = {
	{
		{irr::KEY_KEY_Z, {0, Bomberman::Character::GO_UP}},
		{irr::KEY_KEY_S, {0, Bomberman::Character::GO_DOWN}},
		{irr::KEY_KEY_Q, {0, Bomberman::Character::GO_LEFT}},
		{irr::KEY_KEY_D, {0, Bomberman::Character::GO_RIGHT}},
		{irr::KEY_UP, {1, Bomberman::Character::GO_UP}},
		{irr::KEY_DOWN, {1, Bomberman::Character::GO_DOWN}},
		{irr::KEY_LEFT, {1, Bomberman::Character::GO_LEFT}},
		{irr::KEY_RIGHT, {1, Bomberman::Character::GO_RIGHT}},
	},
	{
		{irr::KEY_SPACE, {0, Bomberman::Character::PUT_BOMB}},
		{irr::KEY_KEY_U, {0, Bomberman::Character::JUMP}},
		{irr::KEY_RETURN, {1, Bomberman::Character::PUT_BOMB}},
		{irr::KEY_KEY_M, {1, Bomberman::Character::JUMP}}
	}
};

Bomberman::Game::Game(size_t nb) : _irr(Bomberman::Irrlicht::instance()),
			  _nb_players(nb)
{
  this->_map = new Bomberman::Map();
  for (int i = 0; i < this->_nb_players; ++i)
    {
      this->_players.push_back(static_cast<Bomberman::Character*>(this->_map->createObj("./assets/ninja/ninja.b3d",
											this->_players_conf[i].first,
											this->_players_conf[i].second.first,
											this->_players_conf[i].second.second,
											Bomberman::CHARACTER)));
      this->_players.back()->add_bomb(static_cast<Bomberman::Bomb*>(this->_map->createObj("", "", 0, 0, BOMB)));
    }
  this->_map->createMap();
  for (int i = 0; i < 42; ++i)
    this->_map->createObjSomewhere(WALLOBJ, WALLTEXT, Bomberman::BRICK);
  for (int j = 0; j < 106; ++j)
    this->_map->createObjSomewhere(BOXOBJ, BOXTEXT, Bomberman::BOX);
  //for (int k = 0; k < this->_map->getObjs().size(); ++k)
    //std::cout << "X = " << this->_map->getObjs()[k]->getX() << " & Y = " << this->_map->getObjs()[k]->getY() << std::endl;
}


Bomberman::Game::Game(const std::string &name) : _irr(Bomberman::Irrlicht::instance())
{
  std::vector<std::string> data;
  std::ifstream file;
  std::string line;
  std::string word;
  std::stringstream ss;

  file.open("save.txt");
  this->_map = new Bomberman::Map();
  if (file.is_open())
    {
      while (std::getline(file, line))
	{
	  ss << line;
	  while (std::getline(ss, word, ';'))
	    {
	      data.push_back(word);
	      std::cout << word << std::endl;
	    }
	  _map->createObj(data[3], data[4], std::stof(data[0].c_str()), std::stof(data[1].c_str()), (TYPE) std::stoi(data[2].c_str()));
	  data.clear();
	}
    }
}



Bomberman::Game::~Game()
{
}

void Bomberman::Game::explodeObjs(Bomberman::Bomb *bomb)
{
  int i = -1;

  //std::cout << (int)this->getX() << std::endl;
  //std::cout << (int)this->getX() - ((int)this->getX() % 5) << std::endl;
  //std::cout << ">" << ((((int)this->getX() + (int)(this->getX() > 0) * (5 - 1)) / 5) * 5) << std::endl;
  int x = Bomberman::Map::getRoundPosition(bomb->getX());
  int y = Bomberman::Map::getRoundPosition(bomb->getY());
  //std::cout << "BOMB x = " << x << " & y = " << y << std::endl;
  //std::cout << "------------" << std::endl;
  //for (int i = -200; i < 200; ++i)
    //{
      //std::cout << Bomberman::Map::getRoundPosition(i) << std::endl;
    //}
  //std::cout << "------------" << std::endl;
  int start_x = x - (((bomb->getRange()) + 1) * 5);
  int start_y = y - (((bomb->getRange()) + 1) * 5);
  for (int i = 0; (i < (((bomb->getRange() * 2) + 1)) * 5); ++i)
    if (this->_map->checkObjOnPlan((start_x + i), y)
	&& this->_map->getObjOnPlan((start_x + i), y)->isDestructible())
      this->_map->getObjOnPlan((start_x + i), y)->remove();
  for (int i = 0; (i < (((bomb->getRange() * 2) + 1)) * 5); ++i)
    if (this->_map->checkObjOnPlan(x, (start_y + i))
	&& this->_map->getObjOnPlan(x, (start_y + i))->isDestructible())
      this->_map->getObjOnPlan(x, (start_y + i))->remove();

    //{
      //std::cout << "----" << std::endl;
      //std::cout << "Real x = " << bomb->getX() << " & real y = " << bomb->getY() << std::endl;
      //std::cout << "x = " << x << " & y = " << y << std::endl;
      //std::cout << "start_x = " << start_x << " & start_y = " << start_y << std::endl;
      //std::cout << "start_x + i = " << (start_x + i) << " & start_y + i = " << (start_y + i) << std::endl;
      //std::cout << "----" << std::endl;
      //if (this->_map->checkObjOnPlan((start_x + i), start_y + i)
	//  && this->_map->getObjOnPlan((start_x + i), (start_y + i))->isDestructible())
	//this->_map->getObjOnPlan((start_x + i), (start_y + i))->remove();
    //}
/*  while (++i < this->_map->getObjs().size())
    if (this->_map->getObjs()[i]->isDestructible()
	  && !this->_map->checkObjectPosition(this->_map->getObjs()[i], bomb->getX(), bomb->getY(), bomb->getRange()))
	this->_map->getObjs()[i]->remove();
 */
}

void Bomberman::Game::handleMovements()
{
  std::map<irr::EKEY_CODE, std::pair<int, Bomberman::Character::ACTION>>::const_iterator	it;
  for (it = this->_events[0].begin(); it != _events[0].end(); ++it)
    if (this->_irr.event.getKeys()[it->first] && it->second.first < this->_players.size()
      && this->_map->checkPosition(this->_players[it->second.first]->getX() + Bomberman::Game::positions[it->second.second][0],
				   this->_players[it->second.first]->getY() + Bomberman::Game::positions[it->second.second][1], 4.5))
      this->_players[it->second.first]->do_action(it->second.second);
}

void Bomberman::Game::handleActions()
{
  std::map<irr::EKEY_CODE, std::pair<int, Bomberman::Character::ACTION>>::const_iterator	it;
  for (it = this->_events[1].begin(); it != _events[1].end(); ++it)
    if (this->_irr.event.getKeys()[it->first] && it->second.first < this->_players.size())
      this->_players[it->second.first]->do_action(it->second.second);
}

void Bomberman::Game::handleTime()
{
  irr::u32 	now = this->_irr.getDevice()->getTimer()->getTime();
  int		i = -1;

  while (++i < this->_map->getObjs().size())
    //{
      if (this->_map->getObjs()[i]->getType() == Bomberman::BOMB
	  && this->_map->getObjs()[i]->getExplosionTime()
	  && now > this->_map->getObjs()[i]->getExplosionTime())
	{
	  this->explodeObjs(static_cast<Bomberman::Bomb *>(this->_map->getObjs()[i]));
	  static_cast<Bomberman::Bomb *>(this->_map->getObjs()[i])->explode();
	}
	//{//  && (this->_map->getObjs()[i]->getExplosionTime() || this->_map->getObjs()[i]->getAnimation_time()))
	//{
	  //if (this->_map->getObjs()[i]->getAnimation_time())
	    //std::cout << "ANIM TIME: " << this->_map->getObjs()[i]->getAnimation_time() << std::endl;
	  //if (this->_map->getObjs()[i]->getExplosionTime() || this->_map->getObjs()[i]->getAnimation_time())
	    //{
	      //if (now > this->_map->getObjs()[i]->getAnimation_time())
		//static_cast<Bomberman::Bomb *>(this->_map->getObjs()[i])->clean();
	      //if (now > this->_map->getObjs()[i]->getExplosionTime())
		//{
		  //this->explodeObjs(static_cast<Bomberman::Bomb *>(this->_map->getObjs()[i]));
		  //static_cast<Bomberman::Bomb *>(this->_map->getObjs()[i])->explode();
		//}
	    //}
	  //if (now > this->_map->getObjs()[i]->getAnimation_time())
	    //static_cast<Bomberman::Bomb *>(this->_map->getObjs()[i])->clean();
	//}
    //}
//*/
}

int Bomberman::Game::handleEvents()
{
  std::vector<Bomberman::Character*>::const_iterator	it;
  int 							players_alive = 0;

  this->_map->createPlan();
  handleTime();
  handleMovements();
  handleActions();
  for (it = this->_players.begin(); it != this->_players.end(); ++it)
    if ((*it)->isDestructible())
      players_alive++;
  return (players_alive == this->_nb_players);
}

Bomberman::Map *Bomberman::Game::run()
{
  irr::scene::ICameraSceneNode *camera = this->_irr.getSmgr()->addCameraSceneNode(0, irr::core::vector3df(0, 60, -20),
									   irr::core::vector3df(0, 0, 0));
  camera->setNearValue(10);
  irr::video::ITexture *background = this->_irr.getDriver()->getTexture("./assets/Te/sky-clouds.jpg");
  int 	lastFPS = -1;
  //for (int i = 0; i != 3; ++i)
      //this->_players[i]->add_bomb(reinterpret_cast<Bomberman::Bomb*>(this->_map->createObj("", "", 0, 0, BOMB)));
  //int i =  -1;
  //while (++i < this->_map->getObjs().size())
    //if (this->_map->getObjs()[i]->getType() == Bomberman::CHARACTER)
      //std::cout << "Everybody must die1" << std::endl;
  //std::cout << this->_players[0]->isDestructible() << std::endl;
  //this->_players[0]->add_bomb(static_cast<Bomberman::Bomb*>(this->_map->createObj("", "", 0, 0, BOMB)));
  //while (this->_irr.getDevice()->drop())
  int pause = 0;
  while (this->_irr.getDevice()->run() && handleEvents())
    {
      if (this->_irr.getDevice()->isWindowActive())
	{
	 this->_irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
	 this->_irr.getDriver()->draw2DImage(background, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
					     irr::core::rect<irr::s32>(0, 0, 1920, 1080));
	  //if (this->_irr.event.getKeys()[irr::KEY_ESCAPE])
	  this->_irr.getSmgr()->drawAll();
	 this->_irr.getDriver()->endScene();
	 int fps = this->_irr.getDriver()->getFPS();
	 if (lastFPS != fps)
	   {
	     irr::core::stringw str = "Bomberman | driver [";
	     str += this->_irr.getDriver()->getName();
	     str += "] FPS :";
	     str += fps;
	     this->_irr.getDevice()->setWindowCaption(str.c_str());
	     lastFPS = fps;
	   }
       }
    }
  return (this->_map);
}
