#ifndef __CPUINTERFACE_H__
#define __CPUINTERFACE_H__
#include "../mem/bus.h"

class cpuInterface {
public:
  virtual void decodeOP(int address) = 0; 
  virtual void decodeOP() = 0;
  virtual void attachBus(bus *) = 0;
};

#endif
