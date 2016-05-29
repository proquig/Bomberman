//
// Character.hpp for indie_studio in /home/proqui_g/rendu/cpp_indie_studio/includes
// 
// Made by Guillaume PROQUIN
// Login   <proqui_g@epitech.net>
// 
// Started on  Fri May 27 18:46:24 2016 Guillaume PROQUIN
// Last update Sun May 29 20:32:35 2016 Guillaume PROQUIN
//

#ifndef							__CHARACTER_HPP__
# define						__CHARACTER_HPP__

# include						"Obj.hpp"
# include						"Irrlicht.hpp"
# include						"AnimationEndCallback.hpp"
# include						"Bomb.hpp"

# define						START_FRAME 0
# define						START_WALK_FRAME 1
# define						END_WALK_FRAME 13

namespace						Bomberman
{
  class							Character : public Obj
  {
  public:
    enum						ACTION
      {
	GO_UP,
	GO_DOWN,
	GO_LEFT,
	GO_RIGHT,
	PUT_BOMB,
	JUMP
      };
  private:
    typedef						void (Character::*CharMemFn)(Character::ACTION);
    static const std::map<irr::EKEY_CODE, ACTION>	_events;
    std::vector<Bomberman::Bomb*>			_bombs;
  public:
    //Character();
    //Character(Bomberman::Map *map);
    //Character(float x, float y);
    Character(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type);
    ~Character();
    //static Bomberman::Obj*				create(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type);
    void						set_pos(ACTION direction);
    void						set_orientation(ACTION direction);
    void						add_bomb();
    void						put_bomb(ACTION action);
    void						do_action(ACTION action);
    void						jump(ACTION action);
    void						afk();
    void						catch_event(std::vector<bool> keys);
    void						handle_event();
  };
}

#endif
