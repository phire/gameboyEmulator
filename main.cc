#include "mem/bus.h"
#include "cpu/cpuInterface.h"
#include "cpu/gz80.h"
#include "mem/rom.h"

int main() {
  cpuInterface *cpu = new gz80();
  bus *b = new bus(16, 8);


  std::ifstream bios;
  bios.open("gbc_bios.bin", std::fstream::in);
  b->attach(new rom(bios, 0x900));

  cpu->attachBus(b);
  cpu->decodeOP(0x0);
  cpu->decodeOP(0x03);
  cpu->decodeOP(0x05);
  cpu->decodeOP(0x7c);
  return 0;
}

