#ifndef __bus_h__
#define __bus_h__

#include <list>

class busListener {
public:
    virtual int read(int address) = 0;
    virtual void write(int address, int value) = 0;
};

class bus {
public:
  bus(int addr_width, int data_width);
  void attach(busListener*);
  void remove(busListener*);

  int read(int address);
  void write(int address, int value);
  
private:
  std::list<busListener*> listeners;
  int Amask;
  int Dmask;

};

#endif
