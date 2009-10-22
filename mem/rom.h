#ifndef __rom_h__
#define __rom_h__

#include "bus.h"
#include <iostream>
#include <fstream>

class rom : public busListener {

public:
  rom(std::ifstream &, int);
  int read(int);
  void write(int, int);

private:
  int romsize;
  uint8_t* data;
};

#endif
