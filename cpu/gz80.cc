#include <stdio.h>
#include "gz80.h"

gz80::gz80() {
  pc_ = 0x0;
}

void gz80::decodeOP(int address) {
  printf("0x%04x: 0x%02x\n", address, b->read(address));
  decode(address);
}

void gz80::decodeOP() {
  decodeOP(0x0000);
}

void gz80::attachBus(bus *bus) {
  b = bus;
}


char* rp[] = {"bc", "de", "hl", "sp"};
char* r[] = {"b", "c", "d", "e", "h", "l", "(hl)", "a"};
void gz80::decode(uint16_t addr) {
  uint8_t op = b->read(addr);

  uint8_t x = (op >> 6) & 0x3;
  uint8_t y = (op >> 3) & 0x7;
  uint8_t z = op & 0x7;

  uint8_t p = (y >> 1) & 0x3;
  uint8_t q = y & 0x1;

  printf("\t");
  int bytes = 1;

  switch (x) {
  case 0:
    switch(z) {
    case 0:
      switch(y) {
      case 0:
        printf("nop");
	break;
      case 1:
        printf("ld (0x%02x%02x), sp", b->read(addr+2), b->read(addr+1));
	bytes = 3;
	break;
      case 2:
        printf("STOP");
	break;
      case 3:
        printf("jr %+i", b->read(addr+1));
	++bytes;
	break;
      default:
        printf("jr cc[%i], %+i",  y - 4, b->read(addr+1));
	++bytes;
	break;
      }
      break;
    case 1:
      if(q == 0) {
        printf("ld %s, 0x%02x%02x", rp[p], b->read(addr+2), b->read(addr+1));
	bytes = 3;
      } else {
        printf("add hl, %s", rp[p]);
      }
      break;
    case 6:
      printf("ld %s, 0x%02x", r[y], b->read(addr+1));
      bytes++;
      break;
    default:
      goto unimplemented;
    }
    break;
    case 3:
      switch(z) {
      case 0:
        switch(y) {
	case 4:
	  printf("ld 0xff[%02x], a", b->read(addr+1));
	  bytes++;
	  break;
	default: goto unimplemented;
	}
	break;
      case 3:
        switch(y) {
        case 0:
          printf("jp 0x%02x%02x", b->read(addr+2), b->read(addr+1));
  	  bytes = 3;
	  break;
        default: goto unimplemented;
        }
      break;
      case 5: 
        switch (y) {
	case 1:
	  printf("call 0x%02x%02x",  b->read(addr+2), b->read(addr+1));
	  bytes = 3;
	  break;
	default: goto unimplemented;
	}
	break;
      default: goto unimplemented;
      }
    break;
    default: goto unimplemented;
  }
  printf("\n");
  return;

unimplemented:
  printf("unimplemented:\n x: %i\ty: %i\tz: %i\tp: %i\tq: %i\n", x,y,z,p,q);

}
