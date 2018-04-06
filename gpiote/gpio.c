#include "gpio.h"

void gpio_set_ground_output(){
  for(int i = 4; i <= 15; i++){
    GPIO->DIRSET = (1 << i);
    GPIO->OUTCLR = (1 << i);
  }
}
