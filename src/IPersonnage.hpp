//
// Created by cloquet on 05/05/16.
//

#ifndef CPP_INDIE_STUDIO_IPERSONNAGE_HPP
#define CPP_INDIE_STUDIO_IPERSONNAGE_HPP


class 			IPersonnage
{
 public:
  virtual		 ~IPersonnage();
  virtual void		attack(IPersonnage*) = 0;
  virtual int 			takeDammage(int) = 0;
  virtual void 			move(size_t, size_t) = 0;
};


#endif //CPP_INDIE_STUDIO_IPERSONNAGE_HPP
