#include "mbed.h"

// Local Constant Defines
// TODO: How to move to another file?
#define HIGH 1
#define LOW  0

// Pin Assignments
DigitalOut LD3(PD_13);
PwmOut LD4(PD_12);

// TODO: PA_9 as UART is not working
Serial dev(PB_6, PB_7, 115200);

int main() {

  LD4.period_ms(100);
  LD4.write(0.5f);

  while(1) {
    LD3 = HIGH;
    wait(0.5f);
    LD3 = LOW;
    wait(0.5f);
    dev.printf("STM32 Testing\n");
  }
}
