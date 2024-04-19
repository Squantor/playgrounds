#ifndef HIGHER_HPP
#define HIGHER_HPP

#include <middle.hpp>

struct higher : public middle {
  higher() {}
  virtual void doit();
};

#endif