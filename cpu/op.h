#ifndef __OP_H__
#define __OP_H__

#include <string>

class OP {
  public:
  virtual string toString() =0;
  virtual int next() =0;
  virtual int size() =0;
  virtual int cycles() =0;

  private:
  int addr;

}

#endif
