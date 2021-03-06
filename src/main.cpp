#include "mbed.h"
#include <WS2812.h>
#include <MAX31855.h>

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
DigitalOut LD5(PD_14);
DigitalOut LD6(PD_15);

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
//WS2812 ws(PD_7, 1, 3, 7, 9, 9);

//SPI Interfaces
SPI testSPI(PB_5, PB_4, PB_3);
//Thermocouples
max31855 max1(testSPI, PD_7);

int main() {
  LD4.period_ms(200);
  LD4.write(0.1f);

  max1.initialise();
  //Float value to hold temperature returned
  float fvalue = 0;

  while(1) {
    LD3 = HIGH;
    LD5 = LOW;
    wait(0.5f);
    LD3 = LOW;
    LD5 = HIGH;
    wait(0.5f);

    //Check if the chip is ready for a reading to be taken
    if (max1.ready()==1){
      //Get the reading
      fvalue = max1.read_temp();

      if (fvalue > 2000){
        if(fvalue==2001){
          dev.printf("No TC");
        }else if(fvalue==2002){
          dev.printf("Short to GND");
        }else if(fvalue==2004){
          dev.printf("Short to VCC");
        }
      }else{
        dev.printf("Temperature is: %f\n\r", fvalue);
      }

      //dev.printf("STM32 Testing 2\n");
    }
  }
}
