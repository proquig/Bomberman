//
// Created by cloquet on 10/05/16.
//

#include "Exception.hpp"

exception::exception(const std::string &msg)
{
  this->_msg = msg;
}

exception::~exception() throw()
{

}

const char *exception::what() const throw()
{
  return (this->_msg.c_str());
}
