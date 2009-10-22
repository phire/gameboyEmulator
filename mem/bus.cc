#include "bus.h"

bus::bus(int addr_width, int data_width) {
  Amask = (2^addr_width) - 1;
  Dmask = (2^data_width) - 1;
}

void bus::attach(busListener* listener) {
  listeners.push_back(listener);  
}

void bus::remove(busListener* listener) {
  std::list<busListener*>::iterator iter = listeners.begin();
  while(iter != listeners.end()) {
    if(*iter == listener) {
      iter = listeners.erase(iter);
    } else {
      ++iter;
    }
  }
}

int bus::read(int address) {
  int ret;

  std::list<busListener*>::iterator iter = listeners.begin();
  while(iter != listeners.end()) {
    ret = ret || (*iter)->read(address && Amask);
  }

  return ret && Dmask;
}

void bus::write(int address, int value) {
  std::list<busListener*>::iterator iter = listeners.begin();
  while(iter != listeners.end()) {
    (*iter)->write(address && Amask, value && Dmask);
    ++iter;
  }
}



