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

class							Map;

# include						"Obj.hpp"
# include						"Irrlicht.hpp"
# include						"AnimationEndCallback.hpp"
# include						"Bomb.hpp"

# define						START_FRAME 184
# define						START_WALK_FRAME 1
# define						END_WALK_FRAME 15

namespace						Bomberman
{
  class							IA;

  class							Character : public Obj
  {
  public:
    enum						ACTION
      {
	GO_UP = 0,
	GO_DOWN = 1,
	GO_LEFT = 2,
	GO_RIGHT = 3,
	PUT_BOMB,
	JUMP
      };
  private:
    typedef						void (Character::*CharMemFn)(Character::ACTION);
    std::vector<Bomberman::Bomb*>			_bombs;
    float 						_range;
    int 						_speed;
    irr::u32						_bombTime;
    irr::u32						_godTime;
    irr::u32						_speedTime;
    IA							*_ia;

  public:
    Character(const std::string &mesh_path, const std::string &texture_path, float x, float y, Bomberman::TYPE type);
    ~Character();
    //float						getRange() const;
    void						set_pos(ACTION direction);
    void						set_orientation(ACTION direction);
    void						add_bomb(Bomb *bomb);
    void						put_bomb(ACTION action);
    void						do_action(ACTION action);
    void						jump(ACTION action);
    void						afk();

    void						setBombRange();
    irr::u32						getGodTime() const;
    irr::u32						getSpeedTime() const;
    void						setGodTime(irr::u32 time);
    void						setSpeedTime(irr::u32 time);
    void						setIa(IA *ia);
    int 						getSpeed() const;
    virtual void die() override;

    //void remove();
  };
}

#endif
