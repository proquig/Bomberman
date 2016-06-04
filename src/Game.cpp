//
// Created by cloquet on 24/05/16.
//

#include <Bomb.hpp>
#include <Menu.hpp>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <IA.hpp>
#include "Game.hpp"

const std::vector<std::pair<std::string, std::pair<int, int>>> Bomberman::Game::_players_conf = {
	{"./assets/ninja/nskinwh.jpg", {(MAPSIZE_X / 2) - (4 * BLOCKSIZE), -((MAPSIZE_Y / 2) - (4 * BLOCKSIZE))}},
	{"./assets/ninja/nskinbl.jpg", {-((MAPSIZE_X / 2) - (4 * BLOCKSIZE)), (MAPSIZE_Y / 2) - (4 * BLOCKSIZE)}}
};

const std::map<Bomberman::TYPE, Bomberman::Game::BonusMemFn> Bomberman::Game::_bonus = {
	{Bomberman::B_BOMB_R, &Bomberman::Game::bonus_bomb_range},
	{Bomberman::B_BOMB_N, &Bomberman::Game::bonus_bomb_nb},
	{Bomberman::B_STAR, &Bomberman::Game::bonus_god},
	{Bomberman::B_BOOT, &Bomberman::Game::bonus_speed}
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
  for (int i = 0; i < this->_nb_players; ++i)
    {
      this->_players.push_back(static_cast<Bomberman::Character *>(this->_map->createObj("./assets/ninja/ninja.b3d",
											 this->_players_conf[i].first,
											 this->_players_conf[i].second.first,
											 this->_players_conf[i].second.second,
											 Bomberman::CHARACTER)));
      // TODO : Define if IA
      this->_players.back()->setIa(new IA(this->_map, this->_players.back()));
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

Bomberman::Game::Game(/*size_t nb, */const std::string &name) : _irr(Bomberman::Irrlicht::instance())
/*_nb_players(nb)*/
{
  std::vector<std::string> data;
  std::ifstream file("save.txt");
  std::string line;
  std::string word;
  std::stringstream ss;

  this->_map = new Bomberman::Map();
  if (!file)
    throw std::runtime_error("Invalid file");
  while (std::getline(file, line))
    {
      ss << line;
      while (std::getline(ss, word, ';'))
	data.push_back(word);
      ss.clear();
      line.clear();
      if (atoi(data[2].c_str()) == 4)
	{
	  this->_players.push_back(static_cast<Bomberman::Character *>(this->_map->createObj(data[3], data[4], atof(data[0].c_str()), atof(data[1].c_str()), (TYPE)atoi(data[2].c_str()))));
	  this->_players.back()->add_bomb(static_cast<Bomberman::Bomb *>(this->_map->createObj("", "", 0, 0, BOMB)));
	}
      else if (atoi(data[2].c_str()) != 2)
	this->_map->createObj(data[3], data[4], (float) atof(data[0].c_str()), (float) atof(data[1].c_str()), (TYPE)atoi(data[2].c_str()));
      data.clear();
    }
  this->_map->createMap();
  this->_nb_players = this->_players.size();
}

Bomberman::Game::~Game()
{
}

void Bomberman::Game::explodeObjs(Bomberman::Bomb *bomb)
{
  int stop = 0;
  int i = -1;
  std::srand(std::time(0));

  while (!stop && ++i < bomb->getRange())
    for (int j = -1; j < 2; ++j)
      {
	if (this->_map->getPlan()[bomb->getX() + (i * j * BLOCKSIZE)][bomb->getY()]
	    && this->_map->getPlan()[bomb->getX() + (i * j * BLOCKSIZE)][bomb->getY()]->isDestructible())
	  {
	    this->_map->getPlan()[bomb->getX() + (i *j * BLOCKSIZE)][bomb->getY()]->remove();
	    if (!(std::rand() % 2))
	      this->_map->createObj("", "", bomb->getX() + (i *j * BLOCKSIZE), bomb->getY(), Bomberman::BONUS);
	  }
	if (this->_map->getPlan()[bomb->getX()][bomb->getY() + (i * j * BLOCKSIZE)]
	    && this->_map->getPlan()[bomb->getX()][bomb->getY() + (i * j * BLOCKSIZE)]->isDestructible())
	  {
	    this->_map->getPlan()[bomb->getX()][bomb->getY() + (i * j * BLOCKSIZE)]->remove();
	    if (!(std::rand() % 2))
	      this->_map->createObj("", "", bomb->getX(), bomb->getY() + (i *j * BLOCKSIZE), Bomberman::BONUS);
	  }
	stop = ((this->_map->getPlan()[bomb->getX() + (i * j * BLOCKSIZE)][bomb->getY()]
		  && this->_map->getPlan()[bomb->getX() + (i * j * BLOCKSIZE)][bomb->getY()]->isBlocking())
		|| (this->_map->getPlan()[bomb->getX()][bomb->getY() + (i * j * BLOCKSIZE)]
		  && this->_map->getPlan()[bomb->getX()][bomb->getY() + (i * j * BLOCKSIZE)]->isBlocking()));
      }
  //int i = -1;

  //std::cout << (int)this->getX() << std::endl;
  //std::cout << (int)this->getX() - ((int)this->getX() % 5) << std::endl;
  //std::cout << ">" << ((((int)this->getX() + (int)(this->getX() > 0) * (5 - 1)) / 5) * 5) << std::endl;
  /*int x = Bomberman::Map::getRoundPosition(bomb->getX());
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
*/
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

bool Bomberman::Game::getBonus(Bomberman::Character *player, Bomberman::Character::ACTION action)
{
  Bomberman::Obj *obj;
  Bomberman::Game::BonusMemFn fn;

  if ((obj = this->_map->getPlan()[Bomberman::Map::getRoundPosition(player->getX() + Bomberman::Game::positions[action][0])]
  [Bomberman::Map::getRoundPosition(player->getY() + Bomberman::Game::positions[action][0])])
    && (fn = this->_bonus.find(obj->getType())->second))
      (this->*fn)(player, obj);
  return (true);
}

void Bomberman::Game::handleBonus()
{
  for (int i = 0; i < this->_players.size(); ++i)
    {
      if (this->_players[i]->getGodTime() && this->_irr.getDevice()->getTimer()->getTime() > this->_players[i]->getGodTime())
	this->_players[i]->setGodTime(0);
      if (this->_players[i]->getSpeedTime() && this->_irr.getDevice()->getTimer()->getTime() > this->_players[i]->getSpeedTime())
	this->_players[i]->setSpeedTime(0);
    }
}

void Bomberman::Game::handleMovements()
{
  std::map<irr::EKEY_CODE, std::pair<int, Bomberman::Character::ACTION>>::const_iterator it;
  for (it = this->_events[0].begin(); it != _events[0].end(); ++it)
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
    {
      if ((*it)->isDestructible() || (!(*it)->isDestructible() && (*it)->getGodTime()))
	players_alive++;
      else
	(*it)->die();
    }
  return (players_alive == this->_nb_players);
}

Bomberman::Map *Bomberman::Game::run()
{
  irr::scene::ICameraSceneNode *camera = this->_irr.getSmgr()->addCameraSceneNode(0, irr::core::vector3df(0, (12 * BLOCKSIZE), -40),
								  irr::core::vector3df(0, 0, 0));
  camera->setNearValue(10);
  irr::video::ITexture *background = this->_irr.getDriver()->getTexture("./assets/Te/sky-clouds.jpg");
  int lastFPS = -1;
  _pause = 0;
  while (this->_irr.getDevice()->run() && handleEvents())
    {
      if (this->_irr.event.getKeys()[irr::KEY_ESCAPE])
	return (this->_map);
      if (this->_irr.getDevice()->isWindowActive())
	{
	  this->_irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
	  this->_irr.getDriver()->draw2DImage(background, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
					      irr::core::rect<irr::s32>(0, 0, 1920, 1080));
	  if (!_pause)
	    this->_irr.getSmgr()->drawAll();
	  !_pause ? this->_irr.getSmgr()->drawAll(): this->_irr.getGui()->drawAll();
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
  return (NULL);
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
