#ifndef __ram_h__
#define __ram_h__

#include "bus.h"
#include <stdint.h>

class ram : public busListener {

public:
  ram(int, int);
  int read(int);
  void write(int, int);

private:
  int baseAddress;
  int topAddress;
  uint8_t *data;
};

#endif
