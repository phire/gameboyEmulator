#include "mem/bus.h"
#include "cpu/cpuInterface.h"
#include "cpu/gz80.h"
#include "mem/rom.h"

int main() {
  cpuInterface *cpu = new gz80;
  bus *b = new bus(16, 8);
  b->attach(new rom());
  return 0;
}

