//
// Created by cloquet on 05/05/16.
//

#ifndef CPP_INDIE_STUDIO_APERSONNAGE_HPP
#define CPP_INDIE_STUDIO_APERSONNAGE_HPP

#include "IPersonnage.hpp"

class 		APersonnage : public IPersonnage
{
 private:
  int		_hp;
  size_t 	_x;
  size_t 	_y;

 public:
  APersonnage();
  virtual ~APersonnage();

  /*  Getter  */
  int 		getHP() const;
  size_t 	getX() const;
  size_t 	getY() const;

  /*  Setter  */
  int 		setHP(int);
  size_t 	setX(size_t);
  size_t 	setY(size_t);

  void		attack(IPersonnage*);
  int 			takeDammage(int);
  void 			move(size_t, size_t);
};


#endif //CPP_INDIE_STUDIO_APERSONNAGE_HPP
