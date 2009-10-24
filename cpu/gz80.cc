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
char* rp2[] = {"bc", "de", "hl", "af"};
char* r[] = {"b", "c", "d", "e", "h", "l", "(hl)", "a"};
char* alu[] = {"add a,", "adc a,", "sub", "sbc a,", "and", "xor", "or", "cp"};
char* cc[] = {"nz", "z", "nc", "c"};
char* rot[] = {"rlc", "rrc", "rl", "rr", "sla", "sra", "sll", "srl"};

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
        printf("jr %+i", b->read(addr+1)); // FIXME: make signed.
	++bytes;
	break;
      default:
        printf("jr %s, %+i",  cc[y-4], b->read(addr+1));
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
    case 2:
      printf("ld ");
      if(q) printf("a, ");
      switch(p) {
        case 0:
	  printf("(bc)");
	  break;
	case 1:
	  printf("(de)");
	  break;
	case 2:
	  printf("(hl+)");
	  break;
	case 3:
	  printf("(hl-)");
	  break;
      }
      if (!q) printf(", a");
      break;
    case 3:
      if(q == 0) {
        printf("inc %s", rp[p]);
      } else {
        printf("dec %s", rp[p]);
      }
      break;
    case 4:
      printf("inc %s", r[y]);
      break;
    case 5:
      printf("dec %s", r[y]);
      break;
    case 6:
      printf("ld %s, 0x%02x", r[y], b->read(addr+1));
      bytes++;
      break;
    case 7:
      switch (y) {
      case 0:
        printf("rlca");
        break;
      case 1:
        printf("rrca");
        break;
      case 2:
        printf("rla");
        break;
      case 3:
        printf("rra");
        break;
      case 4:
        printf("dda");
        break;
      case 5:
        printf("cpl");
        break;
      case 6:
        printf("scf");
        break;
      case 7:
        printf("ccf");
        break;
      }
      break;
    }
    break;
  case 1:
    if(y == 6 && z == 6) {
      printf("halt");
    } else {
      printf("ld %s, %s", r[y], r[z]);
    }
    break;
  case 2:
    printf("%s %s", alu[y], r[z]);
    break;
  case 3:
    switch(z) {
    case 0:
      switch(y) {
      default:
        printf("ret %s", cc[y]);
	break;
      case 4:
	printf("ld 0xff[%02x], a", b->read(addr+1));
	bytes++;
	break;
      case 5:
        printf("add sp, %+i", b->read(addr+1)); //FIXME: make signed
	bytes++;
	break;
      case 6:
        printf("ld a, 0xff[%02x]", b->read(addr+1));
	bytes++;
        break;
      case 7:
        printf("ld hl, (sp%+i)", b->read(addr+1));  //FIXME: make signed
	bytes++;
        break;
      }
      break;
    case 1:
      if(q == 0) {
        printf("pop %s", rp2[p]);
      } else {
        switch (p) {
        case 0:
	  printf("ret");
	  break;
	case 1:
	  printf("reti");
	  break;
	case 2:
	  printf("jp (hl)");
	  break;
	case 3:
	  printf("ld sp, hl");
	  break;
	}
      }
      break;
    case 2:
      switch (y) {
      default:
        printf("jp %s, 0x%02x%02x", cc[y],  b->read(addr+2), b->read(addr+1));
	bytes = 3;
        break;
      case 4:
        printf("ld 0xff[c], a");
	break;
      case 5:
        printf("ld (0x%02x%02x), a",  b->read(addr+2), b->read(addr+1));
	bytes = 3;
	break;
      case 6:
        printf("ld a, 0xff[c]");
        break;
      case 7:
        printf("ld a, (0x%02x%02x)",  b->read(addr+2), b->read(addr+1));
	bytes = 3;
	break;
      }
      break;
    case 3:
      switch(y) {
      case 0:
        printf("jp 0x%02x%02x", b->read(addr+2), b->read(addr+1));
        bytes = 3;
        break;
      case 1:
        bytes++;
        op = b->read(addr);
	x = (op >> 6) & 0x3;
	y = (op >> 3) & 0x7;
	z = op & 0x7;
        switch(x) {
        case 0:
	  printf("%s %s", rot[y], r[z]);
	  break;
	case 1:
	  printf("bit %i, %s", y, r[z]);
	  break;
	case 2:
	  printf("res %i, %s", y, r[z]);
	  break;
	case 3:
	  printf("set %i, %s", y, r[z]);
	  break;
	}
	break;
      case 6:
        printf("di");
	break;
      case 7:
        printf("ei");
	break;
      default:
        printf("(removed)");
      }
      break;
    case 4:
      if(y < 4) {
        printf("call %s, 0x%02x%02x", cc[y], b->read(addr+2), b->read(addr+1));
	bytes = 3;
      } else printf("(removed)");
      break;
    case 5:
      switch (q) {
      case 0:
        printf("push %s", rp2[p]);
	break;
      case 1:
        if(p == 0) {
          printf("call 0x%02x%02x", b->read(addr+2), b->read(addr+1));
          bytes = 3;
	} else printf("(removed)");
        break;
      }
      break;
    case 6:
      printf("%s %i", alu[y], b->read(addr+2));
      break;
    case 7:
      printf("rst 0x%02x", y*8);
      break;
    default: goto unimplemented;
    }
    break;
  }
  printf("\n");
  return;

unimplemented:
  printf("unimplemented:\n x: %i\ty: %i\tz: %i\tp: %i\tq: %i\n", x,y,z,p,q);

}
