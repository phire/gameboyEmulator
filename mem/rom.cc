#include "rom.h"

#include <stdlib.h>

rom::rom(std::ifstream& file, int size) {
  data = (uint8_t*) malloc(size);
  file.read((char *) data, size);
  romsize = size;
  file.close();
}

int rom::read(int address) {
  if(address < romsize)
    return data[address];
  return 0x00;
}

void rom::write(int address, int value) {
}
