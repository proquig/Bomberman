//
// Created by cloquet on 10/05/16.
//

#include "Irrlicht.hpp"
#include "Exception.hpp"

Bomberman::Irrlicht::Irrlicht()
{
  irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL;
  this->_device = irr::createDevice(driverType, irr::core::dimension2d<irr::u32>(1920, 1080));

  if (this->_device == NULL)
    throw (exception("Can't Load OpenGL"));

  this->_device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

  this->_driver = _device->getVideoDriver();
  this->_smgr = _device->getSceneManager();
}

Bomberman::Irrlicht::~Irrlicht()
{
}

irr::IrrlichtDevice *Bomberman::Irrlicht::get_device() const
{
  return _device;
}

irr::video::IVideoDriver *Bomberman::Irrlicht::get_driver() const
{
  return _driver;
}

irr::scene::ISceneManager *Bomberman::Irrlicht::get_smgr() const
{
  return _smgr;
}
