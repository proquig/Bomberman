//
// Created by cloquet on 01/06/16.
//

#include <fstream>
#include <Exception.hpp>
#include "Save.hpp"

Bomberman::Save::Save(Bomberman::Map *map)
{
  if (map)
    {
      std::vector<Bomberman::Obj *> save = map->getObjs();
      try
	{
	  std::ofstream file;
	  file.open("save.txt");
	  for (std::vector<Bomberman::Obj *>::iterator it = save.begin(); it < save.end(); ++it)
	    if ((*it)->isDestructible() || (*it)->isBlocking())
	      file << (*it)->getX() << ";" << (*it)->getY() << ";" << (*it)->getType()
	    << ";" << ((*it)->getMeshName() == "" ? " " : (*it)->getMeshName())
	    << ";" << ((*it)->getTextureName() == "" ? " " : (*it)->getTextureName())
	    << "\n";
	  file.close();
	}
      catch (exception &e)
	{
	  std::cerr << e.what() << std::endl;
	}
    }
}

Bomberman::Save::~Save()
{

}
