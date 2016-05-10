//
// Created by cloquet on 10/05/16.
//

#ifndef CPP_INDIE_STUDIO_EXCEPTION_HPP
#define CPP_INDIE_STUDIO_EXCEPTION_HPP


# include	<exception>
# include	<iostream>
# include	<string>

class exception : public std::exception
{
 public:
  exception(const std::string &message);

  ~exception() throw();

  const char *what() const throw();

 private:
  std::string _msg;
};

#endif //CPP_INDIE_STUDIO_EXCEPTION_HPP
