//
// Created by cloquet on 10/05/16.
//

#include "Irrlicht.hpp"
#include "Exception.hpp"

Bomberman::Irrlicht Bomberman::Irrlicht::_instance = Bomberman::Irrlicht();

Bomberman::Irrlicht &Bomberman::Irrlicht::instance()
{
  return _instance;
}

Bomberman::Irrlicht::Irrlicht()
{
  irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL;
  this->_device = irr::createDevice(driverType, irr::core::dimension2d<irr::u32>(1920, 1080),\
   0, false, false, false, &this->event);

  if (this->_device == NULL)
    throw (exception("Can't Load OpenGL"));

  this->_device->setWindowCaption(L"jnique des meres");
}

Bomberman::Irrlicht &Bomberman::Irrlicht::operator=(const Bomberman::Irrlicht &)
{
  return *this;
}

Bomberman::Irrlicht::~Irrlicht()
{
  this->_device->drop();
}

irr::IrrlichtDevice *Bomberman::Irrlicht::getDevice() const
{
  return _device;
}

irr::video::IVideoDriver *Bomberman::Irrlicht::getDriver() const
{
  return _device->getVideoDriver();
}

irr::gui::IGUIEnvironment *Bomberman::Irrlicht::getGui() const
{
  return _device->getGUIEnvironment();
}

irr::scene::ISceneManager *Bomberman::Irrlicht::getSmgr() const
{
  return _device->getSceneManager();
}
