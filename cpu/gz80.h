#ifndef __GZ80_H__
#define __GZ80_H__

#include "cpuInterface.h"
#include <stdint.h>

class gz80 : public cpuInterface {

public:
 gz80();
 void decodeOP(int);
 void decodeOP();
 void attachBus(bus*);

private:
 void decode(uint16_t);
 uint16_t pc_;
 uint16_t af_;
 uint16_t bc_;
 uint16_t de_;
 uint16_t hl_;
 uint16_t sp_;

 bus *b;
};

#endif
