#include "ram.h"
#include <stdlib.h>

ram::ram(int address, int size) {
  data = (uint8_t *) malloc(size);
  baseAddress = address;
  topAddress = address + size;
}

int ram::read(int address) {
  if(address >= baseAddress && address < topAddress)
    return data[address - baseAddress];
  return 0;
}

void ram::write(int address, int data) {
  if(address >= baseAddress && address < topAddress)
    *(data + (uint8_t *) (address - baseAddress)) = data;
}

