#include <iostream>
#include "gz80.h"


void gz80::decode(int address) {
  std::cout << "Decoding instruction at " << address << "\n";
}

void gz80::decode() {
  decode(0x0000);
}
