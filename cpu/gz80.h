#include "cpuInterface.h"
#include <stdint.h>

class gz80 : public cpuInterface {

public:
 void decode(int);
 void decode();

private:
 uint16_t pc_;
 uint16_t af_;
 uint16_t bc_;
 uint16_t de_;
 uint16_t sp_;
};
