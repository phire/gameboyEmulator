#include "mem/bus.h"
#include "cpu/cpuInterface.h"
#include "cpu/gz80.h"
#include "mem/rom.h"
#include "mem/ram.h"

int main() {
  cpuInterface *cpu = new gz80();
  bus *b = new bus(16, 8);
  b->attach(new ram(0xff80, 79));

  std::ifstream bios;
  bios.open("gbc_bios.bin", std::fstream::in);
  b->attach(new rom(bios, 0x900));

  cpu->attachBus(b);
  for(int i = 0; i < 40; i++) {
    cpu->decodeOP();
    cpu->execute();
  }
  return 0;
}

