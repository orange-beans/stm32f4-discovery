#include "mbed.h"

DigitalOut LD3(PD_13);

int main() {
  while(1) {
    LD3 = 1;
    wait(1.0f);
    LD3 = 0;
    wait(1.0f);
  }
}
