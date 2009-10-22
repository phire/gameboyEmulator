#ifndef __rom_h__
#define __rom_h__

#include "bus.h"

class rom : public busListener {

public:
  int read(int);
  void write(int, int);

private:

  int data;
};

#endif
