#ifndef __GZ80OP_H__
#define __GZ80OP_H__

#include "op.h"
class gz80op : public OP {
  public:
  string toString();
  int next();
  int size();
  int cycles();

  private:
  
  
}

#endif
