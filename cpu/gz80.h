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
 void execute();

private:
 void decode(uint16_t);
 uint16_t pc;
 uint16_t af;
 uint16_t bc;
 uint16_t de;
 uint16_t hl;
 uint16_t sp;
 void write_r(uint8_t, uint8_t);

 
 uint16_t* rp_[4];

 bus *b;
};

#endif
