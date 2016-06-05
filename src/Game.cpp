//
// Created by cloquet on 24/05/16.
//

#include <Bomb.hpp>
#include <Menu.hpp>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <IA.hpp>
#include <Exception.hpp>
#include <Highscore.hpp>
#include "Game.hpp"

const std::vector<std::pair<std::string, std::pair<int, int>>> Bomberman::Game::_players_conf = {
	{"./assets/ninja/nskinwh.jpg", {(MAPSIZE_X / 2) - (4 * BLOCKSIZE),     -((MAPSIZE_Y / 2) - (4 * BLOCKSIZE))}},
	{"./assets/ninja/nskinbl.jpg", {-((MAPSIZE_X / 2) - (4 * BLOCKSIZE)),  (MAPSIZE_Y / 2) - (4 * BLOCKSIZE)}},
	{"./assets/ninja/nskinbr.jpg", {-((MAPSIZE_X / 2) + (-2 * BLOCKSIZE)), -(MAPSIZE_Y / 2) + (2 * BLOCKSIZE)}},
	{"./assets/ninja/nskinrd.jpg", {((MAPSIZE_X / 2) - (4 * BLOCKSIZE)),   (MAPSIZE_Y / 2) - (4 * BLOCKSIZE)}},
};

const std::map<Bomberman::TYPE, Bomberman::Game::BonusMemFn> Bomberman::Game::_bonus = {
	{Bomberman::B_BOMB_R, &Bomberman::Game::bonus_bomb_range},
	{Bomberman::B_BOMB_N, &Bomberman::Game::bonus_bomb_nb},
	{Bomberman::B_STAR,   &Bomberman::Game::bonus_god},
	{Bomberman::B_BOOT,   &Bomberman::Game::bonus_speed}
};

const float Bomberman::Game::positions[4][2] = {
	{0,  1},
	{0,  -1},
	{-1, 0},
	{1,  0}
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

Bomberman::Game::Game(size_t nb, int size_map) : _irr(Bomberman::Irrlicht::instance()),
						 _nb_players(nb)
{
  this->_map = new Bomberman::Map();
  for (int i = 0; i < 84; ++i)
    this->_map->createObjSomewhere(WALLOBJ, WALLTEXT, Bomberman::BRICK);
  for (int i = 0; i < size_map; ++i)
    this->_map->createObjSomewhere(BOXOBJ, BOXTEXT, Bomberman::BOX);
  this->_map->createMap();
  this->_map->createPlan();
  for (int i = 0; i < 4; ++i)
    {
      this->_players.push_back(static_cast<Bomberman::Character *>(this->_map->createObj("./assets/ninja/ninja.b3d",
											 this->_players_conf[i].first,
											 this->_players_conf[i].second.first,
											 this->_players_conf[i].second.second,
											 Bomberman::CHARACTER)));
      if (i > _nb_players - 1)
	  this->_players.back()->setIa(new IA(this->_map, this->_players.back()));
      //for (int z = 0; z < 10; ++z)
	this->_players.back()->add_bomb(static_cast<Bomberman::Bomb *>(this->_map->createObj("", "", 0, 0, BOMB)));
      for (int j = -1; j < 2; ++j)
	{
	  if (this->_map->getPlan()[this->_players_conf[i].second.first + (j * BLOCKSIZE)][this->_players_conf[i].second.second])
	    this->_map->getPlan()[this->_players_conf[i].second.first + (j * BLOCKSIZE)][this->_players_conf[i].second.second]
		    ->remove();
	  if (this->_map->getPlan()[this->_players_conf[i].second.first][this->_players_conf[i].second.second + (j * BLOCKSIZE)])
	    this->_map->getPlan()[this->_players_conf[i].second.first][this->_players_conf[i].second.second + (j * BLOCKSIZE)]->remove();
	}
    }
}

Bomberman::Game::Game(const std::string &name) : _irr(Bomberman::Irrlicht::instance())
{
  std::vector<std::string> data;
  std::ifstream file("save.txt");
  std::string line;
  std::string word;
  std::stringstream ss;

  this->_map = new Bomberman::Map();
  if (!file)
    throw (exception("Invalid file"));
  while (std::getline(file, line))
    {
      ss << line;
      while (std::getline(ss, word, ';'))
	data.push_back(word);
      ss.clear();
      line.clear();
      if (std::atoi(data[2].c_str()) == 4)
	{
	  this->_players.push_back(static_cast<Bomberman::Character *>(this->_map->createObj(data[3],
											     data[4],
											     std::atof(data[0].c_str()),
											     std::atof(data[1].c_str()),
											     (TYPE) std::atoi(
												        data[2].c_str()))));
	  this->_players.back()->add_bomb(static_cast<Bomberman::Bomb *>(this->_map->createObj("", "", 0, 0, BOMB)));
	}
      else if (std::atoi(data[2].c_str()) != 2)
	this->_map->createObj(data[3],
			      data[4],
			      (float) std::atof(data[0].c_str()),
			      (float) std::atof(data[1].c_str()),
			      (TYPE) std::atoi(data[2].c_str()));
      data.clear();
    }
  this->_map->createMap();
  this->_nb_players = this->_players.size();
}

Bomberman::Game::~Game()
{
}

void Bomberman::Game::explodeObj(Bomberman::Obj *obj)
{
  if (obj->isDestructible())
    {
      //std::cout << ">>> X = " << obj->getX() << " & Y = " << obj->getY() << std::endl;
      if (obj->getType() == Bomberman::BOMB)
	this->explodeObjs(static_cast<Bomberman::Bomb *>(obj));
      else  if (obj->getType() == Bomberman::BOX && !(std::rand() % 2))
	this->_map->createObj("", "", obj->getX(), obj->getY(), Bomberman::BONUS);
      obj->remove();
    }
}

void Bomberman::Game::explodeObjs(Bomberman::Bomb *bomb)
{
  std::srand(std::time(0));

  bomb->explode();
  //std::cout << "BOMB X = " << bomb->getX() << " & Y = " << bomb->getY() << std::endl;
  for (int i = -1; i < 2; ++i)
    {
      int j = -1;
      while ((i || j) && (++j < bomb->getRange())
	     && (!this->_map->getPlan()[bomb->getX() + (i * j * BLOCKSIZE)][bomb->getY()]
		 || !(this->_map->getPlan()[bomb->getX() + (i * j * BLOCKSIZE)][bomb->getY()]->isBlocking()
		      || this->_map->getPlan()[bomb->getX() + (i * j * BLOCKSIZE)][bomb->getY()]->isDestructible())));
      if (i && this->_map->getPlan()[bomb->getX() + (i * j * BLOCKSIZE)][bomb->getY()])
	this->explodeObj(this->_map->getPlan()[bomb->getX() + (i * j * BLOCKSIZE)][bomb->getY()]);
    }
  for (int i = -1; i < 2; ++i)
    {
      int j = -1;
      while ((i || j) && (++j < bomb->getRange())
	     && (!this->_map->getPlan()[bomb->getX()][bomb->getY() + (i * j * BLOCKSIZE)]
		 || !(this->_map->getPlan()[bomb->getX()][bomb->getY() + (i * j * BLOCKSIZE)]->isBlocking()
		      || this->_map->getPlan()[bomb->getX()][bomb->getY() + (i * j * BLOCKSIZE)]->isDestructible())));
      if (i && this->_map->getPlan()[bomb->getX()][bomb->getY() + (i * j * BLOCKSIZE)])
	this->explodeObj(this->_map->getPlan()[bomb->getX()][bomb->getY() + (i * j * BLOCKSIZE)]);
    }
  for (int i = 0; i < this->_players.size(); ++i)
    if (this->_players[i]->getX() == bomb->getX()
	    && this->_players[i]->getY() == bomb->getY())
      this->_players[i]->remove();
}

bool Bomberman::Game::getBonus(Bomberman::Character *player, Bomberman::Character::ACTION action)
{
  Bomberman::Obj *obj;
  Bomberman::Game::BonusMemFn fn;

  if ((obj = this->_map->getPlan()[Bomberman::Map::getRoundPosition(
	  player->getX() + Bomberman::Game::positions[action][0])]
  [Bomberman::Map::getRoundPosition(player->getY() + Bomberman::Game::positions[action][0])])
      && (fn = this->_bonus.find(obj->getType())->second))
    (this->*fn)(player, obj);
  return (true);
}

void Bomberman::Game::handleBonus()
{
  for (int i = 0; i < this->_players.size(); ++i)
    {
      if (this->_players[i]->getGodTime() &&
	  this->_irr.getDevice()->getTimer()->getTime() > this->_players[i]->getGodTime())
	this->_players[i]->setGodTime(0);
      if (this->_players[i]->getSpeedTime() &&
	  this->_irr.getDevice()->getTimer()->getTime() > this->_players[i]->getSpeedTime())
	this->_players[i]->setSpeedTime(0);
    }
}

void Bomberman::Game::handleMovements()
{
  std::map<irr::EKEY_CODE, std::pair<int, Bomberman::Character::ACTION>>::const_iterator it;
   for (it = this->_events[0].begin(); it != _events[0].end(); ++it)
    //    for (int i = 0; i < this->_players[it->second.first]->getSpeed(); ++i)
    if (this->_irr.event.getKeys()[it->first] && it->second.first < this->_players.size()
	&& this->getBonus(this->_players[it->second.first], it->second.second)
	&& this->_map->checkPosition(
	    this->_players[it->second.first]->getX() + Bomberman::Game::positions[it->second.second][0],
	    this->_players[it->second.first]->getY() + Bomberman::Game::positions[it->second.second][1],
	    float(BLOCKSIZE - 0.1)))
      this->_players[it->second.first]->do_action(it->second.second);
}

void Bomberman::Game::handleActions()
{
  std::map<irr::EKEY_CODE, std::pair<int, Bomberman::Character::ACTION>>::const_iterator it;
  for (it = this->_events[1].begin(); it != _events[1].end(); ++it)
    if (this->_irr.event.getKeys()[it->first] && it->second.first < this->_players.size())
      this->_players[it->second.first]->do_action(it->second.second);
}

void Bomberman::Game::handleTime()
{
  irr::u32 now = this->_irr.getDevice()->getTimer()->getTime();
  int i = -1;

  while (++i < this->_map->getObjs().size())
    if (this->_map->getObjs()[i]->getType() == Bomberman::BOMB
	&& this->_map->getObjs()[i]->getExplosionTime()
	&& now > this->_map->getObjs()[i]->getExplosionTime())
      this->explodeObjs(static_cast<Bomberman::Bomb *>(this->_map->getObjs()[i]));
}

int Bomberman::Game::handleEvents()
{
  std::vector<Bomberman::Character *>::const_iterator it;
  int players_alive = 0;

  this->_map->createPlan();
  if (this->_irr.event.getKeys()[irr::KEY_KEY_P])
    _pause = !_pause;
  if (!_pause)
    {
      handleTime();
      handleBonus();
      handleMovements();
      handleActions();
    }
  for (it = this->_players.begin(); it != this->_players.end(); ++it)
    if ((*it)->isDestructible() || (!(*it)->isDestructible() && (*it)->getGodTime()))
      players_alive++;
    else
      (*it)->die();
  return (!this->_players[0]->_dead);
}

Bomberman::Map *Bomberman::Game::run()
{
  irr::scene::ICameraSceneNode *camera = this->_irr.getSmgr()
					     ->addCameraSceneNode(0, irr::core::vector3df(0, (12 * BLOCKSIZE), -40),
								  irr::core::vector3df(0, 0, 0));
  camera->setNearValue(10);
  irr::video::ITexture *background = this->_irr.getDriver()->getTexture("./assets/Te/sky-clouds.jpg");
  int lastFPS = -1;
  _pause = 0;
  while (this->_irr.getDevice()->run() && handleEvents())
    {
      if (this->_irr.event.getKeys()[irr::KEY_ESCAPE])
	{
	  for (auto &&item : this->_players)
	    item->die();
	  return (this->_map);
	}
      if (this->_irr.getDevice()->isWindowActive())
	{
	  this->_irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
	  this->_irr.getDriver()->draw2DImage(background, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
					      irr::core::rect<irr::s32>(0, 0, 1920, 1080));
	  !_pause ? this->_irr.getSmgr()->drawAll() : this->_irr.getGui()->drawAll();
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
  for (auto &&item : this->_players)
    item->die();
  _players[0]->_dead ? this->printLose() : this->printWin();
  return (NULL);
}

void                Bomberman::Game::printWin()
{
    irr::video::ITexture *background = this->_irr.getDriver()->getTexture("./assets/Te/sky-clouds.jpg");

  if (this->_irr.getDevice()->isWindowActive())
    {
      irr::video::ITexture *logo = this->_irr.getDriver()->getTexture("./assets/YouWon.png");
      _irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
      this->_irr.getDriver()->draw2DImage(background, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
					  irr::core::rect<irr::s32>(0, 0, 1920, 1080));
      this->_irr.getSmgr()->drawAll();
      this->_irr.getDriver()->draw2DImage(logo, irr::core::rect<irr::s32>((1920 / 2) - (380 / 2),
									  1080 / 2 - (84 / 2),
									  (1920 / 2) + (380 / 2) + 10,
									  1080 / 2 + (84 / 2) + 10),
					  irr::core::rect<irr::s32>(0, 0, 380, 84), 0, 0, true);
      _irr.getDriver()->endScene();
      sleep(3);
    }
}

void                Bomberman::Game::printLose()
{
  irr::video::ITexture *background = this->_irr.getDriver()->getTexture("./assets/Te/sky-clouds.jpg");

  if (this->_irr.getDevice()->isWindowActive())
    {
      irr::video::ITexture *logo = this->_irr.getDriver()->getTexture("./assets/YouLose.png");
      _irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
      this->_irr.getDriver()->draw2DImage(background, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
					  irr::core::rect<irr::s32>(0, 0, 1920, 1080));
      this->_irr.getSmgr()->drawAll();
      this->_irr.getDriver()->draw2DImage(logo, irr::core::rect<irr::s32>((1920 / 2) - (380 / 2),
									  1080 / 2 - (84 / 2),
									  (1920 / 2) + (380 / 2) + 10,
									  1080 / 2 + (84 / 2) + 10),
					  irr::core::rect<irr::s32>(0, 0, 380, 84), 0, 0, true);
      _irr.getDriver()->endScene();
      sleep(3);
    }
}

void Bomberman::Game::bonus_bomb_range(Bomberman::Character *player, Bomberman::Obj *obj)
{
  std::cout << "BOMB RANGE" << std::endl;
  obj->remove();
  player->add_bomb(static_cast<Bomberman::Bomb *>(this->_map->createObj("", "", 0, 0, BOMB)));
}

void Bomberman::Game::bonus_bomb_nb(Bomberman::Character *player, Bomberman::Obj *obj)
{
  std::cout << "BOMB NB" << std::endl;
  obj->remove();
  player->setBombRange();
}

void Bomberman::Game::bonus_god(Bomberman::Character *player, Bomberman::Obj *obj)
{
  std::cout << "BONUS GOD" << std::endl;
  obj->remove();
  player->setGodTime(this->_irr.getDevice()->getTimer()->getTime() + 10000);
}

void Bomberman::Game::bonus_speed(Bomberman::Character *player, Bomberman::Obj *obj)
{
  std::cout << "BONUS SPEED" << std::endl;
  obj->remove();
  player->setSpeedTime(this->_irr.getDevice()->getTimer()->getTime() + 10000);
}
