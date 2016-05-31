//
// Created by cloquet on 24/05/16.
//

#include <Bomb.hpp>
#include <Menu.hpp>
#include "Game.hpp"
#include "Character.hpp"
#include "Map.hpp"

# define X 90
# define Y 70

const float Bomberman::Game::positions[4][2] = {
	{0, 0.2f},
	{0, -0.2f},
	{-0.2f, 0},
	{0.2f, 0}
};

const std::map<irr::EKEY_CODE, std::pair<int, Bomberman::Character::ACTION>>			Bomberman::Game::_events[] = {
	{
		{irr::KEY_KEY_Z, std::make_pair(0, Bomberman::Character::GO_UP)},
		{irr::KEY_KEY_S, std::make_pair(0, Bomberman::Character::GO_DOWN)},
		{irr::KEY_KEY_Q, std::make_pair(0, Bomberman::Character::GO_LEFT)},
		{irr::KEY_KEY_D, std::make_pair(0, Bomberman::Character::GO_RIGHT)},
		{irr::KEY_UP, std::make_pair(1, Bomberman::Character::GO_UP)},
		{irr::KEY_DOWN, std::make_pair(1, Bomberman::Character::GO_DOWN)},
		{irr::KEY_LEFT, std::make_pair(1, Bomberman::Character::GO_LEFT)},
		{irr::KEY_RIGHT, std::make_pair(1, Bomberman::Character::GO_RIGHT)},
	},
	{
		{irr::KEY_SPACE, std::make_pair(0, Bomberman::Character::PUT_BOMB)},
		{irr::KEY_KEY_U, std::make_pair(0, Bomberman::Character::JUMP)}
	}
};

Bomberman::Game::Game(size_t nb) : _irr(Bomberman::Irrlicht::instance()),
			  _nbPlayer(nb)
{
  this->_map = new Bomberman::Map();
  this->_map->createMap();

   for (int i = 0; i < 20; ++i)
   {
     this->_map->createObjSomewhere(WALLOBJ, WALLTEXT, Bomberman::BRICK);
   }
  for (int j = 0; j < 50; ++j)
    {
      this->_map->createObjSomewhere(BOXOBJ, BOXTEXT, Bomberman::BOX);
    }
}

Bomberman::Game::~Game()
{
}

void Bomberman::Game::explodeObjs(Bomberman::Bomb *bomb)
{
  //std::vector<Bomberman::Obj*>::iterator it;


  /*
  //for (it = this->_map->getObjs().begin(); it != this->_map->getObjs().end(); ++it)
    //{
      std::cout << "ADDR: " << &it << std::endl;
      std::cout << (*it)->getType() << std::endl;
      if ((*it)->isBlockable()
	  && this->_map->checkPosition(
	      bomb->getX()
	      , bomb->getY(),
bomb->getRange()))
	(*it)->remove();
      	//this->_map->getObjs().erase(it);
    //}
    */
  int i = -1;

  while (++i < this->_map->getObjs().size())
    if (this->_map->getObjs()[i]->isDestructible()
	&& !this->_map->checkObjectPosition(this->_map->getObjs()[i], bomb->getX(), bomb->getY(), bomb->getRange()))
      {
	//std::cout << "YOU MUST DIE BITCH" << std::endl;
	this->_map->getObjs()[i]->remove();
	//this->_map->getObjs().erase(std::remove(this->_map->getObjs().begin(), this->_map->getObjs().end(), i), this->_map->getObjs().end());
      }
}

void Bomberman::Game::handleMovements()
{
  std::map<irr::EKEY_CODE, std::pair<int, Bomberman::Character::ACTION>>::const_iterator	it;
  for (it = this->_events[0].begin(); it != _events[0].end(); ++it)
    if (this->_irr.event.getKeys()[it->first] && it->second.first < this->_players.size()
      && this->_map->checkPosition(this->_players[it->second.first]->getX() + Bomberman::Game::positions[it->second.second][0],
				   this->_players[it->second.first]->getY() + Bomberman::Game::positions[it->second.second][1], 5))
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
    {
      if (this->_map->getObjs()[i]->getType() == Bomberman::BOMB
	  && this->_map->getObjs()[i]->getExplosionTime()
	  && now > this->_map->getObjs()[i]->getExplosionTime())
	{
	  this->explodeObjs(static_cast<Bomberman::Bomb *>(this->_map->getObjs()[i]));
	  static_cast<Bomberman::Bomb *>(this->_map->getObjs()[i])->explode();
	}
      if (this->_map->getObjs()[i]->getType() == Bomberman::BOMB
	  && this->_map->getObjs()[i]->getAnimation_time()
	  && now > this->_map->getObjs()[i]->getAnimation_time())
	static_cast<Bomberman::Bomb *>(this->_map->getObjs()[i])->clean();
    }
}

void Bomberman::Game::handleEvents()
{
  handleTime();
  handleMovements();
  handleActions();
}

void Bomberman::Game::run()
{
  this->_players.push_back(static_cast<Bomberman::Character*>(this->_map->createObjSomewhere("./assets/ninja/ninja.b3d", "./assets/ninja/nskinrd.jpg", Bomberman::CHARACTER)));
  this->_players.push_back(static_cast<Bomberman::Character*>(this->_map->createObjSomewhere("./assets/ninja/ninja.b3d", "./assets/ninja/nskinbr.jpg", Bomberman::CHARACTER)));
  this->_players.push_back(static_cast<Bomberman::Character*>(this->_map->createObjSomewhere("./assets/ninja/ninja.b3d", "./assets/ninja/nskingr.jpg", Bomberman::CHARACTER)));
  this->_players.push_back(static_cast<Bomberman::Character*>(this->_map->createObjSomewhere("./assets/ninja/ninja.b3d", "./assets/ninja/nskinwh.jpg", Bomberman::CHARACTER)));
  irr::scene::ICameraSceneNode *camera = this->_irr.getSmgr()->addCameraSceneNode(0, irr::core::vector3df(0, 70, -20),
									   irr::core::vector3df(0, 0, 0));
  camera->setNearValue(10);
  irr::video::ITexture *background = this->_irr.getDriver()->getTexture("./assets/Te/sky-clouds.jpg");
  int 	lastFPS = -1;
  for (int i = 0; i != 3; ++i)
      this->_players[i]->add_bomb(reinterpret_cast<Bomberman::Bomb*>(this->_map->createObj("", "", 0, 0, BOMB)));
  //this->_players[0]->add_bomb(static_cast<Bomberman::Bomb*>(this->_map->createObj("", "", 0, 0, BOMB)));
  while (this->_irr.getDevice()->run())
    {
      handleEvents();
      if (this->_irr.getDevice()->isWindowActive())
	{
	 this->_irr.getDriver()->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
	 this->_irr.getDriver()->draw2DImage(background, irr::core::rect<irr::s32>(0, 0, 1920, 1080),
					     irr::core::rect<irr::s32>(0, 0, 1920, 1080));
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
}
