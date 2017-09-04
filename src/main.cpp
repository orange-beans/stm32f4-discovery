#include "mbed.h"
#include <WS2812.h>

// Local Constant Defines
// TODO: How to move to another file?
#define HIGH 1
#define LOW  0

#define NUM_COLORS 6

int BLUE_COLOR   =  0xff0000ff;
int RED_COLOR    =  0xffff0000;
int GREEN_COLOR  =  0xff00ff00;
int YELLOW_COLOR =  0xffffff00;
int ORANGE_COLOR =  0xffff8000;
int PINK_COLOR   =  0xfff00fff;

int colorbuf[NUM_COLORS] = {0xff0000ff,0xffff0000,0xff00ff00,0xffffff00,0xffff8000,0xfff00fff};

// Pin Assignments
DigitalOut LD3(PD_13);
PwmOut LD4(PD_12);

// TODO: PA_9 as UART is not working because it is in use for the USB port
Serial dev(PB_6, PB_7, 115200);

// NOTE: timer is critical for different platforms:
// DO USE Oscilloscope to determine the actual timing settings
// K64F, KL46Z: 0, 5, 5, 0
// LPC1768: 3, 11, 10, 11
// NUCLEO_F401RE: 3, 12, 9, 12
// NUCELO_F746ZG: 32, 105, 70, 123

// WS2812 ws(PB_5, 1, 7, 7, 10, 15);
WS2812 ws(PD_7, 1, 3, 7, 9, 9);

int main() {

  int counter = 0;

  LD4.period_ms(200);
  LD4.write(0.1f);

  while(1) {
    LD3 = HIGH;
    wait(0.5f);
    LD3 = LOW;
    wait(0.5f);

    ws.write(&colorbuf[counter]);
    counter ++;
    if (counter >= 5) counter = 0;
    dev.printf("STM32 Testing 2\n");
  }
}
